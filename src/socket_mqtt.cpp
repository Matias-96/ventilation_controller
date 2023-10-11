/*
 ===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <cstdio>
#include "systick.h"
#include "esp8266_socket.h"
#include "retarget_uart.h"
#include "ModbusMaster.h"
#include "ModbusRegister.h"
#include "MQTTClient.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include "SDP610.h"
#include <cstring>
#include <string.h>
#include "VentilationSystem.h"
#include "VentilationFan.h"
#include <algorithm>
#include "LpcUart.h"
#include "GMP252.h"
#include "HMP60.h"

#include "MenuItem.h"
#include "HumTempModbus.h"
//#include "Co2Modbus.h"
#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include "DecimalEdit.h"
#include "StringEdit.h"
#include "Button.h"

#include "MonitorEdit.h"
#include <LogEdit.h>

#define SSID	    "SmartIotMQTT"
#define PASSWORD    "SmartIot"
#define BROKER_IP   "192.168.1.106"
#define BROKER_PORT  1883

// TODO: insert other definitions and declarations here
static volatile int counter;
static volatile uint32_t systicks = 0;
static volatile bool t3Fired;
int mrtch;

VentilationSystem *s;
Button *upBtn;
Button *backBtn;
Button *okBtn;
Button *downBtn;
SimpleMenu *menu_ptr;

IntegerEdit *speed_ptr;
IntegerEdit *pressure_ptr;
StringEdit *mode_ptr;


#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */

void SysTick_Handler(void) {
	systicks++;
	if (counter > 0)
		counter--;
}

void MRT_IRQHandler(void) {
	uint32_t int_pend;

	/* Get and clear interrupt pending status for all timers */
	int_pend = Chip_MRT_GetIntPending();
	Chip_MRT_ClearIntPending(int_pend);

	if (upBtn && upBtn->read()) {
		menu_ptr->event(MenuItem::up);
	} else if (backBtn && backBtn->read()) {
		menu_ptr->event(MenuItem::back);
	} else if (okBtn && okBtn->read()) {
		menu_ptr->event(MenuItem::ok);
	} else if (downBtn && downBtn->read()) {
		menu_ptr->event(MenuItem::down);
	}
}

uint32_t get_ticks(void) {
	return systicks;
}

#ifdef __cplusplus
}
#endif

void init_MRT_interupt() {
	/* MRT Initialization and disable all timers */
	Chip_MRT_Init();
	int mrtch;
	for (mrtch = 0; mrtch < MRT_CHANNELS_NUM; mrtch++) {
		Chip_MRT_SetDisabled(Chip_MRT_GetRegPtr(mrtch));
	}

	/* Enable the interrupt for the MRT */
	NVIC_EnableIRQ(MRT_IRQn);

	/* Get pointer to timer selected by ch */
	LPC_MRT_CH_T *pMRT = Chip_MRT_GetRegPtr(0);

	/* Setup timer with rate based on MRT clock */
	// 200ms interval
	//Chip_MRT_SetInterval(pMRT, 14400000U | MRT_INTVAL_LOAD);
	// 100ms interval
	Chip_MRT_SetInterval(pMRT, 7200000 | MRT_INTVAL_LOAD);

	/* Timer mode */
	Chip_MRT_SetMode(pMRT, MRT_MODE_REPEAT);

	/* Clear pending interrupt and enable timer */
	Chip_MRT_IntClear(pMRT);
	Chip_MRT_SetEnabled(pMRT);
}

void Sleep(int ms) {
	counter = ms;
	while (counter > 0) {
		__WFI();
	}
}

/* this function is required by the modbus library */
uint32_t millis() {
	return systicks;
}

void abbModbusTest();
void socketTest();
void mqttTest();
void produalModbusTest();
void messageArrived(MessageData *data);

#if 1
int main(void) {

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
#endif
#endif
	// this call initializes debug uart for stdout redirection
	retarget_init();
	/* Set up SWO to PIO1_2 */
	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2); // Needed for SWO printf

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

	printf("\nBoot\n");

	ModbusMaster fanNode(1);
	//ModbusMaster co2Node(240);
	//ModbusMaster humTempNode(241);

	fanNode.begin(9600);
	//co2Node.begin(9600);
	//humTempNode.begin(9600);

	ModbusRegister AO1(&fanNode, 0);
	ModbusRegister DI1(&fanNode, 4, false);
	//ModbusRegister CO2(&co2Node, 256, false);
	//ModbusRegister CO2status(&co2Node, 2049, false);
	//ModbusRegister temp_register(&humTempNode, 257, false);

	DigitalIoPin a5(0, 7, DigitalIoPin::pullup, true);
	DigitalIoPin a4(0, 6, DigitalIoPin::pullup, true);
	DigitalIoPin a3(0, 5, DigitalIoPin::pullup, true);
	DigitalIoPin a2(1, 8, DigitalIoPin::pullup, true);

	Button up(&a5);
	Button back(&a4);
	Button ok(&a3);
	Button down(&a2);

	upBtn = &up;
	backBtn = &back;
	okBtn = &ok;
	downBtn = &down;

	DigitalIoPin *rs = new DigitalIoPin(0, 29, DigitalIoPin::output);
	DigitalIoPin *en = new DigitalIoPin(0, 9, DigitalIoPin::output);
	DigitalIoPin *d4 = new DigitalIoPin(0, 10, DigitalIoPin::output);
	DigitalIoPin *d5 = new DigitalIoPin(0, 16, DigitalIoPin::output);
	DigitalIoPin *d6 = new DigitalIoPin(1, 3, DigitalIoPin::output);
	DigitalIoPin *d7 = new DigitalIoPin(0, 0, DigitalIoPin::output);

	LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
	VentilationFan fan(&AO1, &AO1, 0, false);
	SDP610 pressure_sensor(LPC_I2C0);
	//Co2Modbus co2Probe(&co2Node, 256, 2049);
	SimpleMenu menu;
	menu_ptr = &menu;

	/* connect to mqtt broker, subscribe to a topic,
	 * send and receive messages regularly every 1 sec */



	 MQTTClient client;
	 Network network;
	 unsigned char sendbuf[256], readbuf[2556];
	 int rc = 0, count = 0;
	 MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;


	 NetworkInit(&network, SSID, PASSWORD);
	 MQTTClientInit(&client, &network, 5000, sendbuf, sizeof(sendbuf), readbuf,
	 sizeof(readbuf));

	 char *address = (char*) BROKER_IP;
	 if ((rc = NetworkConnect(&network, address, BROKER_PORT)) != 0)
	 printf("Return code from network connect is %d\n", rc);

	 connectData.MQTTVersion = 3;
	 connectData.clientID.cstring = (char*) "esp_test";

	 bool mqtt_connected;

	 if ((rc = MQTTConnect(&client, &connectData)) != 0) {
	 printf("Return code from MQTT connect is %d\n", rc);
	 mqtt_connected = false;
	 }

	 else {
	 printf("MQTT Connected\n");
	 mqtt_connected = true;
	 }

	 if ((rc = MQTTSubscribe(&client, "controller/settings", QOS2,
	 messageArrived)) != 0)
	 printf("Return code from MQTT subscribe is %d\n", rc);

	VentilationSystem system(&fan, &pressure_sensor, true, 0);

	s = &system;
	uint32_t sec_20 = 0;
	uint32_t sec_5 = 0;
	uint32_t sec_3 = 0;

	std::vector<std::string> modeOptions = { "Auto", "Manual" };
	StringEdit modeEdit(&lcd, "Mode", modeOptions);
	mode_ptr = &modeEdit;

	std::vector<std::string> statusLog = { "Pressure", "Fan", "GMP252", "HMP60", "SDP610" }; // TODO append with relevant codes
	LogEdit status(&lcd, "Device Status", statusLog);
	std::vector<int> statusValues = { 0, 0, 0, 0, 0 };
	status.setValues(statusValues);

	IntegerEdit fanSpeed(&lcd, "Set fan speed", 0, 100, 1, "%");
	IntegerEdit targetPressure(&lcd, "Set pressure", 0, 120, 1, "Pa");
	MonitorEdit monitor(&lcd, "Pa", "Ppm", "RH%", "C");
	monitor.setValues(100, 600, 30, 23);

	speed_ptr = &fanSpeed;
	pressure_ptr = &targetPressure;

	menu.addItem(new MenuItem(&monitor));
	menu.addItem(new MenuItem(&status));
	menu.addItem(new MenuItem(&modeEdit));
	menu.addItem(new MenuItem(&fanSpeed));
	menu.addItem(new MenuItem(&targetPressure));

	menu.event(MenuItem::show);

	HMP60 temp_humidity_sensor;
	GMP252 co2_sensor;

	init_MRT_interupt();

	while (true) {

		if (get_ticks() / 3000 != sec_3) {
			sec_3 = get_ticks() / 3000;

			if (modeEdit.getValue() == "Manual") {
				system.set_speed(fanSpeed.getValue());
				system.set_mode(false);
			} else {
				fanSpeed.setValue(system.get_speed());
				system.set_target_pressure(targetPressure.getValue());
				system.set_mode(true);
			}

			system.adjust();
		}

		 if (mqtt_connected && get_ticks() / 5000 != sec_5) {
			 sec_5 = get_ticks() / 5000;
			 MQTTMessage message;
			 char payload[150];

			 ++count;

			 Sleep(5);
			int humidity = temp_humidity_sensor.getHumidity();
			Sleep(5);
			int co2 = co2_sensor.get_co2();
			Sleep(5);
			int temp = temp_humidity_sensor.getTemperature();
			Sleep(5);
			int temp_sensor_status = temp_humidity_sensor.getStatus();
			Sleep(5);
			int co2_sensor_status = co2_sensor.getStatus();
			int pressure = system.get_pressure();
			monitor.setValues(pressure, co2, humidity, temp);

			//printf("%d %d \n", co2_sensor_status, temp_sensor_status);

			//{ "Pressure", "Fan", "GMP252", "HMP60", "SDP610" };
			statusValues[0] = system.pressure_error();
			statusValues[1] = system.fan_error();
			statusValues[2] = co2_sensor_status;
			statusValues[3] = temp_sensor_status;
			statusValues[4] = system.sensor_error();
			status.setValues(statusValues);

			menu.event(MenuItem::show);

			 message.qos = QOS1;
			 message.retained = 0;
			 message.payload = payload;
			sprintf(payload, "{\"nr\":%4d, \"speed\":%3d, \"setpoint\":%3d, \"pressure\":%3d, \"auto\":%5s, \"error\":%5s, \"co2\":%d, \"rh\":%d, \"temp\":%d }",
					count,
					system.get_speed(),
					system.get_mode() ? system.get_target_pressure() : system.get_speed(),
					pressure,
					system.get_mode() ? "true" : "false",
					system.error() ? "true" : "false",
					co2,
					humidity,
					temp);
			 message.payloadlen = strlen(payload);

			 if ((rc = MQTTPublish(&client, "controller/status", &message)) != 0) {
				 printf("Return code from MQTT publish is %d\n", rc);
				 mqtt_connected = false;
			 }
		 }

		 // Try to reconnect every 20 seconds
		 if (!mqtt_connected && get_ticks() / 20000 != sec_20) {
		 printf("trying to reconnect to MQTT\n");
		 sec_20 = get_ticks() / 20000;
		 //NetworkDisconnect(&network);
		 // we should re-establish connection!!
		 if ((rc = MQTTConnect(&client, &connectData)) != 0) {
		 printf("Return code from MQTT connect is %d\n", rc);
		 } else {
		 printf("MQTT Connected\n");
		 mqtt_connected = true;
		 if ((rc = MQTTSubscribe(&client, "controller/settings", QOS2,
		 messageArrived)) != 0)
		 printf("Return code from MQTT subscribe is %d\n", rc);
		 }

		 //break;
		 }

		 // run MQTT for 100 ms
		 if ((rc = MQTTYield(&client, 100)) != 0)
		 printf("Return code from yield is %d\n", rc);
	}

	printf("MQTT connection closed!\n");

	while (1) {}

	return 0;

}
#endif

#if 1

void messageArrived(MessageData *data) {
	//printf("Message arrived on topic %.*s: %.*s\n", data->topicName->lenstring.len, data->topicName->lenstring.data,
	//		data->message->payloadlen, (char *)data->message->payload);
	std::string input((char*) data->message->payload,
			data->message->payloadlen);
	// Remove unwanted characters from input
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	input.erase(remove(input.begin(), input.end(), '"'), input.end());
	input.erase(remove(input.begin(), input.end(), '{'), input.end());
	input.erase(remove(input.begin(), input.end(), '}'), input.end());

	size_t separator_position = input.find(",");
	if (separator_position == std::string::npos) {
		printf("Invalid MQTT message\n");
		// Invalid msg
		// TODO Set active error.
		return;
	}
	std::string mode = input.substr(0, separator_position);
	std::string value = input.substr(separator_position + 1,
			input.length() - separator_position - 1);
	bool auto_mode = false;

	if (mode.find("auto") == 0) {
		if (mode.find("true") != std::string::npos) {
			auto_mode = true;
			printf("Mode: auto\n");
		} else if (mode.find("false") != std::string::npos) {
			auto_mode = false;
			printf("Mode: manual\n");
		} else {
			printf("Value is invalid\r\n");
			// TODO Set active error.
			return;
		}
	} else {
		printf("Invalid input\r\n");
		// TODO Set active error.
		return;
	}

	size_t colon_pos = value.find(":", 0);
	int reading = 0;
	if (value.find("pressure") != std::string::npos) {
		reading = std::stoi(value.substr(colon_pos + 1, std::string::npos));
		printf("Pressure input: %d\r\n", reading);
	} else if (value.find("speed") != std::string::npos) {
		reading = std::stoi(value.substr(colon_pos + 1, std::string::npos));
		printf("Speed input: %d\r\n", reading);
	} else {
		printf("Value is invalid\r\n");
		// TODO Set active error.
		return;
	}

	s->set_mode(auto_mode);

	if (auto_mode) {
		s->set_target_pressure(reading);
		mode_ptr->setValue(std::string("Auto"));
		pressure_ptr->setValue(reading);
	} else {
		s->set_speed(reading);
		speed_ptr->setValue(reading);
		mode_ptr->setValue(std::string("Manual"));
	}
	menu_ptr->event(MenuItem::show);

}

void mqttTest() {
	/* connect to mqtt broker, subscribe to a topic, send and receive messages regularly every 1 sec */
	MQTTClient client;
	Network network;
	unsigned char sendbuf[256], readbuf[2556];
	int rc = 0, count = 0;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

	NetworkInit(&network, SSID, PASSWORD);
	MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf,
			sizeof(readbuf));

	char *address = (char*) BROKER_IP;
	if ((rc = NetworkConnect(&network, address, BROKER_PORT)) != 0)
		printf("Return code from network connect is %d\n", rc);

	connectData.MQTTVersion = 3;
	connectData.clientID.cstring = (char*) "esp_test";

	if ((rc = MQTTConnect(&client, &connectData)) != 0)
		printf("Return code from MQTT connect is %d\n", rc);
	else
		printf("MQTT Connected\n");

	if ((rc = MQTTSubscribe(&client, "test/sample", QOS2, messageArrived)) != 0)
		printf("Return code from MQTT subscribe is %d\n", rc);

	uint32_t sec = 0;
	while (true) {
		// send one message per second
		if (get_ticks() / 1000 != sec) {
			MQTTMessage message;
			char payload[30];

			sec = get_ticks() / 1000;
			++count;

			message.qos = QOS1;
			message.retained = 0;
			message.payload = payload;
			sprintf(payload, "message number %d", count);
			message.payloadlen = strlen(payload);

			if ((rc = MQTTPublish(&client, "controller/status", &message)) != 0)
				printf("Return code from MQTT publish is %d\n", rc);
		}

		if (rc != 0) {
			NetworkDisconnect(&network);
			// we should re-establish connection!!
			break;
		}

		// run MQTT for 100 ms
		if ((rc = MQTTYield(&client, 100)) != 0)
			printf("Return code from yield is %d\n", rc);
	}

	printf("MQTT connection closed!\n");

}
#endif

#if 0   // example that uses modbus library directly
void printRegister(ModbusMaster& node, uint16_t reg)
{
	uint8_t result;
	// slave: read 16-bit registers starting at reg to RX buffer
	result = node.readHoldingRegisters(reg, 1);

	// do something with data if read is successful
	if (result == node.ku8MBSuccess)
	{
		printf("R%d=%04X\n", reg, node.getResponseBuffer(0));
	}
	else {
		printf("R%d=???\n", reg);
	}
}

bool setFrequency(ModbusMaster& node, uint16_t freq)
{
	uint8_t result;
	int ctr;
	bool atSetpoint;
	const int delay = 500;

	node.writeSingleRegister(1, freq); // set motor frequency

	printf("Set freq = %d\n", freq/40); // for debugging

	// wait until we reach set point or timeout occurs
	ctr = 0;
	atSetpoint = false;
	do {
		Sleep(delay);
		// read status word
		result = node.readHoldingRegisters(3, 1);
		// check if we are at setpoint
		if (result == node.ku8MBSuccess) {
			if(node.getResponseBuffer(0) & 0x0100) atSetpoint = true;
		}
		ctr++;
	} while(ctr < 20 && !atSetpoint);

	printf("Elapsed: %d\n", ctr * delay); // for debugging

	return atSetpoint;
}


void abbModbusTest()
{
	ModbusMaster node(2); // Create modbus object that connects to slave id 2
	node.begin(9600); // set transmission rate - other parameters are set inside the object and can't be changed here

	printRegister(node, 3); // for debugging

	node.writeSingleRegister(0, 0x0406); // prepare for starting

	printRegister(node, 3); // for debugging

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	printRegister(node, 3); // for debugging

	node.writeSingleRegister(0, 0x047F); // set drive to start mode

	printRegister(node, 3); // for debugging

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	printRegister(node, 3); // for debugging

	int i = 0;
	int j = 0;
	const uint16_t fa[20] = { 1000, 2000, 3000, 3500, 4000, 5000, 7000, 8000, 10000, 15000, 20000, 9000, 8000, 7000, 6000, 5000, 4000, 3000, 2000, 1000 };

	while (1) {
		uint8_t result;

		// slave: read (2) 16-bit registers starting at register 102 to RX buffer
		j = 0;
		do {
			result = node.readHoldingRegisters(102, 2);
			j++;
		} while(j < 3 && result != node.ku8MBSuccess);
		// note: sometimes we don't succeed on first read so we try up to threee times
		// if read is successful print frequency and current (scaled values)
		if (result == node.ku8MBSuccess) {
			printf("F=%4d, I=%4d  (ctr=%d)\n", node.getResponseBuffer(0), node.getResponseBuffer(1),j);
		}
		else {
			printf("ctr=%d\n",j);
		}

		Sleep(3000);
		i++;
		if(i >= 20) {
			i=0;
		}
		// frequency is scaled:
		// 20000 = 50 Hz, 0 = 0 Hz, linear scale 400 units/Hz
		setFrequency(node, fa[i]);
	}
}
#endif

#if 0
void produalModbusTest() {
	ModbusMaster node(1); // Create modbus object that connects to slave id 1
	node.begin(9600); // set transmission rate - other parameters are set inside the object and can't be changed here

	ModbusRegister AO1(&node, 0);
	ModbusRegister DI1(&node, 4, false);

	const uint16_t fa[20] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5,
			4, 3, 2, 1 };

	while (1) {

		for (int i = 0; i < 20; ++i) {
			printf("DI1=%4d\n", DI1.read());
			AO1.write(fa[i] * 100);
			// just print the value without checking if we got a -1
			printf("AO1=%4d\n", (int) fa[i] * 100);

			Sleep(5000);
			printf("DI1=%4d\n", DI1.read());
			Sleep(5000);
		}
	}
}
#endif

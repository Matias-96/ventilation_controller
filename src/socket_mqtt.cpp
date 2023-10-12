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
#include "SimpleMenu.h"
#include "IntegerEdit.h"
#include "DecimalEdit.h"
#include "StringEdit.h"
#include "Button.h"

#include "MonitorEdit.h"
#include <LogEdit.h>
#include <mutex>
#include "Imutex.hpp"

//#define SSID	    "SmartIotMQTT"
//#define PASSWORD    "SmartIot"
//#define BROKER_IP   "192.168.1.106"

#define SSID	    "TP_Link_20E6"
#define PASSWORD    "Oranssikesakyy105"
#define BROKER_IP   "192.168.1.101"
#define BROKER_PORT  1883

// TODO: insert other definitions and declarations here
static volatile int counter;
static volatile uint32_t systicks = 0;
static volatile bool t3Fired;
int mrtch;

VentilationSystem *system_ptr = nullptr;
Button *upBtn;
Button *backBtn;
Button *okBtn;
Button *downBtn;
SimpleMenu *menu_ptr;

IntegerEdit *menu_speed;
IntegerEdit *menu_pressure;
StringEdit *menu_mode;


#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */

void SysTick_Handler(void) {
	systicks++;
	if(system_ptr) system_ptr->tick();
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
	// 100ms interval
	uint32_t value = 100 * (SystemCoreClock / 1000);
	Chip_MRT_SetInterval(pMRT, value | MRT_INTVAL_LOAD);

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
	fanNode.begin(9600);

	ModbusRegister AO1(&fanNode, 0);
	ModbusRegister DI1(&fanNode, 4, false);
	VentilationFan fan(&DI1, &AO1, 0, false);

	GMP252 co2_sensor;
	HMP60 temp_humidity_sensor;
	SDP610 pressure_sensor(LPC_I2C0);

	VentilationSystem system(&fan, &pressure_sensor, true, 0);
	system_ptr = &system;


	DigitalIoPin a5(0, 7, DigitalIoPin::pullup, true);
	DigitalIoPin a4(0, 6, DigitalIoPin::pullup, true);
	DigitalIoPin a3(0, 5, DigitalIoPin::pullup, true);
	DigitalIoPin a2(1, 8, DigitalIoPin::pullup, true);

	Button up(&a5, true, 1500);
	Button back(&a4);
	Button ok(&a3);
	Button down(&a2, true, 1500);

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
	lcd.setCursor(0,0);
	SimpleMenu menu;
	menu_ptr = &menu;

	 MQTTClient client;
	 Network network;
	 unsigned char sendbuf[256], readbuf[2556];
	 int rc = 0, count = 0;
	 MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;


	 lcd.print("Connecting...");
	 lcd.setCursor(0,1);
	 lcd.print(SSID);


	 NetworkInit(&network, SSID, PASSWORD);
	 MQTTClientInit(&client, &network, 5000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	 char *address = (char*) BROKER_IP;
	 int mqtt_status = 0;

	 rc = NetworkConnect(&network, address, BROKER_PORT);
	 if (rc != 0)
		 printf("Return code from network connect is %d\n", rc);

	 connectData.MQTTVersion = 3;
	 connectData.clientID.cstring = (char*) "esp_test";

	 bool mqtt_connected;
	 mqtt_status = rc = MQTTConnect(&client, &connectData);

	 if (rc != 0) {
		 printf("Return code from MQTT connect is %d\n", rc);
		 mqtt_connected = false;
	 }
	 else {
		 printf("MQTT Connected\n");
		 mqtt_connected = true;
		 mqtt_status = rc = MQTTSubscribe(&client, "controller/settings", QOS2,messageArrived);
		 if (rc != 0)
			 printf("Return code from MQTT subscribe is %d\n", rc);
	 }

	uint32_t sec_60 = 0;
	uint32_t sec_5 = 0;
	uint32_t sec_3 = 0;

	// Initialize menu
	std::vector<std::string> modeOptions = { "Auto", "Manual" };
	StringEdit modeEdit(&lcd, "Mode", modeOptions);
	menu_mode = &modeEdit;

	std::vector<std::string> statusLog = { "Pressure", "Fan", "GMP252", "HMP60", "SDP610", "MQTT" };
	LogEdit status(&lcd, "Device Status", statusLog);
	std::vector<int> statusValues = { 0, 0, 0, 0, 0, mqtt_status };
	status.setValues(statusValues);

	IntegerEdit fanSpeed(&lcd, "Set fan speed", 0, 100, 1, "%");
	IntegerEdit targetPressure(&lcd, "Set pressure", 0, 120, 1, "Pa");
	MonitorEdit monitor(&lcd, "Pa", "Ppm", "RH%", "C");
	monitor.setValues(0, 0, 0, 0);

	menu_speed = &fanSpeed;
	menu_pressure = &targetPressure;

	menu.addItem(new MenuItem(&monitor));
	menu.addItem(new MenuItem(&status));
	menu.addItem(new MenuItem(&modeEdit));
	menu.addItem(new MenuItem(&fanSpeed));
	menu.addItem(new MenuItem(&targetPressure));

	menu.event(MenuItem::show);

	init_MRT_interupt();

	while (true) {

		if (get_ticks() / 3000 != sec_3) {
			sec_3 = get_ticks() / 3000;

			if (modeEdit.getValue() == "Manual") {
				system.set_speed(fanSpeed.getValue());
				if(system.get_mode() != false){
					system.set_mode(false);
				}
			} else {
				fanSpeed.setValue(system.get_speed());
				system.set_target_pressure(targetPressure.getValue());
				if(system.get_mode() != true){
					system.set_mode(true);
				}
			}

			system.adjust();
		}

		 if (get_ticks() / 5000 != sec_5) {
			 sec_5 = get_ticks() / 5000;
			 int pressure = system.get_pressure();


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

			monitor.setValues(pressure, co2, humidity, temp);

			statusValues[0] = system.pressure_error();
			statusValues[1] = system.fan_error();
			statusValues[2] = co2_sensor_status;
			statusValues[3] = temp_sensor_status;
			statusValues[4] = system.sensor_error();
			statusValues[5] = mqtt_status;
			status.setValues(statusValues);

			menu.event(MenuItem::show);
			if(mqtt_connected){
				 MQTTMessage message;
				 char payload[150];
				 ++count;

				 message.qos = QOS1;
				 message.retained = 0;
				 message.payload = payload;
				sprintf(payload, "{\"nr\":%4d, \"speed\":%3d, \"setpoint\":%3d, \"pressure\":%3d, \"auto\":%5s, \"error\":%5s, \"co2\":%d, \"rh\":%d, \"temp\":%d }",
						count,
						system.get_speed(),
						system.get_mode() ? system.get_target_pressure() : system.get_speed(),
						pressure,
						system.get_mode() ? "true" : "false",
						system.pressure_error() ? "true" : "false",
						co2,
						humidity,
						temp);
				 message.payloadlen = strlen(payload);

				 mqtt_status = rc = MQTTPublish(&client, "controller/status", &message);
				 if (rc != 0) {
					 printf("Return code from MQTT publish is %d\n", rc);
					 mqtt_connected = false;
				 }
			}
		 }

		 // Try to reconnect every 60 seconds if connection to broker breaks
		 if (!mqtt_connected && get_ticks() / 60000 != sec_60) {
			 printf("trying to reconnect to MQTT\n");
			 sec_60 = get_ticks() / 60000;
			 mqtt_status = rc = MQTTConnect(&client, &connectData);
			 if (rc != 0) {
				 printf("Return code from MQTT connect is %d\n", rc);
			 }
			 else {
				 printf("MQTT Connected\n");
				 mqtt_connected = true;
				 mqtt_status = rc = MQTTSubscribe(&client, "controller/settings", QOS2, messageArrived);
				 if (rc != 0){
					 mqtt_connected = false;
					 printf("Return code from MQTT subscribe is %d\n", rc);
				 }
			 }
		 }

		 // run MQTT for 100 ms
		 if(mqtt_connected){
			 mqtt_status = rc = MQTTYield(&client, 100);
			 if (rc != 0){
				 printf("Return code from yield is %d\n", rc);
			 }
		 }

	}

	while (1) {}

	return 0;

}
#endif

void messageArrived(MessageData *data) {
	std::string input((char*) data->message->payload, data->message->payloadlen);
	// Remove unwanted characters from input
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	input.erase(remove(input.begin(), input.end(), '"'), input.end());
	input.erase(remove(input.begin(), input.end(), '{'), input.end());
	input.erase(remove(input.begin(), input.end(), '}'), input.end());

	size_t separator_pos = input.find(",");
	if (separator_pos == std::string::npos) {
		printf("Invalid MQTT message\n");
		// Invalid msg
		// TODO Set active error.
		return;
	}
	std::string mode = input.substr(0, separator_pos);
	std::string value = input.substr(separator_pos + 1, input.length() - separator_pos - 1);
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
	// Check that number input is a valid number and does not contain text
	std::string number_input = value.substr(colon_pos + 1, std::string::npos);
	for(char c : number_input){
		if(!isdigit(c)){
			printf("Input value is not a valid number\r\n");
			return;
		}
	}

	if (auto_mode && value.find("pressure") != std::string::npos) {
		reading = std::stoi(number_input);
		printf("Pressure input: %d\r\n", reading);
	}
	else if (!auto_mode && value.find("speed") != std::string::npos) {
		reading = std::stoi(number_input);
		printf("Speed input: %d\r\n", reading);
	}
	else {
		printf("Value is invalid\r\n");
		// TODO Set active error.
		return;
	}

	Imutex guard;
	std::lock_guard<Imutex> lock(guard);
	system_ptr->set_mode(auto_mode);
	if (auto_mode) {
		system_ptr->set_target_pressure(reading);
		menu_mode->setValue(std::string("Auto"));
		menu_pressure->setValue(reading);
	} else {
		system_ptr->set_speed(reading);
		menu_speed->setValue(reading);
		menu_mode->setValue(std::string("Manual"));
	}
	menu_ptr->event(MenuItem::show);

}


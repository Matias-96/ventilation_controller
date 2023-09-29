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
#include <cstring>
#include "systick.h"
#include "LpcUart.h"
#include "esp8266_socket.h"
#include "retarget_uart.h"
#include "ModbusMaster.h"
#include "ModbusRegister.h"
#include "MQTTClient.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include "SDP610.h"
#include <string>
#include <string.h>
//#include "VentilationSystem.h"
//#include "VentilationFan.h"

#define SSID	    ""
#define PASSWORD    ""
#define BROKER_IP   "192.168.1.101"
#define BROKER_PORT  1883

// TODO: insert other definitions and declarations here
static volatile int counter;
static volatile uint32_t systicks;

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

uint32_t get_ticks(void) {
	return systicks;
}

#ifdef __cplusplus
}
#endif

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
void messageArrived(MessageData* data);

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

	DigitalIoPin *rs = new DigitalIoPin(0, 29, DigitalIoPin::output);
	DigitalIoPin *en = new DigitalIoPin(0, 9, DigitalIoPin::output);
	DigitalIoPin *d4 = new DigitalIoPin(0, 10, DigitalIoPin::output);
	DigitalIoPin *d5 = new DigitalIoPin(0, 16, DigitalIoPin::output);
	DigitalIoPin *d6 = new DigitalIoPin(1, 3, DigitalIoPin::output);
	DigitalIoPin *d7 = new DigitalIoPin(0, 0, DigitalIoPin::output);
	LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

	// configure display geometry
	//lcd.begin(16, 2);
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	//lcd.setCursor(0, 0);
	// Print a message to the LCD.
	//lcd.print(SSID);
	//lcd.setCursor(0, 1);
	//lcd.print(BROKER_IP);
	//char tmp[8];
	//sprintf(tmp, ":%d", BROKER_PORT);
	//lcd.print(tmp);

	//abbModbusTest();
	//socketTest();
	//mqttTest();
	//produalModbusTest();

	// printing co2 measurements -- Matias

	ModbusMaster fanNode(1); // slave address of 1
	ModbusMaster co2Node(240); // slave address of 240

	ModbusMaster temp(241); // slave address of 240

	fanNode.begin(9600);
	co2Node.begin(9600);

	//notice the offset of -1 when defining the register number
	//ModbusRegister::read() checks the next register over

	ModbusRegister AO1(&fanNode, 0); // drive the motor
	ModbusRegister DI1(&fanNode, 4, false); // set holding register to false if it's read only
	ModbusRegister CO2(&co2Node, 256, false); // 257 - measured co2 value
	ModbusRegister CO2status(&co2Node, 2049, false); // 0 if ok

	ModbusRegister temp_register(&temp, 257, false); // 0 if ok

	// printing co2 measurements -- Matias

	//AO1.write(0); // fan speed at 50%

	//SDP610 pressure_sensor(LPC_I2C0);
	//int i2c_error = 0;

	/* connect to mqtt broker, subscribe to a topic, send and receive messages regularly every 1 sec */
	/*
	MQTTClient client;
	Network network;
	unsigned char sendbuf[256], readbuf[2556];
	int rc = 0, count = 0;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

	NetworkInit(&network,SSID,PASSWORD);
	MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	char* address = (char *)BROKER_IP;
	if ((rc = NetworkConnect(&network, address, BROKER_PORT)) != 0)
		printf("Return code from network connect is %d\n", rc);


	connectData.MQTTVersion = 3;
	connectData.clientID.cstring = (char *)"esp_test";

	if ((rc = MQTTConnect(&client, &connectData)) != 0)
		printf("Return code from MQTT connect is %d\n", rc);
	else
		printf("MQTT Connected\n");

	if ((rc = MQTTSubscribe(&client, "controller/settings", QOS2, messageArrived)) != 0)
		printf("Return code from MQTT subscribe is %d\n", rc);
	int pressure = 0;
*/
	while (true)
	{
		Sleep(2000);
		printf("Temp reading: %d ppm\n", temp_register.read()); // returns -1 if read is unsuccessful
		//printf("CO2 status: %d\n", CO2status.read()); // 0 - status OK
		//pressure = pressure_sensor.read(i2c_error);
		//if(i2c_error){
		//	printf("I2C Error occurred\r\n");
		//	break;
		//}
		/*
		MQTTMessage message;
		char payload[30];

		++count;

		message.qos = QOS1;
		message.retained = 0;
		message.payload = payload;
		sprintf(payload, "counter %d", count);
		message.payloadlen = strlen(payload);

		if ((rc = MQTTPublish(&client, "controller/status", &message)) != 0)
			printf("Return code from MQTT publish is %d\n", rc);


		if(rc != 0) {
			NetworkDisconnect(&network);
			// we should re-establish connection!!
			break;
		}

		// run MQTT for 100 ms
		if ((rc = MQTTYield(&client, 100)) != 0)
			printf("Return code from yield is %d\n", rc);

		*/
	}

	printf("MQTT connection closed!\n");

	while (1) {

	}

	return 0;

}
#endif

#if 0  // example of opening a plain socket
void socketTest()
{

	esp_socket(SSID, PASSWORD);

	const char *http_request = "GET / HTTP/1.0\r\n\r\n"; // HTTP requires cr-lf to end a line

	for(int i = 0; i < 2; ++i) {
		printf("\nopen socket\n");
		esp_connect(1,  "www.metropolia.fi", 80);
		printf("\nsend request\n");
		esp_write(1, http_request, strlen(http_request));

		uint32_t now = get_ticks();
		printf("\nreply:\n");

		while(get_ticks() - now < 3000) {
			char buffer[64];
			memset(buffer, 0, 64);
			if(esp_read(1, buffer, 63) > 0) {
				fputs(buffer,stdout);
			}
		}
		esp_close(1);

		printf("\nsocket closed\n");
	}

}
#endif

#if 1

void messageArrived(MessageData* data)
{
	printf("Message arrived on topic %.*s: %.*s\n", data->topicName->lenstring.len, data->topicName->lenstring.data,
			data->message->payloadlen, (char *)data->message->payload);
	std::string input((char *)data->message->payload, data->message->payloadlen);
	size_t comma_pos = input.find(",", 0);
	std::string mode = input.substr(0, comma_pos);
	std::string value = input.substr(comma_pos+1, input.length() - comma_pos - 2);

	if(mode.find("auto", 0)){
		if(mode.find("true", 0) != std::string::npos){
			printf("Value is true\r\n");
		}
		else if(mode.find("false", 0) != std::string::npos) {
			printf("Value is false\r\n");
		}
		else {
			printf("Value is invalid\r\n");
		}
	}
	else {
		printf("Invalid input\r\n");
	}

	size_t colon_pos = value.find(":", 0);
	int reading;
	if(value.find("pressure") != std::string::npos){
		reading = std::stoi(value.substr(colon_pos+1, std::string::npos));
		printf("Pressure input: %d\r\n", reading);
	}
	else if(value.find("speed") != std::string::npos){
		reading = std::stoi(value.substr(colon_pos+1, std::string::npos));
		printf("Speed input: %d\r\n", reading);
	}
	else {
		printf("Value is invalid\r\n");
	}
}

void mqttTest()
{
	/* connect to mqtt broker, subscribe to a topic, send and receive messages regularly every 1 sec */
	MQTTClient client;
	Network network;
	unsigned char sendbuf[256], readbuf[2556];
	int rc = 0,
			count = 0;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

	NetworkInit(&network,SSID,PASSWORD);
	MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	char* address = (char *)BROKER_IP;
	if ((rc = NetworkConnect(&network, address, BROKER_PORT)) != 0)
		printf("Return code from network connect is %d\n", rc);


	connectData.MQTTVersion = 3;
	connectData.clientID.cstring = (char *)"esp_test";

	if ((rc = MQTTConnect(&client, &connectData)) != 0)
		printf("Return code from MQTT connect is %d\n", rc);
	else
		printf("MQTT Connected\n");

	if ((rc = MQTTSubscribe(&client, "test/sample", QOS2, messageArrived)) != 0)
		printf("Return code from MQTT subscribe is %d\n", rc);

	uint32_t sec = 0;
	while (true)
	{
		// send one message per second
		if(get_ticks() / 1000 != sec) {
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

		if(rc != 0) {
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

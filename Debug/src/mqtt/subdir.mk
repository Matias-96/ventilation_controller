################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mqtt/serial_port.cpp 

C_SRCS += \
../src/mqtt/MQTT_lpc1549.c \
../src/mqtt/esp8266_socket.c 

CPP_DEPS += \
./src/mqtt/serial_port.d 

C_DEPS += \
./src/mqtt/MQTT_lpc1549.d \
./src/mqtt/esp8266_socket.d 

OBJS += \
./src/mqtt/MQTT_lpc1549.o \
./src/mqtt/esp8266_socket.o \
./src/mqtt/serial_port.o 


# Each subdirectory must supply rules for building sources it contributes
src/mqtt/%.o: ../src/mqtt/%.c src/mqtt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\workspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\workspace\lpc_chip_15xx\inc" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\modbus" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/mqtt/%.o: ../src/mqtt/%.cpp src/mqtt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\workspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\workspace\lpc_chip_15xx\inc" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\modbus" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-mqtt

clean-src-2f-mqtt:
	-$(RM) ./src/mqtt/MQTT_lpc1549.d ./src/mqtt/MQTT_lpc1549.o ./src/mqtt/esp8266_socket.d ./src/mqtt/esp8266_socket.o ./src/mqtt/serial_port.d ./src/mqtt/serial_port.o

.PHONY: clean-src-2f-mqtt


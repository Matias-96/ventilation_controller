################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/modbus/ModbusMaster.cpp \
../src/modbus/ModbusRegister.cpp \
../src/modbus/SerialPort.cpp 

CPP_DEPS += \
./src/modbus/ModbusMaster.d \
./src/modbus/ModbusRegister.d \
./src/modbus/SerialPort.d 

OBJS += \
./src/modbus/ModbusMaster.o \
./src/modbus/ModbusRegister.o \
./src/modbus/SerialPort.o 


# Each subdirectory must supply rules for building sources it contributes
src/modbus/%.o: ../src/modbus/%.cpp src/modbus/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\workspace\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\workspace\lpc_chip_15xx\inc" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\modbus" -I"C:\Users\jpj1\amk-opiskelu\3_vuosi\embedded_systems_programming\ventilation_controller\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-modbus

clean-src-2f-modbus:
	-$(RM) ./src/modbus/ModbusMaster.d ./src/modbus/ModbusMaster.o ./src/modbus/ModbusRegister.d ./src/modbus/ModbusRegister.o ./src/modbus/SerialPort.d ./src/modbus/SerialPort.o

.PHONY: clean-src-2f-modbus


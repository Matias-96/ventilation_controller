################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DigitalIoPin.cpp \
../src/LiquidCrystal.cpp \
../src/LpcUart.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp \
../src/retarget_uart.cpp \
../src/socket_mqtt.cpp 

C_SRCS += \
../src/crp.c \
../src/sysinit.c 

CPP_DEPS += \
./src/DigitalIoPin.d \
./src/LiquidCrystal.d \
./src/LpcUart.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d \
./src/retarget_uart.d \
./src/socket_mqtt.d 

C_DEPS += \
./src/crp.d \
./src/sysinit.d 

OBJS += \
./src/DigitalIoPin.o \
./src/LiquidCrystal.o \
./src/LpcUart.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/retarget_uart.o \
./src/socket_mqtt.o \
./src/sysinit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\lpc_chip_15xx\inc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\modbus" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\lpc_chip_15xx\inc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\modbus" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\socket_mqtt\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/DigitalIoPin.d ./src/DigitalIoPin.o ./src/LiquidCrystal.d ./src/LiquidCrystal.o ./src/LpcUart.d ./src/LpcUart.o ./src/cr_cpp_config.d ./src/cr_cpp_config.o ./src/cr_startup_lpc15xx.d ./src/cr_startup_lpc15xx.o ./src/crp.d ./src/crp.o ./src/retarget_uart.d ./src/retarget_uart.o ./src/socket_mqtt.d ./src/socket_mqtt.o ./src/sysinit.d ./src/sysinit.o

.PHONY: clean-src


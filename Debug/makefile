################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/paho.mqtt.embedded-c/MQTTPacket/src/subdir.mk
-include src/paho.mqtt.embedded-c/MQTTClient-C/src/subdir.mk
-include src/mqtt/subdir.mk
-include src/modbus/subdir.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := socket_mqtt
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: socket_mqtt.axf

# Tool invocations
socket_mqtt.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\lpc_board_nxp_lpcxpresso_1549\Debug" -L"C:\Users\Matias\Documents\MCUXpressoIDE_11.5.1_7266\modbus_mqtt-master\lpc_chip_15xx\Debug" -Xlinker -Map="socket_mqtt.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T socket_mqtt_Debug.ld -o "socket_mqtt.axf" $(OBJS) $(USER_OBJS) $(LIBS) -llpc_board_nxp_lpcxpresso_1549 -llpc_chip_15xx
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) socket_mqtt.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "socket_mqtt.axf"; # arm-none-eabi-objcopy -v -O binary "socket_mqtt.axf" "socket_mqtt.bin" ; # checksum -p LPC1549 -d "socket_mqtt.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets

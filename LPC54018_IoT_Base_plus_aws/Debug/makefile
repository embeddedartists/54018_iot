################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wifi_qca/port/shields/subdir.mk
-include wifi_qca/port/env/freertos/subdir.mk
-include wifi_qca/port/drivers/flexcomm_freertos/subdir.mk
-include wifi_qca/custom_src/stack_custom/subdir.mk
-include wifi_qca/custom_src/qapi/subdir.mk
-include wifi_qca/custom_src/hw_interface/subdir.mk
-include wifi_qca/custom_src/driver/subdir.mk
-include wifi_qca/custom_src/api_interface/subdir.mk
-include wifi_qca/common_src/wmi/subdir.mk
-include wifi_qca/common_src/util/subdir.mk
-include wifi_qca/common_src/storerecall/subdir.mk
-include wifi_qca/common_src/stack_common/subdir.mk
-include wifi_qca/common_src/reorder/subdir.mk
-include wifi_qca/common_src/qapi/subdir.mk
-include wifi_qca/common_src/hw_interface/subdir.mk
-include wifi_qca/common_src/htc/subdir.mk
-include wifi_qca/common_src/driver/subdir.mk
-include wifi_qca/common_src/bmi/subdir.mk
-include wifi_qca/common_src/api_interface/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include mbedTLS/port/ksdk/subdir.mk
-include mbedTLS/library/subdir.mk
-include exp_click2/subdir.mk
-include exp_click1/subdir.mk
-include exp_arduino/subdir.mk
-include drivers/freertos/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include amazon-freertos/wifi/subdir.mk
-include amazon-freertos/utils/subdir.mk
-include amazon-freertos/tls/subdir.mk
-include amazon-freertos/third_party/jsmn/subdir.mk
-include amazon-freertos/shadow/subdir.mk
-include amazon-freertos/secure_sockets/subdir.mk
-include amazon-freertos/portable/subdir.mk
-include amazon-freertos/pkcs11/subdir.mk
-include amazon-freertos/mqtt/subdir.mk
-include amazon-freertos/logging/subdir.mk
-include amazon-freertos/drivers/subdir.mk
-include amazon-freertos/devmode_key_provisioning/subdir.mk
-include amazon-freertos/crypto/subdir.mk
-include amazon-freertos/bufferpool/subdir.mk
-include amazon-freertos/FreeRTOS/portable/subdir.mk
-include amazon-freertos/FreeRTOS/subdir.mk
-include Pervasive_EPD_BoosterPack2/subdir.mk
-include PervasiveDisplays_Library/src/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPC54018_IoT_Base_plus_aws.axf

# Tool invocations
LPC54018_IoT_Base_plus_aws.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\temp\2018-05-08_iot\ws\LPC54018_IoT_Base_plus_aws\libs" -Xlinker -Map="LPC54018_IoT_Base_plus_aws.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T "LPC54018_IoT_Base_plus_aws_Debug.ld" -o "LPC54018_IoT_Base_plus_aws.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) LPC54018_IoT_Base_plus_aws.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "LPC54018_IoT_Base_plus_aws.axf"; # arm-none-eabi-objcopy -v -O binary "LPC54018_IoT_Base_plus_aws.axf" "LPC54018_IoT_Base_plus_aws.bin" ; # checksum -p LPC54018 -d "LPC54018_IoT_Base_plus_aws.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/TaskEPD.cpp 

C_SRCS += \
../source/aws_shadow_lightbulb_on_off.c \
../source/data_store.c \
../source/expansion.c \
../source/freertos_helper.c \
../source/i2c_handler.c \
../source/main.c \
../source/semihost_hardfault.c 

OBJS += \
./source/TaskEPD.o \
./source/aws_shadow_lightbulb_on_off.o \
./source/data_store.o \
./source/expansion.o \
./source/freertos_helper.o \
./source/i2c_handler.o \
./source/main.o \
./source/semihost_hardfault.o 

CPP_DEPS += \
./source/TaskEPD.d 

C_DEPS += \
./source/aws_shadow_lightbulb_on_off.d \
./source/data_store.d \
./source/expansion.d \
./source/freertos_helper.d \
./source/i2c_handler.d \
./source/main.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DENERGIA -DMXL12835F -DXIP_IMAGE -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCPU_LPC54018JET180_cm4 -DCPU_LPC54018JET180 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DMBEDTLS_CONFIG_FILE='"aws_mbedtls_config.h"' -DA_LITTLE_ENDIAN -DIMG_BAUDRATE=96000000 -I../board -I../wifi_qca/port/shields -I../wifi_qca/port/shields/gt202 -I../wifi_qca/port/env/freertos -I../wifi_qca/common_src/hcd -I../wifi_qca/common_src/include -I../wifi_qca/common_src/stack_common -I../wifi_qca/common_src/wmi -I../wifi_qca/custom_src/include -I../wifi_qca/custom_src/stack_custom -I../wifi_qca/include/AR6002/hw2.0/hw -I../wifi_qca/include/AR6002/hw4.0/hw -I../wifi_qca/include/AR6002 -I../wifi_qca/include -I../wifi_qca/port -I../wifi_qca/port/drivers/flexcomm_freertos -I../PervasiveDisplays_Library/src -I../source -I../ -I../amazon-freertos/portable -I../amazon-freertos/FreeRTOS/portable -I../amazon-freertos/include -I../amazon-freertos/drivers -I../amazon-freertos/pkcs11 -I../amazon-freertos/third_party/jsmn -I../amazon-freertos/config_files -I../mbedTLS/include/mbedtls -I../mbedTLS/port/ksdk -I../mbedTLS/include -I../drivers -I../CMSIS -I../drivers/freertos -I../utilities -I../startup -I../Pervasive_EPD_BoosterPack2 -I../exp_click1 -I../exp_click2 -I../exp_arduino -O0 -fno-common -g -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__NEWLIB__ -DENERGIA -DMXL12835F -DXIP_IMAGE -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCPU_LPC54018JET180_cm4 -DCPU_LPC54018JET180 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DMBEDTLS_CONFIG_FILE='"aws_mbedtls_config.h"' -DA_LITTLE_ENDIAN -DIMG_BAUDRATE=96000000 -I../board -I../wifi_qca/port/shields -I../wifi_qca/port/shields/gt202 -I../wifi_qca/port/env/freertos -I../wifi_qca/common_src/hcd -I../wifi_qca/common_src/include -I../wifi_qca/common_src/stack_common -I../wifi_qca/common_src/wmi -I../wifi_qca/custom_src/include -I../wifi_qca/custom_src/stack_custom -I../wifi_qca/include/AR6002/hw2.0/hw -I../wifi_qca/include/AR6002/hw4.0/hw -I../wifi_qca/include/AR6002 -I../wifi_qca/include -I../wifi_qca/port -I../wifi_qca/port/drivers/flexcomm_freertos -I../PervasiveDisplays_Library/src -I../source -I../ -I../amazon-freertos/portable -I../amazon-freertos/FreeRTOS/portable -I../amazon-freertos/include -I../amazon-freertos/drivers -I../amazon-freertos/pkcs11 -I../amazon-freertos/third_party/jsmn -I../amazon-freertos/config_files -I../mbedTLS/include/mbedtls -I../mbedTLS/port/ksdk -I../mbedTLS/include -I../drivers -I../CMSIS -I../drivers/freertos -I../utilities -I../startup -I../Pervasive_EPD_BoosterPack2 -I../exp_click1 -I../exp_click2 -I../exp_arduino -O0 -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



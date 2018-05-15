################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/portable/fsl_tickless_systick.c \
../amazon-freertos/portable/heap_4.c 

OBJS += \
./amazon-freertos/portable/fsl_tickless_systick.o \
./amazon-freertos/portable/heap_4.o 

C_DEPS += \
./amazon-freertos/portable/fsl_tickless_systick.d \
./amazon-freertos/portable/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/portable/%.o: ../amazon-freertos/portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING -DENERGIA -DMXL12835F -DXIP_IMAGE -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCPU_LPC54018JET180_cm4 -DCPU_LPC54018JET180 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../PervasiveDisplays_Library/src -I../source -I../ -I../amazon-freertos/portable -I../amazon-freertos/FreeRTOS/portable -I../amazon-freertos/include -I../drivers -I../CMSIS -I../drivers/freertos -I../utilities -I../startup -I../Pervasive_EPD_BoosterPack2 -I../exp_click1 -I../exp_click2 -I../exp_arduino -Og -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PervasiveDisplays_Library/src/LCD_screen.cpp \
../PervasiveDisplays_Library/src/LCD_screen_buffer.cpp \
../PervasiveDisplays_Library/src/LCD_utilities.cpp \
../PervasiveDisplays_Library/src/Screen_EPD.cpp 

OBJS += \
./PervasiveDisplays_Library/src/LCD_screen.o \
./PervasiveDisplays_Library/src/LCD_screen_buffer.o \
./PervasiveDisplays_Library/src/LCD_utilities.o \
./PervasiveDisplays_Library/src/Screen_EPD.o 

CPP_DEPS += \
./PervasiveDisplays_Library/src/LCD_screen.d \
./PervasiveDisplays_Library/src/LCD_screen_buffer.d \
./PervasiveDisplays_Library/src/LCD_utilities.d \
./PervasiveDisplays_Library/src/Screen_EPD.d 


# Each subdirectory must supply rules for building sources it contributes
PervasiveDisplays_Library/src/%.o: ../PervasiveDisplays_Library/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DENERGIA -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING -DMXL12835F -DXIP_IMAGE -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCPU_LPC54018JET180_cm4 -DCPU_LPC54018JET180 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../exp_click1 -I../exp_click2 -I../exp_arduino -I../Pervasive_EPD_BoosterPack2 -I../PervasiveDisplays_Library/src -I../source -I../ -I../amazon-freertos/portable -I../amazon-freertos/FreeRTOS/portable -I../amazon-freertos/include -I../drivers -I../CMSIS -I../drivers/freertos -I../utilities -I../startup -Og -fno-common -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



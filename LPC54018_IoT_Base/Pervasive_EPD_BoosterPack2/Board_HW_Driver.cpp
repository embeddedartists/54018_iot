/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
**/


#include <stdint.h>
//#include <Arduino.h>
#include "Board_HW_Driver.h"
#include "fsl_spi.h"
#include "fsl_debug_console.h"
//#include <SPI.h>

#define millis() xTaskGetTickCount()

static  volatile uint32_t EPD_Counter;
//#define CS_H_L_Delay()	delayMicroseconds(10)
#define CS_H_L_Delay()   do { int cntDly = 20; while (--cntDly > 0) {	__NOP(); }} while (0)

static bool spi_initialized = false;

void Board_HW_DriverClass::begin()
{
    Config_Busy_Pin();
    Config_EPD_cs_Pin();
    Config_EPD_rst_Pin();
    Config_EPD_panelon_Pin();
    Config_EPD_discharge_Pin();
    Config_EPD_border_Pin();
    Config_EPD_flash_cs_Pin();
    Config_EPD_pwm_Pin();
    Config_LED1_Pin();
    Config_EPD_BS1_Pin();
    EPD_BS1_low();
    EPD_display_hardware_init();
    EPD_Counter = 0;
}
Board_HW_DriverClass::Board_HW_DriverClass()
{
    begin();
}


void Board_HW_DriverClass::end()
{

}


uint32_t Board_HW_DriverClass::getnowtime(void)
{
    return millis();
}

void Board_HW_DriverClass::start_EPD_timer(void)
{
    EPD_Counter = millis();
}
void Board_HW_DriverClass::stop_EPD_timer(void)
{
    EPD_Counter=0;
}
uint32_t Board_HW_DriverClass::get_EPD_time_tick(void)
{
    return (millis() - EPD_Counter);
}
//void Board_HW_DriverClass::PWM_run(uint16_t ms)
//{
//    start_EPD_timer();
//    do
//    {
//
//        EPD_pwm_high();
//        delayMicroseconds(20);
//        EPD_pwm_low();
//        delayMicroseconds(20);
//    }
//    while (get_EPD_time_tick() < ms);   //wait Delay Time
//
//    stop_EPD_timer();
//
//}
#define PIN_AS_FUNCX(__port, __pin, __func) do {\
	if (!IS_BAD(__port, __pin)) { \
	  uint32_t reg = IOCON->PIO[(__port)][(__pin)] & ~0x7; \
	  IOCON->PIO[(__port)][(__pin)] = reg | (((__func)<<0) & 0x7); \
	} \
} while(0)
#define PIN_AS_FUNC(PortPin, func) PIN_AS_FUNCX(PortPin, func)
//void spi_pins_as_spi(void)
//{
//	uint32_t reg = IOCON->PIO[1][28] & ~0x7;
//	IOCON->PIO[1][28] & ~0x7;
//	
//}
	

void Board_HW_DriverClass::EPD_spi_attach(void)
{
//    SPI.begin();
//	SPI.setClockDivider(SPI_CLOCK_DIV2);
	if (!spi_initialized) {
		
#define EXAMPLE_SPI_MASTER SPI7
#define EXAMPLE_SPI_MASTER_IRQ FLEXCOMM7_IRQn
#define EXAMPLE_SPI_MASTER_CLK_SRC kCLOCK_Flexcomm7
#define EXAMPLE_SPI_MASTER_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm7)
#define EXAMPLE_SPI_SSEL 0
#define EXAMPLE_SPI_SPOL kSPI_SpolActiveAllLow
		
		PIN_AS_FUNC(SPICLK_PIN, 1);
		PIN_AS_FUNC(SPIMOSI_PIN, 1);
		PIN_AS_FUNC(SPIMISO_PIN, 1);
		
		/* attach 12 MHz clock to SPI7 */
		CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);

		/* reset FLEXCOMM for SPI */
		RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);
    NVIC_SetPriority(EXAMPLE_SPI_MASTER_IRQ, 3);
	
    /*
     * userConfig.enableLoopback = false;
     * userConfig.enableMaster = true;
     * userConfig.polarity = kSPI_ClockPolarityActiveHigh;
     * userConfig.phase = kSPI_ClockPhaseFirstEdge;
     * userConfig.direction = kSPI_MsbFirst;
     * userConfig.baudRate_Bps = 500000U;
     */
		 spi_master_config_t userConfig = {0};
    SPI_MasterGetDefaultConfig(&userConfig);
		 userConfig.baudRate_Bps = 5000000U;
    uint32_t srcFreq = EXAMPLE_SPI_MASTER_CLK_FREQ;
    userConfig.sselNum = (spi_ssel_t)EXAMPLE_SPI_SSEL;
    userConfig.sselPol = (spi_spol_t)EXAMPLE_SPI_SPOL;
    if (SPI_MasterInit(EXAMPLE_SPI_MASTER, &userConfig, srcFreq) == kStatus_Success) {
			spi_initialized = true;
		}
	}
}

void Board_HW_DriverClass::EPD_spi_detach(void)
{
//    SPI.end();
		PIN_AS_FUNC(SPICLK_PIN, 0);
		PIN_AS_FUNC(SPIMOSI_PIN, 0);
		PIN_AS_FUNC(SPIMISO_PIN, 0);
    config_gpio_dir_o(SPICLK_PIN);
    config_gpio_dir_o(SPIMOSI_PIN);
    config_gpio_dir_o(SPIMISO_PIN);
    SPIMISO_low();
    SPIMOSI_low();
    SPICLK_low();
	if (spi_initialized) {
		SPI_Deinit(EXAMPLE_SPI_MASTER);
		spi_initialized = false;
	}
}
bool Board_HW_DriverClass::check_flash_spi(void)
{
    return true;
}
uint8_t Board_HW_DriverClass::EPD_spi_read(uint8_t data)
{
    //return SPI.transfer(data);
	
	uint8_t rx = 0;
	SPI_WriteData(EXAMPLE_SPI_MASTER, data, 0);
	rx = (uint8_t)SPI_ReadData(EXAMPLE_SPI_MASTER);
	while (!(SPI_GetStatusFlags(EXAMPLE_SPI_MASTER) & SPI_FIFOSTAT_TXEMPTY_MASK))
	{
	}
	return rx;
}
void Board_HW_DriverClass::EPD_spi_write(uint8_t data)
{
    //EPD_spi_read(data);
	SPI_WriteData(EXAMPLE_SPI_MASTER, data, 1<<22); // 1<<22 is RXIGNORE
	while (!(SPI_GetStatusFlags(EXAMPLE_SPI_MASTER) & SPI_FIFOSTAT_TXEMPTY_MASK))
	{
	}
}

void Board_HW_DriverClass::iTC_spi_sendReg(uint8_t register_index)
{
	//PRINTF("iTC_spi_sendReg: 0x%x\n", register_index);
    EPD_cs_low();
    EPD_DC_low();
    CS_H_L_Delay();
    EPD_spi_write(register_index);
    EPD_cs_high();
    CS_H_L_Delay();
    EPD_DC_high();
    EPD_cs_low();
    CS_H_L_Delay();
}
void Board_HW_DriverClass::iTC_spi_sendRegData(uint8_t register_data)
{
	//PRINTF("iTC_spi_sendRegData: 0x%x\n", register_data);
//	PRINTF(".");
    EPD_spi_write(register_data);
}
void Board_HW_DriverClass::iTC_spi_send(uint8_t register_index, uint8_t *register_data, uint8_t len)
{
	//PRINTF("iTC_spi_send: idx: 0x%x, len=%u: ", register_index, len);
    EPD_cs_low();
    EPD_DC_low();
    CS_H_L_Delay();
    EPD_spi_write(register_index);
    CS_H_L_Delay();
    EPD_DC_high();
    CS_H_L_Delay();
    while (len--)
    {
//PRINTF("0x%x, ", *register_data);
        EPD_spi_write(*register_data++);
        CS_H_L_Delay();
    }
//PRINTF("\n");

    EPD_cs_high();
}
void Board_HW_DriverClass::iTC_spi_send_array(Em_register_array_t *register_array, uint8_t len)
{
	//PRINTF("iTC_spi_send_array: len=%u\n", len);
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        iTC_spi_send(register_array[i].register_index, register_array[i].register_data, register_array[i].len);
    }
}

void Board_HW_DriverClass::EPD_Gx_spi_send(unsigned char register_index, unsigned char *register_data, unsigned length)
{
    EPD_cs_low();
    EPD_spi_write(0x70);  // header of Register Index
    EPD_spi_write(register_index);
    EPD_cs_high();
    CS_H_L_Delay();
    EPD_cs_low();

    EPD_spi_write(0x72);  // header of Register Data of write command
    while (length--)
    {
        EPD_spi_write(*register_data++);
    }
    EPD_cs_high();
}
void Board_HW_DriverClass::EPD_Gx_spi_send_byte(uint8_t register_index, uint8_t register_data)
{
    EPD_cs_low();
    EPD_spi_write(0x70);  // header of Register Index
    EPD_spi_write(register_index);
    EPD_cs_high();
    CS_H_L_Delay();
    EPD_cs_low();
    EPD_spi_write(0x72);  // header of Register Data
    EPD_spi_write(register_data);
    EPD_cs_high();
}
uint8_t Board_HW_DriverClass::EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data)
{
    uint8_t result;
    EPD_cs_low();
    EPD_spi_write(0x70);  // header of Register Index
    EPD_spi_write(register_index);
    EPD_cs_high();
    CS_H_L_Delay();
    EPD_cs_low();

    EPD_spi_write(0x73);  // header of Register Data of read command
    result = EPD_spi_read(register_data);

    EPD_cs_high();

    return result;
}
uint8_t Board_HW_DriverClass::EPD_Gx_spi_rid(void)
{
    uint8_t result;
    EPD_cs_low();
    EPD_spi_write(0x71);
    result = EPD_spi_read(0x00);
    EPD_cs_high();
    return result;
}
void Board_HW_DriverClass::EPD_display_hardware_init(void)
{
    EPD_Vcc_turn_off();
    EPD_pwm_low();
    EPD_flash_cs_high();
    EPD_border_low();
    EPD_cs_low();
    EPD_rst_low();
    EPD_discharge_low();

}
//==============================================================================
//IIC Temperature

//IIC_IO_Assign_t IIC_IO;
//
//uint8_t inline getSDA()
//{
//    return input_get(IIC_IO.SDA_Pin);
//}
//void inline  TS_SDA_High()
//{
//    set_gpio_high(IIC_IO.SDA_Pin);
//}
//void inline  TS_SDA_Low()
//{
//    set_gpio_low(IIC_IO.SDA_Pin);
//}
//void inline  TS_SCL_High()
//{
//    set_gpio_high(IIC_IO.SCL_Pin);
//}
//void inline  TS_SCL_Low()
//{
//    set_gpio_low(IIC_IO.SCL_Pin);
//}
//void i2c_delay(void)
//{
//    int i = 1000;
//    while (i--);
//}
//void SDA_High(void)
//{
//    TS_SDA_High();
//    config_gpio_dir_i(IIC_IO.SDA_Pin);
//    i2c_delay();
//}
//void SDA_Low(void)
//{
//    config_gpio_dir_o(IIC_IO.SDA_Pin);
//    TS_SDA_Low();
//    i2c_delay();
//}
//void SCL_High(void)
//{
//    TS_SCL_High();
//    i2c_delay();
//}
//void SCL_Low(void)
//{
//    TS_SCL_Low();
//    i2c_delay();
//}
//void i2c_Init(void)
//{
//
//    config_gpio_dir_i(IIC_IO.SDA_Pin);
//
//    config_gpio_dir_o(IIC_IO.SCL_Pin);
//}
//
//uint8_t i2c_in_BYTE(void)
//{
//    uint8_t i_BYTE = 0, n;
//    SDA_High();
//    for (n = 0; n < 8; n++)
//    {
//        SCL_High();
//        i_BYTE <<= 1;
//        if (getSDA()) i_BYTE |= 1;
//        SCL_Low();
//    }
//    return i_BYTE;
//}
//void i2c_out_BYTE(uint8_t o_BYTE)
//{
//    uint8_t n;
//    for (n = 0; n < 8; n++)
//    {
//        if (o_BYTE & 0x80) SDA_High();
//        else SDA_Low();
//        SCL_High();
//        SCL_Low();
//        o_BYTE = o_BYTE << 1;
//    }
//}
//uint8_t i2c_ReadAck(void)
//{
//    uint8_t ack = 0;
//    SDA_High();
//    SCL_High();
//    ack = ~getSDA();
//    SCL_Low();
//    return ack;
//}
//void i2c_WriteAck(void)
//{
//    SDA_Low();
//    SCL_High();
//    SCL_Low();
//}
//void i2c_start(void)
//{
//    SDA_High();
//    SCL_High();
//    SDA_Low();
//    SCL_Low();
//}
//void i2c_stop(void)
//{
//    SCL_Low();
//    SDA_Low();
//    SCL_High();
//    SDA_High();
//}
//
//bool getTemperatureOne(int16_t *temp)
//{
//    bool flag = false;
//
//    i2c_Init();
//    i2c_start();
//    i2c_out_BYTE(IIC_Slave_address);
//    flag = i2c_ReadAck();
//    *temp = i2c_in_BYTE();
//    i2c_WriteAck();
//    i2c_in_BYTE();
//    i2c_stop();
//    if (!flag)*temp = 0xFF;
//    return flag;
//}
//
//bool DetectionTemperature(int16_t *temper)
//{
//    uint8_t i = 4;
//    bool flag = false;
//    getTemperatureOne(temper);
//    do
//    {
//        delay_ms(1);
//        if (getTemperatureOne(temper))
//        {
//            flag = true;
//            break;
//        }
//    }
//    while (i--);
//    if (*temper == 255)flag = false;
//    return flag;
//}

int16_t Board_HW_DriverClass::getTemperature(void)
{
    //bool flag = false;
    //int16_t temper;
    //
    //IIC_IO.SDA_Pin = TS_SDA0_PIN;
    //IIC_IO.SCL_Pin = TS_SCL0_PIN;
    //flag = DetectionTemperature(&temper);
    //
    //if (!flag)
    //{
    //    IIC_IO.SDA_Pin = TS_SDA1_PIN;
    //    IIC_IO.SCL_Pin = TS_SCL1_PIN;
    //    flag = DetectionTemperature(&temper);
    //}
    //else flag = true;
    //if (!flag)temper = 25;
    //return temper;
	return 25;
}

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

#ifndef BOARD_HW_DRIVER_H_
#define BOARD_HW_DRIVER_H_
//#include <Arduino.h>
//#include <inttypes.h>
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"


typedef struct Em_register_array
{
    uint8_t register_index;
    uint8_t len;
    uint8_t *register_data;
} Em_register_array_t;
//IIC Temperature
#define IIC_Slave_address           0x97

typedef struct
{
    uint8_t SDA_Pin;
    uint8_t SCL_Pin;
} IIC_IO_Assign_t;
//#define	config_gpio_dir_o(Pin)  		pinMode(Pin, OUTPUT) /**< set output direction for an IOPORT pin */
//#define	config_gpio_dir_i(Pin)  		pinMode(Pin,INPUT)  /**< set input direction for an IOPORT pin */
//#define	set_gpio_high(Pin)      		digitalWrite (Pin,HIGH) /**< set HIGH for an IOPORT pin */
//#define	set_gpio_low(Pin)       		digitalWrite (Pin,LOW)  /**< set LOW for an IOPORT pin */
//#define	input_get(Pin)          		(bool)(digitalRead (Pin ))   /**< get current value of an IOPORT pin */

// Pin must be declared as e.g.   {0, 6}
//typedef struct {
//	GPIO_Type* gpio;
//	uint8_t port;
//	uint8_t pin;
//} Pin_t;
#define BAD_PIN_VALUE                   100
#define IS_BAD(__a, __b) (((__a)==BAD_PIN_VALUE)||((__b)==BAD_PIN_VALUE))
#define	config_gpio_dir_i(PortPin)  do { gpio_pin_config_t p = {kGPIO_DigitalInput, 0U}; if (!IS_BAD(PortPin)) GPIO_PinInit(GPIO, PortPin, &p);}while(0)
#define	config_gpio_dir_o(PortPin)  do { gpio_pin_config_t p = {kGPIO_DigitalOutput, 0U}; if (!IS_BAD(PortPin)) GPIO_PinInit(GPIO, PortPin, &p);}while(0)
#define	set_gpio_high(PortPin)      do { uint8_t p[] = {PortPin}; if (!IS_BAD(PortPin)) GPIO_PortSet(GPIO, p[0], 1U << p[1]);}while(0)
#define	set_gpio_low(PortPin)       do { uint8_t p[] = {PortPin}; if (!IS_BAD(PortPin)) GPIO_PortClear(GPIO, p[0], 1U << p[1]);}while(0)
#define	input_get(PortPin)          (IS_BAD(PortPin) ? 0 : GPIO_ReadPinInput(GPIO, PortPin))

/******************************************************************************
* GPIO Defines
*****************************************************************************/
#define PIN_NOT_USED                    BAD_PIN_VALUE,BAD_PIN_VALUE

#define EPD_DB2_PIN              				PIN_NOT_USED  //1

//For Gen2 V1.0
#define TS_SDA0_PIN                 		PIN_NOT_USED  //5
#define TS_SCL0_PIN                 		PIN_NOT_USED  //6
//For Gen2 V1.1
#define TS_SDA1_PIN                 		PIN_NOT_USED  //6
#define TS_SCL1_PIN                 		PIN_NOT_USED  //5
#define SPICLK_PIN              				1,28  //7
#define EPD_BUSY_PIN            				1,30  //8
#define PWM_PIN                 				PIN_NOT_USED  //9
#define EPD_DC_PIN              				1,20  //PWM_PIN
#define EPD_RST_PIN             				1,23  //10
#define EPD_PANELON_PIN         				1,25  //11
#define EPD_DISCHARGE_PIN       			PIN_NOT_USED  //12  (should be 1,22 but it is not connected to the display)
#define EPD_BORDER_PIN          				PIN_NOT_USED  //13
#define EPD_DB1_PIN              				EPD_BORDER_PIN
#define SPIMISO_PIN             				PIN_NOT_USED  //14
#define SPIMOSI_PIN             				1,29  //15
#define Flash_CS_PIN            				PIN_NOT_USED  //18
#define EPD_CS_PIN              				1,21  //19
#define LED1_PIN            				  	PIN_NOT_USED  //43
#define BS1_PIN            				      1,24  //17

class Board_HW_DriverClass
{
public:
    Board_HW_DriverClass();
    void begin(); // Default
    void end();

    inline static void Config_LED1_Pin()
    {
        config_gpio_dir_o(LED1_PIN);
			//gpio_pin_config_t b = {kGPIO_DigitalOutput, 0U};
			//GPIO_PinInit(GPIO, LED1_PIN, &b);
    }
    inline static void LED1_high()
    {
        set_gpio_high(LED1_PIN);
    }
    inline static void LED1_low()
    {
        set_gpio_low(LED1_PIN);
    }

    inline static void Config_Busy_Pin()
    {
        config_gpio_dir_i(EPD_BUSY_PIN);
    }
    inline static bool EPD_IsBusy()
    {
        return (bool)input_get(EPD_BUSY_PIN);
    }

    inline static void Config_EPD_cs_Pin()
    {
        config_gpio_dir_o(EPD_CS_PIN);
    }
    inline static void EPD_cs_high()
    {
			GPIO_PinWrite(GPIO, 0, 17, 1);
        set_gpio_high(EPD_CS_PIN);
    }
    inline static void EPD_cs_low()
    {
			GPIO_PinWrite(GPIO, 0, 17, 0);
        set_gpio_low(EPD_CS_PIN);
    }

    inline static void Config_EPD_flash_cs_Pin()
    {
        config_gpio_dir_o(Flash_CS_PIN);
    }
    inline static void EPD_flash_cs_high()
    {
        set_gpio_high(Flash_CS_PIN);
    }
    inline static void EPD_flash_cs_low()
    {
        set_gpio_low(Flash_CS_PIN);
    }

    inline static void Config_EPD_rst_Pin()
    {
        config_gpio_dir_o(EPD_RST_PIN);
    }
    inline static void EPD_rst_high()
    {
        set_gpio_high(EPD_RST_PIN);
    }
    inline static void EPD_rst_low()
    {
        set_gpio_low(EPD_RST_PIN);
    }

    inline static void Config_EPD_discharge_Pin()
    {
        config_gpio_dir_o(EPD_DISCHARGE_PIN);
    }
    inline static void EPD_discharge_high()
    {
        set_gpio_high(EPD_DISCHARGE_PIN);
    }
    inline static void EPD_discharge_low()
    {
        set_gpio_low(EPD_DISCHARGE_PIN);
    }

    inline static void Config_EPD_panelon_Pin()
    {
        config_gpio_dir_o(EPD_PANELON_PIN);
    }
    inline static void EPD_Vcc_turn_on()
    {
        set_gpio_high(EPD_PANELON_PIN);
    }
    inline static void EPD_Vcc_turn_off()
    {
        set_gpio_low(EPD_PANELON_PIN);
    }

    inline static void Config_EPD_border_Pin()
    {
        config_gpio_dir_o(EPD_BORDER_PIN);
    }
    inline static void EPD_border_high()
    {
        set_gpio_high(EPD_BORDER_PIN);
    }
    inline static void EPD_border_low()
    {
        set_gpio_low(EPD_BORDER_PIN);
    }

    inline static void Config_EPD_pwm_Pin()
    {
        config_gpio_dir_o(PWM_PIN);
    }
    inline static void EPD_pwm_high()
    {
        set_gpio_high(PWM_PIN);
    }
    inline static void EPD_pwm_low()
    {
        set_gpio_low(PWM_PIN);
    }

    inline static void SPIMISO_low()
    {
        set_gpio_low(SPIMISO_PIN);
    }
    inline static void SPIMOSI_low()
    {
        set_gpio_low(SPIMOSI_PIN);
    }
    inline static void SPICLK_low()
    {
        set_gpio_low(SPICLK_PIN);
    }

    inline static void Config_EPD_DC_Pin()
    {
        config_gpio_dir_o(EPD_DC_PIN);
    }


    inline static void EPD_DC_high()
    {
        set_gpio_high(EPD_DC_PIN);
    }
    inline static void EPD_DC_low()
    {
        set_gpio_low(EPD_DC_PIN);
    }
    inline static void Config_EPD_BS1_Pin()
    {
        config_gpio_dir_o(BS1_PIN);
    }
    inline static void EPD_BS1_high()
    {
        set_gpio_high(BS1_PIN);
    }
    inline static void EPD_BS1_low()
    {
        set_gpio_low(BS1_PIN);
    }
    inline static void Config_EPD_DB1_Pin()
    {
        config_gpio_dir_i(EPD_DB1_PIN);
    }
    inline static bool Get_EPD_DB1()
    {
        return (bool)input_get(EPD_DB1_PIN);
    }

    inline static void Config_EPD_DB2_Pin()
    {
        config_gpio_dir_i(EPD_DB2_PIN);
    }
    inline static bool Get_EPD_DB2()
    {
        return (bool)input_get(EPD_DB2_PIN);
    }

#define delay(__ms)    vTaskDelay((__ms) / portTICK_PERIOD_MS)
#define delay_ms(x)  delay(x)
    inline static void EPD_delay_ms(unsigned int ms)
    {
        delay(ms);
    }

    uint32_t getnowtime(void);

    void start_EPD_timer(void);
    void stop_EPD_timer(void);
    uint32_t get_EPD_time_tick(void);


    void EPD_spi_attach(void);
    void EPD_spi_detach(void);
    bool check_flash_spi(void);
    uint8_t EPD_spi_read(uint8_t data);
    void EPD_spi_write(uint8_t data);

    void iTC_spi_sendReg(uint8_t register_index);
    void iTC_spi_sendRegData(uint8_t register_data);
    void iTC_spi_send(uint8_t register_index, uint8_t *register_data, uint8_t len);
    void iTC_spi_send_array(Em_register_array_t *register_array, uint8_t len);

    void EPD_Gx_spi_send(unsigned char register_index, unsigned char *register_data, unsigned Length);
    void EPD_Gx_spi_send_byte(uint8_t register_index, uint8_t register_data);
    uint8_t EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data);
    uint8_t EPD_Gx_spi_rid(void);

    void EPD_display_hardware_init(void);
    void PWM_run(uint16_t time);

    int16_t getTemperature(void);
private:
};




#endif /* BOARD_HW_DRIVER_H_ */

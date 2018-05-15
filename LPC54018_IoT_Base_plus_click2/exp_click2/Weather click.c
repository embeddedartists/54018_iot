/**************************************************************************************************
* File: Weather click.c
* File Type: C - Source Code File
* Project Name: Weather click
* Company: (c) mikroElektronika, 2015
* Revision History:
*       - initial release (VM);
* Description:
*Weather click carries the BME280 integrated environmental unit from Bosch.
*It’s a sensor that detects humidity, pressure and temperature, specifically designed for low current consumption and long term stability.
*Weather click can communicate with the target MCU either through mikroBUS™ SPI or I2C interfaces. 
*The board is designed to use a 3.3V power supply.
* Test configuration:
*    MCU:             STM32F107VG
*                     http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/DM00037051.pdf
*    dev.board:       EasyMx PRO for STM32
*                     http://www.mikroe.com/eng/products/view/869/mikromedia-for-stm32-m4/
*    Oscillator:      HSI-PLL, 72.000MHz
*    EXT:             Weather click:
*                      http://www.mikroe.com/click/weather
*    SW:              mikroC PRO for ARM
*                     http://www.mikroe.com/eng/products/view/752/mikroc-pro-for-arm/
* NOTES:
*     I2C bus is used for communication with the click.
*/

#include "BME280_Driver.h"
#include "BME280_Defs.h"
#include "resources.h"



// TFT module connections
unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;
// End TFT module connections

char tmp;
char text[20];
float tmp_f;


static void MCU_Init() {
  I2C1_Init_Advanced(400000, &_GPIO_MODULE_I2C1_PB67);   // Initialize I2C on pins PB6 and PB7
  delay_ms(200);
}

static void Display_Init(){
  TFT_Set_Default_Mode();
  TFT_Init_ILI9341_8bit(320, 240);
  TFT_BLED = 1;
  TFT_Fill_Screen(CL_WHITE);
  TFT_Set_Pen(CL_BLACK, 1);
  TFT_Line(20, 220, 300, 220);
  TFT_Line(20,  46, 300,  46);
  TFT_Set_Font(&HandelGothic_BT21x22_Regular, CL_BLACK, FO_HORIZONTAL);
  TFT_Write_Text("Weather click demo", 42, 14);
   TFT_Set_Font(&Verdana12x13_Regular, CL_BLACK, FO_HORIZONTAL);
  TFT_Write_Text("EasyMx PRO v7 for STM32", 19, 223);
  TFT_Write_Text("www.mikroe.com", 200, 223);
}


static void Display_Values() {
  tmp_f = BME280_GetTemperature();
   TFT_Set_Pen(CL_WHITE, 1);
   TFT_Set_Brush(1, CL_WHITE,0,0,0,0);
  FloatToStr(tmp_f, text);
  TFT_Rectangle(180,50,320,70);
  TFT_Write_Text(text,200,50);

  tmp_f = BME280_GetPressure();
  FloatToStr(tmp_f, text);
  TFT_Rectangle(180,110,320,130);
  TFT_Write_Text(text,200,110);

  tmp_f = BME280_GetHumidity();
  FloatToStr(tmp_f, text);
  TFT_Rectangle(180,80,320,100);
  TFT_Write_Text(text,200,80);

}

void BME280_INIT() {
      BME280_SetStandbyTime(BME280_STANDBY_TIME_1_MS);                              // Standby time 1ms
  BME280_SetFilterCoefficient(BME280_FILTER_COEFF_16);                          // IIR Filter coefficient 16
  BME280_SetOversamplingPressure(BME280_OVERSAMP_16X);                          // Pressure x16 oversampling
  BME280_SetOversamplingTemperature(BME280_OVERSAMP_2X);                        // Temperature x2 oversampling
  BME280_SetOversamplingHumidity(BME280_OVERSAMP_1X);                           // Humidity x1 oversampling
  BME280_SetOversamplingMode(BME280_NORMAL_MODE);
}

void main() {
  MCU_Init();
  Display_Init();
  delay_ms(2000);
  TFT_Fill_Screen(CL_WHITE);
  delay_ms(200);
  tmp = BME280_GetID();
  if (tmp != BME280_CHIP_ID) {
    TFT_Write_Text("CHIP ERROR",10,10);
    while (1); //stop program
  }else{
    TFT_Set_Font(&HandelGothic_BT21x22_Regular, CL_RED, FO_HORIZONTAL);
    TFT_Write_Text("Temperature [C]",10,50);
     TFT_Set_Font(&HandelGothic_BT21x22_Regular, CL_NAVY, FO_HORIZONTAL);
    TFT_Write_Text("Humidity [%RH]",10,80);
     TFT_Set_Font(&HandelGothic_BT21x22_Regular, CL_BLACK, FO_HORIZONTAL);
    TFT_Write_Text("Pressure [hPa]",10,110);                                     //hPa = mBar
  }

  delay_ms(200);
  BME280_ReadCalibrationParams();                                               //Read calibration parameters
  BME280_SetOversamplingPressure(BME280_OVERSAMP_1X);
  BME280_SetOversamplingTemperature(BME280_OVERSAMP_1X);
  BME280_SetOversamplingHumidity(BME280_OVERSAMP_1X);
  BME280_SetOversamplingMode(BME280_FORCED_MODE);
  
  while(BME280_IsMeasuring());
  BME280_ReadMeasurements();
  
  BME280_INIT();
  
  while(1) {
     while(BME280_IsMeasuring());
     BME280_ReadMeasurements();
     Display_Values();
     BME280_INIT();
     delay_ms(1500);
  }
  
}
/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
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


/* Glossary of Acronyms
 * LUT = Look-up table, the array to define the parameters of driving waveform 
 */

#include "iTC_Engine.h"
static const uint8_t *LUTFile = NULL;
static long LUTAddress = ADDRESS_NULL;
static uint8_t LUTCmd;
static ColorMode_t cur_ColorMode;
static int8_t cur_temper;
static ImageData_handler _OnImageData_handler = NULL;
static ImageData_handler _OnImageDataPU_handler = NULL;
static EPD_read_memory_handler _OnReadExternalMemory = NULL;
void iTC_EngineClass::readLUTData(uint8_t *outputData, uint8_t len)
{
    if(LUTFile != NULL)
    {
        memcpy(outputData, LUTFile, len);
        LUTFile += len;
    }
    else if(LUTAddress != ADDRESS_NULL)
    {
        if(_OnReadExternalMemory != NULL)_OnReadExternalMemory(LUTAddress, outputData, len);
        LUTAddress += len;
    }
}
// iCMD means commands for iTC, Cr = commands for Spectra, TP = commands for temperature
// IO_Ctrl = commands for ontrolling GPIO of IO_Define_t, image = commands for sending image data
uint8_t iTC_EngineClass::decod_cmd(void)
{
    int16_t x, y, Horizontal = 0;
    iTC_delay_param_t iTC_delay_param;
    iTC_IO_param_t iTC_IO_param;
    iTC_Reg_TP_t iTC_Reg_TP;
    iTC_Reg_Cr_TP_t iTC_Reg_Cr_TP;
    iTC_Reg_Cr_t iTC_Reg_Cr;
    iTC_Reg_data_t iTC_Reg_data;
    iTC_Reg_Temper_t iTC_Reg_Temper;
    iTC_Busy_param_t iTC_Busy_param;
    uint8_t flag = RES_OK, tmp;
    iTC_Reg_Image_t iTC_Reg_Image;
    uint8_t *Pixel_Data;
    readLUTData(&LUTCmd, 1);
    switch(LUTCmd)
    {
        case iCMD_iTC_SPI:
            readLUTData((uint8_t *)&iTC_Reg_data, RegData_Header);
            if(iTC_Reg_data.DataLen > 0)
            {
                iTC_Reg_data.reg_data = (uint8_t *)malloc(iTC_Reg_data.DataLen);
                readLUTData(iTC_Reg_data.reg_data, iTC_Reg_data.DataLen);
            }
            iTC_spi_send(iTC_Reg_data.regIndex_cmd, iTC_Reg_data.reg_data, iTC_Reg_data.DataLen);

            if(iTC_Reg_data.DataLen > 0)	free(iTC_Reg_data.reg_data);

            break;
        case iCMD_SetTemper:
            readLUTData((uint8_t *)&iTC_Reg_Temper, RegTemper_Header);
            if(iTC_Reg_Temper.DataLen > 0)
            {
                iTC_Reg_Temper.reg_data = (uint8_t *)malloc(iTC_Reg_Temper.DataLen);
                readLUTData(iTC_Reg_Temper.reg_data, iTC_Reg_Temper.DataLen);
                iTC_Reg_Temper.reg_data[0] = cur_temper;
                iTC_Reg_Temper.reg_data[1] = 0;
            }
            iTC_spi_send(iTC_Reg_Temper.regIndex_cmd, iTC_Reg_Temper.reg_data, iTC_Reg_Temper.DataLen);

            if(iTC_Reg_Temper.DataLen > 0)	free(iTC_Reg_Temper.reg_data);

            break;
        case iCMD_iTC_SPI_Cr:
            readLUTData((uint8_t *)&iTC_Reg_Cr, RegCr_Header);
            if(iTC_Reg_Cr.DataLen > 0)
            {
                iTC_Reg_Cr.reg_data = (uint8_t *)malloc(iTC_Reg_Cr.DataLen);
                readLUTData(iTC_Reg_Cr.reg_data, iTC_Reg_Cr.DataLen);
            }
            if(iTC_Reg_Cr.CrMode == cur_ColorMode || iTC_Reg_Cr.CrMode == CM_ALL)iTC_spi_send(iTC_Reg_Cr.regIndex_cmd, iTC_Reg_Cr.reg_data, iTC_Reg_Cr.DataLen);

            if(iTC_Reg_Cr.DataLen > 0)free(iTC_Reg_Cr.reg_data);

            break;
        case iCMD_iTC_SPI_TP:
            readLUTData((uint8_t *)&iTC_Reg_TP, RegTP_Header);
            if(iTC_Reg_TP.DataLen > 0)
            {
                iTC_Reg_TP.reg_data = (uint8_t *)malloc(iTC_Reg_TP.DataLen);
                readLUTData(iTC_Reg_TP.reg_data, iTC_Reg_TP.DataLen);
                if(iTC_Reg_TP.Tmin == sig_TP_Empty)
                {
                    if(iTC_Reg_TP.Tmax > cur_temper)
                    {
                        iTC_spi_send(iTC_Reg_TP.regIndex_cmd, iTC_Reg_TP.reg_data, iTC_Reg_TP.DataLen);
                    }
                }
                else if(iTC_Reg_TP.Tmax == sig_TP_Empty)
                {
                    if(cur_temper >= iTC_Reg_TP.Tmin)
                    {
                        iTC_spi_send(iTC_Reg_TP.regIndex_cmd, iTC_Reg_TP.reg_data, iTC_Reg_TP.DataLen);
                    }
                }
                else if(iTC_Reg_TP.Tmin == sig_TP_Empty && iTC_Reg_TP.Tmax == sig_TP_Empty)
                {
                    iTC_spi_send(iTC_Reg_TP.regIndex_cmd, iTC_Reg_TP.reg_data, iTC_Reg_TP.DataLen);
                }
                else
                {
                    if(iTC_Reg_TP.Tmax > cur_temper && cur_temper >= iTC_Reg_TP.Tmin)
                    {
                        iTC_spi_send(iTC_Reg_TP.regIndex_cmd, iTC_Reg_TP.reg_data, iTC_Reg_TP.DataLen);
                    }
                }
                free(iTC_Reg_TP.reg_data);
            }
            break;
        case iCMD_iTC_SPI_Cr_TP :
            readLUTData((uint8_t *)&iTC_Reg_Cr_TP, RegCrTP_Header);
            if(iTC_Reg_Cr_TP.DataLen > 0)
            {
                iTC_Reg_Cr_TP.reg_data = (uint8_t *)malloc(iTC_Reg_Cr_TP.DataLen);
                readLUTData(iTC_Reg_Cr_TP.reg_data, iTC_Reg_Cr_TP.DataLen);
                if(iTC_Reg_Cr_TP.CrMode == cur_ColorMode || iTC_Reg_Cr_TP.CrMode == CM_ALL)
                {
                    if(iTC_Reg_Cr_TP.Tmin == sig_TP_Empty && iTC_Reg_Cr_TP.Tmax == sig_TP_Empty)
                    {
                        iTC_spi_send(iTC_Reg_Cr_TP.regIndex_cmd, iTC_Reg_Cr_TP.reg_data, iTC_Reg_Cr_TP.DataLen);
                    }
                    else if(iTC_Reg_Cr_TP.Tmin == sig_TP_Empty)
                    {
                        if(iTC_Reg_Cr_TP.Tmax > cur_temper)
                        {
                            iTC_spi_send(iTC_Reg_Cr_TP.regIndex_cmd, iTC_Reg_Cr_TP.reg_data, iTC_Reg_Cr_TP.DataLen);
                        }
                    }
                    else if(iTC_Reg_Cr_TP.Tmax == sig_TP_Empty)
                    {
                        if(cur_temper >= iTC_Reg_Cr_TP.Tmin)
                        {
                            iTC_spi_send(iTC_Reg_Cr_TP.regIndex_cmd, iTC_Reg_Cr_TP.reg_data, iTC_Reg_Cr_TP.DataLen);
                        }
                    }
                    else
                    {
                        if(iTC_Reg_Cr_TP.Tmax > cur_temper && cur_temper >= iTC_Reg_Cr_TP.Tmin)
                        {
                            iTC_spi_send(iTC_Reg_Cr_TP.regIndex_cmd, iTC_Reg_Cr_TP.reg_data, iTC_Reg_Cr_TP.DataLen);
                        }
                    }

                }

                free(iTC_Reg_Cr_TP.reg_data);
            }
            break;
        case iCMD_Busy:
            readLUTData((uint8_t *)&iTC_Busy_param, sizeof(iTC_Busy_param));
            start_EPD_timer();
            x = 0;
            do
            {
                if(EPD_IsBusy() == iTC_Busy_param.compare_data) x++;
                if(get_EPD_time_tick() > iTC_Busy_param.time)
                {
                    flag = ERROR_BUSY;
                    break;
                }
            }
            while(x < 32);
            stop_EPD_timer();
            break;
        case iCMD_IO_Ctrl:
            readLUTData((uint8_t *)&iTC_IO_param, sizeof(iTC_IO_param_t));
            switch(iTC_IO_param.io_pin)
            {
                case io_Panel_on:
                    if(iTC_IO_param.io_data) EPD_Vcc_turn_on();
                    else EPD_Vcc_turn_off();
                    break;
                case io_Res:
                    if(iTC_IO_param.io_data) EPD_rst_high();
                    else EPD_rst_low();
                    break;
                case io_CS:
                    if(iTC_IO_param.io_data)
                    {
                        EPD_cs_high();
                        EPD_flash_cs_high();
                    }
                    else
                    {
                        EPD_cs_low();
                        EPD_flash_cs_high();
                    }
                    break;
                case io_DC:
                    if(iTC_IO_param.io_data)
                    {
                        EPD_DC_high();
                    }
                    else
                    {
                        EPD_DC_low();
                    }
                    break;
                case io_discharge:
                    if(iTC_IO_param.io_data)
                    {
                        EPD_discharge_high();
                    }
                    else
                    {
                        EPD_discharge_low();
                    }
                    break;
                case io_SPI_Pin:
                    if(iTC_IO_param.io_data)
                    {
                        EPD_spi_attach();
                    }
                    else
                    {
                        EPD_spi_detach();
                    }
                    break;
                case io_All:
                    if(iTC_IO_param.io_data)
                    {
                        EPD_cs_high();
                        EPD_flash_cs_high();
                        EPD_rst_high();
                        EPD_Vcc_turn_on();
                    }
                    else
                    {
                        EPD_Vcc_turn_off();
                        EPD_rst_low();
                        EPD_discharge_low();
                        EPD_DC_low();
                        EPD_flash_cs_high();
                    }
                    break;
            }
            break;
        case iCMD_Delay:
            readLUTData((uint8_t *)&iTC_delay_param, sizeof(iTC_delay_param));
            EPD_delay_ms(iTC_delay_param.time);
            break;
        case iCMD_Image:

            readLUTData((uint8_t *)&iTC_Reg_Image, sizeof(iTC_Reg_Image));
            if((iTC_Reg_Image.CrMode != cur_ColorMode) && (iTC_Reg_Image.CrMode != CM_ALL)) break;
            if(_OnImageData_handler == NULL) break;
            iTC_spi_sendReg(iTC_Reg_Image.regIndex_cmd);
            Horizontal = (int16_t)(iTC_Reg_Image.Horizontal / 8);
            Pixel_Data = (uint8_t *)malloc(iTC_Reg_Image.pixel_bit);
            for(y = 0; y < iTC_Reg_Image.Vertical; y++)
            {
                for(x = 0; x < Horizontal; x++)
                {
                    if(iTC_Reg_Image.UseInternalData)
                    {
                        if(iTC_Reg_Image.pixel_bit == 1)iTC_spi_sendRegData(iTC_Reg_Image.InternalData);
                        else if(iTC_Reg_Image.pixel_bit == 2)
                        {

                            for(tmp = 0; tmp < iTC_Reg_Image.pixel_bit; tmp++)
                            {
                                iTC_spi_sendRegData(iTC_Reg_Image.InternalData);
                            }
                        }
                    }
                    else
                    {
                        _OnImageData_handler(Pixel_Data, 1, iTC_Reg_Image.pixel_bit);
                        for(tmp = 0; tmp < iTC_Reg_Image.pixel_bit; tmp++)
                        {
                            iTC_spi_sendRegData(Pixel_Data[tmp]);
                        }

                    }
                }
            }
            EPD_cs_high();
            free(Pixel_Data);
            break;
        case iCMD_Image_PU:
            readLUTData((uint8_t *)&iTC_Reg_Image, sizeof(iTC_Reg_Image));
            if((iTC_Reg_Image.CrMode != cur_ColorMode) && (iTC_Reg_Image.CrMode != CM_ALL)) break;
            if(_OnImageDataPU_handler == NULL) break;
            iTC_spi_sendReg(iTC_Reg_Image.regIndex_cmd);
            Horizontal = (int16_t)(iTC_Reg_Image.Horizontal / 8);
            Pixel_Data = (uint8_t *)malloc(iTC_Reg_Image.pixel_bit);
            for(y = 0; y < iTC_Reg_Image.Vertical; y++)
            {
                for(x = 0; x < Horizontal; x++)
                {
                    if(iTC_Reg_Image.UseInternalData)
                    {
                        if(iTC_Reg_Image.pixel_bit == 1)iTC_spi_sendRegData(iTC_Reg_Image.InternalData);
                        else if(iTC_Reg_Image.pixel_bit == 2)
                        {

                            for(tmp = 0; tmp < iTC_Reg_Image.pixel_bit; tmp++)
                            {
                                iTC_spi_sendRegData(iTC_Reg_Image.InternalData);
                            }
                        }
                    }
                    else
                    {

                        _OnImageDataPU_handler(Pixel_Data, 1, iTC_Reg_Image.pixel_bit);
                        for(tmp = 0; tmp < iTC_Reg_Image.pixel_bit; tmp++)
                        {
                            iTC_spi_sendRegData(Pixel_Data[tmp]);
                        }

                    }
                }
            }
            EPD_cs_high();
            free(Pixel_Data);
            break;
        case iCMD_END:

            break;
        default:
            flag = RES_Fail;
            break;
    }
    return flag;
}

void iTC_EngineClass::SetPU_ImageDataHandle(ImageData_handler OnImageDataPU_handler)
{
    _OnImageDataPU_handler = OnImageDataPU_handler;
}
uint8_t iTC_EngineClass::Ex_RunEngine(long ExtenalAddress)
{
    uint8_t RES = RES_OK;
    LUTFile = NULL;
    LUTAddress = ExtenalAddress;
    do
    {
        RES = decod_cmd();
        if(RES != RES_OK) break;
    }
    while(LUTCmd != iCMD_END);
    return  RES;
}

uint8_t iTC_EngineClass::RunEngine(const void *runLUTFile)
{
    uint8_t RES = RES_OK;
    if(runLUTFile == NULL) return RES_OK;
    LUTAddress = ADDRESS_NULL;
    LUTFile = (const uint8_t *)runLUTFile;
    do
    {
        RES = decod_cmd();
        if(RES != RES_OK) break;
    }
    while(LUTCmd != iCMD_END);
    return  RES;
}
void iTC_EngineClass::iTC_Engine_init(ColorMode_t cr, int8_t temper, ImageData_handler OnImageData_handler, EPD_read_memory_handler OnReadExternalMemory)
{
    _OnImageData_handler = OnImageData_handler;
    _OnReadExternalMemory = OnReadExternalMemory;
    cur_ColorMode = cr;
    cur_temper = temper;

}

static const uint8_t *ImageData = NULL;
static long ExImageData = ADDRESS_NULL;
static EPD_read_memory_handler _On_EPD_read_flash;
static const iTC_WaveformLUT_t *iTC_GU_LUT, *iTC_PU_LUT, *iTC_OTP_LUT;
static OperationMode_t OperationMode;
//static uint8_t *CImageData = NULL, *PImageData = NULL;
//static long ExCImageData = ADDRESS_NULL, ExPImageData = ADDRESS_NULL;

// Not available yet for partial update
//static void iTC_ReadLineData_PU_Handle(uint8_t *LineData, uint16_t len, uint8_t PixelBits)
//{
//
//}

static void iTC_ReadLineData_Handle(uint8_t *LineData, uint16_t len, uint8_t PixelBits)
{
    if(PixelBits == 1)
    {
        if(ImageData != NULL)
        {
            memcpy(LineData, (uint8_t *)ImageData, len);
            ImageData += len;
        }
        else if(ExImageData != ADDRESS_NULL)
        {
            _On_EPD_read_flash(ExImageData, LineData, len);
            ExImageData += len;
        }
        else
        {
            memset(LineData, 0x00, len);
        }
    }
    else if(PixelBits == 2)
    {
        uint8_t tmp;
        const uint8_t DTM1ConvertArray[] = {0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x3f, 0xc0, 0xc3, 0xcc, 0xcf, 0xf0, 0xf3, 0xfc, 0xff};
        if(ImageData != NULL)
        {
            memcpy(LineData, ImageData, len);
            ImageData += len;

        }
        else if(ExImageData != ADDRESS_NULL)
        {
            _On_EPD_read_flash(ExImageData, LineData, len);
            ExImageData += len;

        }
        if(PixelBits == 2)
        {
            tmp = *LineData;
            *LineData = DTM1ConvertArray[tmp >> 4];
            LineData++;
            *LineData = DTM1ConvertArray[tmp & 0x0f];
        }
    }
}

// Not available yet for partial update
void iTC_EngineClass::iTC_Display_PU_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr, uint16_t PU_Time)
{

}

// Not available yet for partial update
void iTC_EngineClass::iTC_Display_PU_From_Flash(long previous_image_flash_address, long new_image_flash_address, EPD_read_memory_handler On_EPD_read_flash, uint16_t PU_Time)
{

}

void iTC_EngineClass::iTC_IO_Config(void)
{
    Config_Busy_Pin();
    Config_EPD_cs_Pin();
    Config_EPD_rst_Pin();
    Config_EPD_panelon_Pin();
    Config_EPD_discharge_Pin();
    Config_EPD_border_Pin();
    Config_EPD_flash_cs_Pin();
    EPD_spi_attach();
    Config_EPD_DC_Pin();
    Config_EPD_DB1_Pin();
    Config_EPD_DB2_Pin();
    EPD_Vcc_turn_off();
    EPD_rst_low();
    EPD_discharge_low();
    EPD_DC_low();
    EPD_flash_cs_high();
}

void iTC_EngineClass::iTC_power_on(uint8_t EPD_type_index, int8_t temperature, OperationMode_t operation_mode, const iTC_WaveformLUT_t *GU_LUT, const iTC_WaveformLUT_t *OTP_LUT, const iTC_WaveformLUT_t *PU_LUT)
{
    iTC_GU_LUT = GU_LUT;
    iTC_OTP_LUT = OTP_LUT;
    iTC_PU_LUT = PU_LUT;
    ColorMode_t mode = CM_Monochrome;
    switch(EPD_type_index)
    {
        case EPD_287_BWR:
        case EPD_420_BWR:
        case EPD_266_BWR:
            mode = CM_Color;
            break;
    }
    iTC_Engine_init(mode, temperature, iTC_ReadLineData_Handle, _On_EPD_read_flash);
    switch(operation_mode)
    {
        case GU_Mode:
            RunEngine(iTC_GU_LUT->PowerOn_LUT);
            break;
        case OTP_Mode:
            RunEngine(iTC_OTP_LUT->PowerOn_LUT);
            break;
        case PU_Mode:
            RunEngine(iTC_PU_LUT->PowerOn_LUT);
            break;
        default:

            break;
    }
}

uint8_t iTC_EngineClass::iTC_initialize_driver(OperationMode_t operation_mode)
{
    uint8_t RES = RES_OK;
    OperationMode = operation_mode;
    if(OperationMode == OTP_Mode)RES = RunEngine(iTC_OTP_LUT->Initial_LUT);
    else if(OperationMode == PU_Mode)RES = RunEngine(iTC_PU_LUT->Initial_LUT);
    else RES = RunEngine(iTC_GU_LUT->Initial_LUT);
    if(RES != RES_OK) RunEngine(iTC_GU_LUT->ExceptionLUT);
    return RES;
}

uint8_t iTC_EngineClass::iTC_Display_from_Ram(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr)
{
    uint8_t RES = RES_OK;
    ImageData = new_image_ptr;
    ExImageData = ADDRESS_NULL;
    if(OperationMode == OTP_Mode)RES = RunEngine(iTC_OTP_LUT->Update_LUT);
    else if(OperationMode == PU_Mode)RES = RunEngine(iTC_PU_LUT->Update_LUT);
    else RES = RunEngine(iTC_GU_LUT->Update_LUT);
    return RES;
}

uint8_t iTC_EngineClass::iTC_Display_from_flash(long previous_image_flash_address, long new_image_flash_address, EPD_read_memory_handler On_EPD_read_flash)
{
    uint8_t RES = RES_OK;
    ImageData = NULL;
    _On_EPD_read_flash = On_EPD_read_flash;
    ExImageData = new_image_flash_address;
    if(OperationMode == OTP_Mode)RES = RunEngine(iTC_OTP_LUT->Update_LUT);
    else if(OperationMode == PU_Mode)RES = RunEngine(iTC_PU_LUT->Update_LUT);
    else RES = RunEngine(iTC_GU_LUT->Update_LUT);
    return RES;
}

uint8_t iTC_EngineClass::iTC_power_off()
{
    uint8_t RES = RES_OK;
    if(OperationMode == OTP_Mode)RES = RunEngine(iTC_OTP_LUT->PowerOffLUT);
    else if(OperationMode == PU_Mode)RES = RunEngine(iTC_GU_LUT->PowerOffLUT);
    else RES = RunEngine(iTC_GU_LUT->PowerOffLUT);
    return RES;
}




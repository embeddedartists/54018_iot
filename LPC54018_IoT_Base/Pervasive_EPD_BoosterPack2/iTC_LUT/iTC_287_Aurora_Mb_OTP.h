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
#ifndef _ITC_287_AURORA_MB_OTP_H_
#define _ITC_287_AURORA_MB_OTP_H_

const iTC_WaveformLUT_t iTC_287Mb_OTP_LUT =
{
    (const uint8_t []) //Power on LUT
    {
        iCMD_IO_Ctrl, io_All, 0,    //all pin =0
        iCMD_IO_Ctrl, io_Panel_on, 1, //Turn-on VCC / VDD
        iCMD_Delay, 0x05, 0x00,     //Delay 5ms
        iCMD_IO_Ctrl, io_Res, 1,    //RES=1
        iCMD_Delay, 0x01, 0x00,     //Delay 1ms
        iCMD_IO_Ctrl, io_CS, 1,     //CS=1
        iCMD_IO_Ctrl, io_SPI_Pin, 1, //spi attach
        iCMD_END
    },
    (const uint8_t []) //Initial LUT
    {
        iCMD_SetTemper           , 0xe5, 0x01, 0x1a,  		      //SPI(e5,T)
        iCMD_iTC_SPI	         , 0xe0, 1, 0x02,                //Active Temperature
        iCMD_iTC_SPI	         , 0x00, 1, 0x9f,                //Panel Settings
        iCMD_iTC_SPI	         , 0x06, 3, 0x17, 0x17, 0x17,    //Booster soft start settings
        iCMD_iTC_SPI	         , 0x61, 3, 0x80, 0x01, 0x28,    	 //Resolution settnigs
        iCMD_iTC_SPI	         , 0x50, 1, 0x47,                //Vcom and data interval setting
        iCMD_iTC_SPI	         , 0xe3, 1, 0x88,
        iCMD_END
    },
    (const uint8_t []) //Input image update
    {
        iCMD_Image, CM_Monochrome, true	, 0x00	, 1, 0x10, 0x80, 0x00, 0x28, 0x01,
        iCMD_Image, CM_Monochrome, false 	, 0x00	, 1, 0x13, 0x80, 0x00, 0x28, 0x01,
        iCMD_Busy				, 0x01	, 0xE8	, 0x03,
        iCMD_iTC_SPI			, 0x04	, 0,
        iCMD_Busy				, 0x01   , 0xE8   , 0x03,
        iCMD_iTC_SPI			, 0x12	, 0		,
        iCMD_END
    },
    (const uint8_t []) //Power off
    {
        iCMD_Busy				, 0x01   , 0x30   , 0x75,
        iCMD_iTC_SPI			, 0x02, 0 ,
        iCMD_Busy				, 0x01   , 0x64   , 0x00,
        iCMD_IO_Ctrl			, io_All , 0,
        iCMD_IO_Ctrl			, io_SPI_Pin, 0,
        iCMD_IO_Ctrl			, io_discharge, 1,
        iCMD_END
    }
    ,
    (const uint8_t []) //ExceptionL
    {
        iCMD_IO_Ctrl			, io_discharge, 1,
        iCMD_IO_Ctrl			, io_SPI_Pin, 0,
        iCMD_IO_Ctrl			, io_All, 0,
        iCMD_END
    }
};


#endif /*_ITC_287_AURORA_MB_OTP_H_*/


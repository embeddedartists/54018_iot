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

#ifndef _ITC_420_AURORA_MB_OTP_H_
#define _ITC_420_AURORA_MB_OTP_H_



const iTC_WaveformLUT_t iTC_420Mb_OTP_LUT =
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
        iCMD_SetTemper                  , 0xe5, 0x01, 0x1a,  		     // SPI(e5,T)
        iCMD_iTC_SPI	                , 0xe0, 1, 0x02,                //Active Temperature
        iCMD_iTC_SPI	                , 0x00, 1, 0x0f,                //Panel Settings
        iCMD_iTC_SPI	                , 0x06, 3, 0x17, 0x17, 0x27,    //Booster soft start settings
        iCMD_iTC_SPI	                , 0x61, 4, 0x01, 0x90, 0x01, 0x2c, //Resolution settnigs
        iCMD_iTC_SPI	                , 0x50, 1, 0x87,                //Vcom and data interval setting
        iCMD_iTC_SPI	                , 0x3, 1, 0x88,                 //Power Saving
        iCMD_END
    },
    (const uint8_t []) //Input image update
    {
        iCMD_Busy				        , 0x01   , 0xE8   , 0x0f,
        iCMD_Image      , CM_Monochrome  , false	, 0x00	, 1, 0x10, 0x90, 0x01, 0x2c, 0x01,
        iCMD_Image      , CM_Monochrome  , true 	, 0x00	, 1, 0x13, 0x90, 0x01, 0x2c, 0x01,
        iCMD_Busy				        , 0x01   , 0xE8   , 0x0f,
        iCMD_iTC_SPI			        , 0x04   , 0,
        iCMD_Busy				        , 0x01   , 0xE8   , 0x0f,
        iCMD_iTC_SPI			        , 0x12   , 0,
        iCMD_Busy				        , 0x01   , 0xFF   , 0xFF,
        iCMD_END
    },
    (const uint8_t []) //Power off
    {
        iCMD_iTC_SPI			, 0x02, 0 ,
        iCMD_Busy				, 0x01   , 0xe8   , 0x0f,
        iCMD_IO_Ctrl			, io_All , 0,
        iCMD_IO_Ctrl			, io_SPI_Pin, 0,
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


#endif /*_ITC_420_AURORA_MB_OTP_H_*/


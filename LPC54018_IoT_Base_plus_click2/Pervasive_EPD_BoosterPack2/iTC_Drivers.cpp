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

#include "iTC_Drivers.h"
#include "iTC_LUT/iTC_215_Aurora_Mb_OTP.h"
#include "iTC_LUT/iTC_287_Aurora_Mb_OTP.h"
#include "iTC_LUT/iTC_420_Aurora_Mb_OTP.h"
#include "iTC_LUT/iTC_287_Spectra_OTP.h"
#include "iTC_LUT/iTC_420_Spectra_OTP.h"
#include "iTC_LUT/iTC_266_Spectra_OTP.h"
iTC_DriversClass::iTC_DriversClass()
{
    iTCEng = new iTC_EngineClass();
}
void iTC_DriversClass::EPD_IO_Config()
{
    iTCEng->iTC_IO_Config();
}
void iTC_DriversClass::EPD_power_on(uint8_t EPD_type_index, int8_t temperature, OperationMode_t operation_mode)
{
    const iTC_WaveformLUT_t *OTP_LUT = NULL;
    switch(EPD_type_index)
    {
        case EPD_215_BW:
            OTP_LUT = &iTC_215Mb_OTP_LUT;
            break;
        case EPD_287_BW:
            OTP_LUT = &iTC_287Mb_OTP_LUT;
            break;
        case EPD_420_BW:
            OTP_LUT = &iTC_420Mb_OTP_LUT;
            break;
	    case EPD_287_BWR:
            OTP_LUT = &iTC_287Sp_OTP_LUT;
            break;
        case EPD_420_BWR:
            OTP_LUT = &iTC_420Sp_OTP_LUT;
            break;
        case EPD_266_BWR:
            OTP_LUT = &iTC_266Sp_OTP_LUT;
            break;
    }
    iTCEng->iTC_power_on(EPD_type_index, temperature, operation_mode, NULL, OTP_LUT, NULL);
}
uint8_t iTC_DriversClass::EPD_initialize_driver(OperationMode_t operation_mode)
{
    return iTCEng->iTC_initialize_driver(operation_mode);
}
uint8_t iTC_DriversClass::EPD_Display_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr)
{
    return iTCEng->iTC_Display_from_Ram(previous_image_ptr, new_image_ptr);
}
uint8_t iTC_DriversClass::EPD_Display_from_flash(long previous_image_flash_address, long new_image_flash_address,
        EPD_read_memory_handler On_EPD_read_flash)
{
    return iTCEng->iTC_Display_from_flash(previous_image_flash_address, new_image_flash_address, On_EPD_read_flash);
}
uint8_t iTC_DriversClass::EPD_power_off(void)
{
    return iTCEng->iTC_power_off();
}


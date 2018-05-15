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

#include "Pervasive_EPD_BoosterPack2.h"

/* Glossary of Acronyms
 * GU = Global Update
 * PU = Partial Update
 * OTP = One Time Programming, the waveform is pre-programmed in driver IC
 */

static OperationMode_t Cur_Mode;

// begin: Initialize the hardware drivers and get temperature information
bool Pervasive_EPD_BoosterPack2::begin(Driver_Type_t EPD_Driver, EPD_SIZE_t EPD_size, int8_t Seltemperature)
{
    PWD_State = false;
    use_epd_size = EPD_size;
    EPD_Driver_Handle = NULL;
    selDev = NULL;
    uint8_t i, j;
    bool flag = false;
    uint8_t cnt = ArrayLength(Driver_Handle_list);

    for(i = 0; i < cnt; i++)
    {
        if(Driver_Handle_list[i].Driver_ID == EPD_Driver)
        {
            EPD_Driver_Handle = &Driver_Handle_list[i];
            selDev = EPD_Driver_Handle->EPD_display;
            break;
        }
    }
    if(i >= cnt)
    {
        EPD_Driver_Handle = NULL;
        selDev = NULL;
        Board_HW_DriverClass HW_Driver;
        HW_Driver.begin();
        return false;
    }
    else
    {
        selDev->EPD_IO_Config();
        j = 0;
        while(EPD_Driver_Handle->Support_Size[j] != EPD_Empty)
        {
            if(EPD_Driver_Handle->Support_Size[j] == EPD_size)
            {
                if(Seltemperature <= (USE_Temperature_Sensor))
                {
                    temperature = selDev->getTemperature();
                }
                else temperature = Seltemperature;

                flag = true;
                use_epd_size = EPD_size;
                break;
            }
            j++;
        }
    }
    Cur_Mode = GU_Mode;
    if(!flag)selDev = NULL;
    return flag;
}

void Pervasive_EPD_BoosterPack2::update_temperature()
{
    if(temperature <= (USE_Temperature_Sensor))
    {
        temperature = selDev->getTemperature();
    }
}

uint8_t Pervasive_EPD_BoosterPack2::EPD_Power_off_Ex()
{
    uint8_t result = RES_OK;
    /* Power off COG Driver */
    if(selDev != NULL)
    {
        if(PWD_State)
        {
            result = selDev->EPD_power_off();
            PWD_State = false;
        }
    }
    Cur_Mode = GU_Mode;
    return result;
}

// Not available yet for partial update
uint8_t  Pervasive_EPD_BoosterPack2::EPD_display_PU_from_flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash, bool IsCtrlPWOff, uint16_t PU_Time)
{

    return 0;
}

// Not available yet for partial update
uint8_t Pervasive_EPD_BoosterPack2::EPD_display_PU_from_pointer(const uint8_t *previous_image_ptr,
        const uint8_t *new_image_ptr, bool IsCtrlPWOff, uint16_t PU_Time)
{
    uint8_t result = 0;

    return result;
}

/**
 * \brief Global update EPD from pointer of memory
 * @param operation_mode  for iTC. Define it's on GU, PU or OTP mode   
 * @param IsCtrlPWOff     Define to power off display or not at the end
 */ 
uint8_t Pervasive_EPD_BoosterPack2::EPD_display_GU_from_pointer(const uint8_t *previous_image_ptr,
        const uint8_t *new_image_ptr,
        OperationMode_t operation_mode, bool IsCtrlPWOff)
{
    uint8_t result = 0;
    if(selDev == NULL)
    {
        return ERROR_NoSuport;
    }
    update_temperature();
    if(!PWD_State)
    {
        /* Power on COG Driver */
        selDev->EPD_power_on(use_epd_size, temperature, operation_mode);

        /* Initialize COG Driver */
        result = selDev->EPD_initialize_driver(operation_mode);
        if((result & RES_OK) != RES_OK)
        {
            PWD_State = false;
            return result;
        }
        else PWD_State = true;
    }
    else if(Cur_Mode != operation_mode)
    {
        Cur_Mode = operation_mode;
        /*  Initialize COG Driver */
        result = selDev->EPD_initialize_driver(operation_mode);
        if((result & RES_OK) != RES_OK) return result;
    }
    /* Display image data on EPD from image array */
    selDev->EPD_Display_from_Ram((uint8_t *)previous_image_ptr, (uint8_t *)new_image_ptr);
    if(IsCtrlPWOff)
    {
        result |= EPD_Power_off_Ex();
    }
    return result;
}

uint8_t Pervasive_EPD_BoosterPack2::EPD_display_GU_from_pointer(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr)
{
    return EPD_display_GU_from_pointer(previous_image_ptr, new_image_ptr, OTP_Mode, true);

}

/**
 * \brief Global update EPD from the address of memory
 * @param operation_mode  for iTC. Define it's on GU, PU or OTP mode   
 * @param IsCtrlPWOff     Define to power off display or not at the end
 */ 
uint8_t Pervasive_EPD_BoosterPack2::EPD_display_GU_from_flash(long previous_image_address,
        long new_image_address, EPD_read_memory_handler On_EPD_read_flash,
        OperationMode_t operation_mode, bool IsCtrlPWOff)
{
    uint8_t result = 0;
    if(selDev == NULL)
    {
        return ERROR_NoSuport;
    }
    update_temperature();
    if(!PWD_State)
    {
        /* Power on COG Driver */
        selDev->EPD_power_on(use_epd_size, temperature, operation_mode);

        /* Initialize COG Driver */
        result = selDev->EPD_initialize_driver(operation_mode);
        if((result & RES_OK) != RES_OK)
        {
            PWD_State = false;
            return result;
        }
        else PWD_State = true;
    }
    else if(Cur_Mode != operation_mode)
    {
        Cur_Mode = operation_mode;
        /*  Initialize COG Driver */
        result = selDev->EPD_initialize_driver(operation_mode);
        if((result & RES_OK) != RES_OK) return result;
    }
    /* Display image data on EPD from image array */
    result = selDev->EPD_Display_from_flash(previous_image_address, new_image_address, On_EPD_read_flash);
    if(IsCtrlPWOff)
    {
        result |= EPD_Power_off_Ex();
    }
    return result;
}

uint8_t Pervasive_EPD_BoosterPack2::EPD_display_GU_from_flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash)
{
    return EPD_display_GU_from_flash(previous_image_address, new_image_address, On_EPD_read_flash, OTP_Mode, true);

}


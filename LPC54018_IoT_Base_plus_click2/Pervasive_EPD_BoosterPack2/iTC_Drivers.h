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

#ifndef PDI_DISPLAYS_iTC_Drivers_AURORA_MB_H_
#define PDI_DISPLAYS_iTC_Drivers_AURORA_MB_H_


#include "EPD_drivers.h"
#include "EPD_Display.h"
#include "iTC_Engine.h"
class iTC_DriversClass : public EPDDisplayClass
{
public:
    iTC_DriversClass();
    virtual void 	  EPD_IO_Config();
    virtual void    EPD_power_on(uint8_t EPD_type_index, int8_t temperature, OperationMode_t operation_mode);
    virtual uint8_t EPD_initialize_driver(OperationMode_t operation_mode);
    virtual uint8_t EPD_Display_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr);
    virtual uint8_t EPD_Display_from_flash(long previous_image_flash_address, long new_image_flash_address, EPD_read_memory_handler On_EPD_read_flash);
    virtual uint8_t EPD_power_off(void);

    virtual void    EPD_Display_PU_from_Ram(uint8_t *previous_image_ptr,uint8_t *new_image_ptr, uint16_t PU_Time) {};
    virtual void    EPD_Display_PU_from_Flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash, uint16_t PU_Time) {};

private:
    iTC_EngineClass *iTCEng;
};


#endif /* PDI_DISPLAYS_iTC_Drivers_AURORA_MB_H_ */

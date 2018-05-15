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
//#define eTC_G2_Aurora_Ma
//#define eTC_G2_Aurora_Mb
#define iTC_Drivers

#ifndef PDI_DISPLAYS_DRIVERS_PDI_EPAPER_H_
#define PDI_DISPLAYS_DRIVERS_PDI_EPAPER_H_
#include "EPD_drivers.h"
#include "EPD_Display.h"

#ifdef eTC_G2_Aurora_Mb
    #include "eTC_G2_Size_Aurora_Mb.h"
#endif

#ifdef eTC_G2_Aurora_Ma
    #include "eTC_G2_Size_Aurora_Ma.h"
#endif

#ifdef iTC_Drivers
    #include "iTC_Drivers.h"
#endif
typedef struct
{
    Driver_Type_t						Driver_ID;
    uint8_t *							Support_Size;
    bool 								IsSupportPartialUpdate;
    EPDDisplayClass						*EPD_display;
} Driver_Handle_t;
static const Driver_Handle_t Driver_Handle_list[] =
{
#ifdef eTC_G2_Aurora_Mb
    {
        dr_eTC_G2_Aurora_Mb,
        (uint8_t []){EPD_144_BW, EPD_200_BW, EPD_271_BW, EPD_190_BW, EPD_260_BW, EPD_Empty},
        true,
        (EPDDisplayClass *)new eTC_G2_Size_Aurora_MbClass()

    },
#endif
#ifdef eTC_G2_Aurora_Ma
    {
        dr_eTC_G2_Aurora_Ma,
        (uint8_t []){EPD_144_BW, EPD_200_BW, EPD_271_BW, EPD_190_BW, EPD_260_BW, EPD_Empty},
        false,
        (EPDDisplayClass *)new eTC_G2_Size_Aurora_MaClass()

    },
#endif
#ifdef iTC_Drivers
    {
        dr_iTC_Drivers,
        (uint8_t []){EPD_215_BW, EPD_287_BW,EPD_420_BW,EPD_287_BWR,EPD_420_BWR,EPD_266_BWR, EPD_Empty},
        false,
        (EPDDisplayClass *)new iTC_DriversClass()
    },
#endif
};
#define USE_Temperature_Sensor				-100
class Pervasive_EPD_BoosterPack2
{
public:
    bool begin(Driver_Type_t EPD_Driver, EPD_SIZE_t EPD_size, int8_t Seltemperature);
    uint8_t EPD_Power_off_Ex();
    uint8_t EPD_display_GU_from_pointer(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr, OperationMode_t operationmode, bool IsCtrlPWOff);
    uint8_t EPD_display_GU_from_pointer(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr);
    uint8_t EPD_display_GU_from_flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash, OperationMode_t operationmode, bool IsCtrlPWOff);
    uint8_t EPD_display_GU_from_flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash);
    uint8_t EPD_display_PU_from_pointer(const uint8_t *previous_image_ptr,	const uint8_t *new_image_ptr, bool IsCtrlPWOff, uint16_t PU_Time);
    uint8_t EPD_display_PU_from_flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash, bool IsCtrlPWOff, uint16_t PU_Time);

private:
    const Driver_Handle_t *EPD_Driver_Handle;
    EPDDisplayClass * selDev;
    EPD_SIZE_t use_epd_size;
    bool PWD_State;
    int8_t temperature;
    void update_temperature();
};


#endif /* PDI_DISPLAYS_DRIVERS_PDI_EPAPER_H_ */

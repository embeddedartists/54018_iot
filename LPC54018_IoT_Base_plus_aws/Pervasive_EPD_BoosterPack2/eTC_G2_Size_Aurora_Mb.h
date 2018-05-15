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
#ifndef PDI_DISPLAYS_DRIVERS_FPL_DRIVERS_ETC_G2_SIZE_AURORA_MB_H_
#define PDI_DISPLAYS_DRIVERS_FPL_DRIVERS_ETC_G2_SIZE_AURORA_MB_H_
#include "EPD_drivers.h"
#include "EPD_Display.h"
// The definition for driving stage to compare with for getting Odd and Even data  */
#define eTC_G2Mb_BLACK0   (uint8_t)(0x03) /**< getting bit1 or bit0 as black color(11) */
#define eTC_G2Mb_BLACK1   (uint8_t)(0x0C) /**< getting bit3 or bit2 as black color(11) */
#define eTC_G2Mb_BLACK2   (uint8_t)(0x30) /**< getting bit5 or bit4 as black color(11) */
#define eTC_G2Mb_BLACK3   (uint8_t)(0xC0) /**< getting bit7 or bit6 as black color(11) */
#define eTC_G2Mb_WHITE0   (uint8_t)(0x02) /**< getting bit1 or bit0 as white color(10) */
#define eTC_G2Mb_WHITE1   (uint8_t)(0x08) /**< getting bit3 or bit2 as white color(10) */
#define eTC_G2Mb_WHITE2   (uint8_t)(0x20) /**< getting bit5 or bit4 as white color(10) */
#define eTC_G2Mb_WHITE3   (uint8_t)(0x80) /**< getting bit7 or bit6 as white color(10) */
#define eTC_G2Mb_NOTHING0 (uint8_t)(0x00) /**< getting bit1 or bit0 as nothing input(01) */
#define eTC_G2Mb_NOTHING1 (uint8_t)(0x00) /**< getting bit3 or bit2 as nothing input(01) */
#define eTC_G2Mb_NOTHING2 (uint8_t)(0x00) /**< getting bit5 or bit4 as nothing input(01) */
#define eTC_G2Mb_NOTHING3 (uint8_t)(0x00) /**< getting bit7 or bit6 as nothing input(01) */
#define eTC_G2Mb_NOTHING  (uint8_t)(0x55) /**< sending Nothing frame, 01=Nothing, 0101=0x5 */

// Line data structure of 1.44 inch EPD
struct eTC_G2Mb_144_line_data_t
{
    uint8_t even[16]; /**< 1.44" even byte array */
    uint8_t scan[24]; /**< 1.44" scan byte array */
    uint8_t odd [16]; /**< 1.44" odd byte array */
    uint8_t border_byte;  /**< Internal border_control, for 1.44" EPD only */
} ;

// Line data structure of 2 inch EPD
struct eTC_G2Mb_200_line_data_t
{
    uint8_t dummy_data;	/**< dummy byte 0x00 */
    uint8_t even[25]; /**< 2" even byte array */
    uint8_t scan[24]; /**< 2" scan byte array */
    uint8_t odd [25]; /**< 2" odd byte array */

} ;

// Line data structure of 2.7 inch EPD
struct eTC_G2Mb_270_line_data_t
{
    uint8_t dummy_data;	/**< dummy byte 0x00 */
    uint8_t even[33]; /**< 2.7" even byte array */
    uint8_t scan[44]; /**< 2.7" scan byte array */
    uint8_t odd [33]; /**< 2.7" odd byte array */
} ;


// Line data structure of 1.9 inch EPD
struct eTC_G2Mb_190_line_data_t
{
    uint8_t scan_odd[16];/**< 1.9" scan odd byte array */
    uint8_t data[36];/**< 1.9" data byte array */
    uint8_t scan_even[16]; /**< 1.9"  scan even byte array */
    uint8_t border_byte;	/**< Border Byte, Internal border_control*/
} ;

// Line data structure of 2.6 inch EPD
struct eTC_G2Mb_260_line_data_t
{
    uint8_t scan_odd[16]; /**< 2.6" even byte array */
    uint8_t data[58]; /**< 2.6" scan byte array */
    uint8_t scan_even [16]; /**< 2.6" odd byte array */
    uint8_t border_byte;	/**< Border Byte, Internal border_control */
} ;

// Packet structure of a line data */
typedef union
{
    union
    {
        //eTC_G2_Aurora_Mb
        struct eTC_G2Mb_144_line_data_t eTC_G2Mb_144_line_data; /**< line data structure of 1.44" EPD */
        struct eTC_G2Mb_200_line_data_t eTC_G2Mb_200_line_data; /**< line data structure of 2" EPD */
        struct eTC_G2Mb_270_line_data_t eTC_G2Mb_270_line_data; /**< line data structure of 2.7" EPD */
        struct eTC_G2Mb_190_line_data_t eTC_G2Mb_190_line_data; /**< line data structure of 1.9" EPD */
        struct eTC_G2Mb_260_line_data_t eTC_G2Mb_260_line_data; /**< line data structure of 2.6" EPD */

    } line_data_by_size; /**< the line data of specific EPD size */
    uint8_t uint8[LINE_BUFFER_DATA_SIZE]; /**< the maximum line buffer data size as length */
} eTC_G2Mb_line_data_t;


class eTC_G2_Size_Aurora_MbClass : public EPDDisplayClass
{

public:
    //static const uint8_t Driver_ID=dr_eTC_G2_Aurora_Mb;
    eTC_G2_Size_Aurora_MbClass();
    virtual void EPD_IO_Config();
    virtual void    EPD_power_on(uint8_t EPD_type_index, int8_t temperature, OperationMode_t operationmode);
    virtual uint8_t EPD_initialize_driver(OperationMode_t operationmode);
    virtual uint8_t EPD_Display_from_Ram(uint8_t *previous_image_ptr, uint8_t *new_image_ptr);
    virtual uint8_t EPD_Display_from_flash(long previous_image_flash_address, long new_image_flash_address, EPD_read_memory_handler On_EPD_read_flash);
    virtual uint8_t EPD_power_off(void);

    virtual void    EPD_Display_PU_from_Ram(uint8_t *previous_image_ptr,uint8_t *new_image_ptr, uint16_t PU_Time);
    virtual void    EPD_Display_PU_from_Flash(long previous_image_address, long new_image_address, EPD_read_memory_handler On_EPD_read_flash, uint16_t PU_Time);

private:
    COG_parameters_t *cur_cog_param;
    eTC_G2Mb_line_data_t COG_Line;

    uint32_t current_frame_time;
    uint16_t eTC_G2Mb_PartialUpdate_StageTime;//D_PartialUpdate_StageTime;
    uint8_t  *data_line_even;
    uint8_t  *data_line_odd;
    uint8_t  *data_line_scan;
    uint8_t  *data_line_border_byte;
    uint8_t *previous_lin, *new_line;
    EPD_read_memory_handler _On_EPD_read_flash;

    uint8_t  eTC_G2Mb_GetSizeIndex(uint8_t EPD_type_index);
    void  eTC_G2Mb_temperature_factor(int8_t temperature);
    void  eTC_G2Mb_RegAssign_Select(void);
    void  eTC_G2Mb_GU_Handle(const uint8_t *image_prt, long image_data_address, uint8_t stage_no);
    void  eTC_G2Mb_GU_Handle_19_26(const uint8_t *image_prt, long image_data_address, uint8_t stage_no) ;
    void  eTC_G2Mb_Handle_PU_19_26(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr,
                                   long previous_image_address, long new_image_address);
    void  eTC_G2Mb_Handle_PU(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr,
                             long previous_image_address, long new_image_address);
    void  eTC_G2Mb_PU_Collection(const uint8_t *previous_image_ptr, const uint8_t *new_image_ptr,
                                 long previous_image_address, long new_image_address,
                                 EPD_read_memory_handler On_EPD_read_flash);
    void  eTC_G2Mb_nothing_frame(void);
    void  eTC_G2Mb_dummy_line(void);
    void  eTC_G2Mb_border_dummy_line(void);
    void  eTC_G2Mb_nothing_frame_19_26(void);
    void  eTC_G2Mb_border_dummy_line_frame_19_26(void);

};

extern eTC_G2_Size_Aurora_MbClass *EPD_eTC_G2SizeMb;

#endif /* PDI_DISPLAYS_DRIVERS_FPL_DRIVERS_ETC_G2_SIZE_AURORA_MB_H_ */

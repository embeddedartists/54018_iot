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

#include <SPI.h>
#include "Pervasive_EPD_BoosterPack2.h"

/** Important ******************************************************************
 *  - To understand more of the definitions of film material, drivers and sizes,
 *    please visit http://www.pervasivedisplays.com/products   and
 *    http://www.pervasivedisplays.com/products/label_info
 *  - This example code is made with EPD Extension Kit Gen 2 (EXT2).
 *    Visit http://www.pervasivedisplays.com/kits/ext2_kit for more details.
 *  - Technical support: http://www.pervasivedisplays.com/contact/technical-support
 *  - For converting any image file to image array as .c file, please download
 *    PDi Apps from http://www.pervasivedisplays.com/kits/ext2_kit#Utility by the
 *    [Bitmap] tab of PDi Apps.
 **/

/* Glossary of Acronyms
 * GU = Global Update
 * PU = Partial Update
 * LUT = Look-up table, the array to define the parameters of driving waveform
 * OTP = One Time Programming, the LUTs are pre-programmed in driver IC
 */

/**
 * \brief define the timing controller type and size of EPD
 * \note
 *  - eTC=external timing controller (driver IC)
 *  - iTC=internal timing controller */
// eTC
#define sz_eTC_144  0 //J7 Switches 0000 001x
#define sz_eTC_190  1 //J7 Switches 0000 000x
#define sz_eTC_200  2 //J7 Switches 0000 001x
#define sz_eTC_260  3 //J7 Switches 0000 000x
#define sz_eTC_271  4 //J7 Switches 0000 000x
// iTC
#define sz_iTC_215  5 //J7 Switches 1010 000x
#define sz_iTC_287  6 //J7 Switches 0101 010x
#define sz_iTC_420  7 //J7 Switches 0101 010x
//iTC Spectra
#define sz_iTC_287R  8 //J7 Switches 0101 010x
#define sz_iTC_420R  9 //J7 Switches 0101 010x

/**
 * \brief define the EPD drivers with film material
 * \note
 *  - BW=black and white colors, Aurora film
 *  - BWR=black, white and red colors, Spectra-red film
 *  - a=Aurora Ma (V230)
 *  - b=Aurora Mb (V231) */ 
#define dr_eTC_BWa			0
#define dr_eTC_BWb			1
#define dr_iTC_BWb			2
#define dr_iTC_BWR			3

/**
 * \brief Configure the following two definitions by your connected display model  */
#define USE_EPD_Type    dr_iTC_BWR
#define USE_EPD_Size    sz_iTC_287R


#if (USE_EPD_Type==dr_eTC_BWa || USE_EPD_Type==dr_eTC_BWb)
    #if(USE_EPD_Type==dr_eTC_BWa)
        #define  EPD_Type		dr_eTC_G2_Aurora_Ma
    #else
        #define  EPD_Type		dr_eTC_G2_Aurora_Mb
    #endif
    #if(USE_EPD_Size==sz_eTC_144)
        #include "examples/Images/Image_eTC_144_01.c"
        #include "examples/Images/Image_eTC_144_02.c"
        #define  EPD_Size     EPD_144_BW
        #define Image1        (uint8_t *)&Image_eTC_144_01
        #define Image2        (uint8_t *)&Image_eTC_144_02
        #elif(USE_EPD_Size==sz_eTC_190)
        #include "examples/Images/Image_eTC_190_01.c"
        #include "examples/Images/Image_eTC_190_02.c"
        #define  EPD_Size     EPD_190_BW
        #define Image1        (uint8_t *)&Image_eTC_190_01
        #define Image2        (uint8_t *)&Image_eTC_190_02
        #elif(USE_EPD_Size==sz_eTC_200)
        #include "examples/Images/Image_eTC_200_01.c"
        #include "examples/Images/Image_eTC_200_02.c"
        #define  EPD_Size     EPD_200_BW
        #define Image1        (uint8_t *)&Image_eTC_200_01
        #define Image2        (uint8_t *)&Image_eTC_200_02
        #elif(USE_EPD_Size==sz_eTC_260)
        #include "examples/Images/Image_eTC_260_01.c"
        #include "examples/Images/Image_eTC_260_02.c"
        #define  EPD_Size     EPD_260_BW
        #define Image1        (uint8_t *)&Image_eTC_260_01
        #define Image2        (uint8_t *)&Image_eTC_260_02
        #elif(USE_EPD_Size==sz_eTC_271)
        #include "examples/Images/Image_eTC_271_01.c"
        #include "examples/Images/Image_eTC_271_02.c"
        #define  EPD_Size     EPD_271_BW
        #define Image1        (uint8_t *)&Image_eTC_271_01
        #define Image2        (uint8_t *)&Image_eTC_271_02
    #endif

    #elif(USE_EPD_Type==dr_iTC_BWb)
    #define  EPD_Type		dr_iTC_Drivers
    #if(USE_EPD_Size==sz_iTC_215)
        #include "examples/Images/Image_iTC_215_01.c"
        #include "examples/Images/Image_iTC_215_02.c"
        #define  EPD_Size     EPD_215_BW
        #define Image1        (uint8_t *)&Image_iTC_215_01
        #define Image2        (uint8_t *)&Image_iTC_215_02
        #elif(USE_EPD_Size==sz_iTC_287)
        #include "examples/Images/Image_iTC_287_01.c"
        #include "examples/Images/Image_iTC_287_02.c"
        #define  EPD_Size     EPD_287_BW
        #define Image1        (uint8_t *)&Image_iTC_287_01
        #define Image2        (uint8_t *)&Image_iTC_287_02
        #elif(USE_EPD_Size==sz_iTC_420)
        #include "examples/Images/Image_iTC_420_01.c"
        #include "examples/Images/Image_iTC_420_02.c"
        #define  EPD_Size     EPD_420_BW
        #define Image1        (uint8_t *)&Image_iTC_420_01
        #define Image2        (uint8_t *)&Image_iTC_420_02
    #endif
    #elif(USE_EPD_Type==dr_iTC_BWR)
    #define  EPD_Type		dr_iTC_Drivers
    #if(USE_EPD_Size==sz_iTC_287R)
        #include "examples/Images/Image_iTC_287SP_01.c"
        #include "examples/Images/Image_iTC_287SP_02.c"
        #define  EPD_Size     EPD_287_BWR
        #define Image1        (uint8_t *)&Image_iTC_287SP_01
        #define Image2        (uint8_t *)&Image_iTC_287SP_02
        #elif(USE_EPD_Size==sz_iTC_420R)
        #include "examples/Images/Image_iTC_420SP_01.c"
        #include "examples/Images/Image_iTC_420SP_02.c"
        #define  EPD_Size     EPD_420_BWR
        #define Image1        (uint8_t *)&Image_iTC_420SP_01
        #define Image2        (uint8_t *)&Image_iTC_420SP_02
    #endif
#endif

// This example will toggle between two images.
Pervasive_EPD_BoosterPack2 pdi_epd;
uint8_t result;
void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.println("*** EPD Tests");
    Serial.print("Driver = ");
    switch (USE_EPD_Type)
    {
        case dr_eTC_BWa:
            Serial.println("dr_eTC_BWa");
            break;

        case dr_eTC_BWb:
            Serial.println("dr_eTC_BWb");
            break;

        case dr_iTC_BWb:
            Serial.println("dr_iTC_BWb");
            break;

        case dr_iTC_BWR:
            Serial.println("dr_iTC_BWR");
            break;
        default:
            Serial.println("?");
            break;
    }

    Serial.print("Size = ");
    switch (USE_EPD_Size)
    {
        case sz_eTC_144:
            Serial.println("sz_eTC_144");
            break;

        case sz_eTC_190:
            Serial.println("sz_eTC_190");
            break;

        case sz_eTC_200:
            Serial.println("sz_eTC_200");
            break;

        case sz_eTC_260:
            Serial.println("sz_eTC_260");
            break;

        case sz_eTC_271:
            Serial.println("sz_eTC_271");
            break;

        case sz_iTC_215:
            Serial.println("sz_iTC_215");
            break;

        case sz_iTC_287:
            Serial.println("sz_iTC_287");
            break;

        case sz_iTC_420:
            Serial.println("sz_iTC_420");
            break;

        case sz_iTC_287R:
            Serial.println("sz_iTC_287R");
            break;

        case sz_iTC_420R:
            Serial.println("sz_iTC_420R");
            break;

        default:
            Serial.println("?");
            break;
    }

    delay(500);
    Serial.print("pdi_epd.begin... 0x");
    result = pdi_epd.begin(EPD_Type, EPD_Size, USE_Temperature_Sensor);
    Serial.println(result, HEX);
}

void loop()
{
    Serial.print("pdi_epd.EPD_display_GU_from_pointer 2... 0x");
    result = pdi_epd.EPD_display_GU_from_pointer(Image2, Image1);
    Serial.println(result, HEX);
    delay(5000);
    Serial.print("pdi_epd.EPD_display_GU_from_pointer 1... 0x");
    result = pdi_epd.EPD_display_GU_from_pointer(Image1, Image2);
    Serial.println(result, HEX);
    delay(5000);
}


///
/// @file       LCD_screen.h
/// @brief      Class library header
/// @details    Generic LCD class library
/// @n
/// @n @b       Project LCD_screen
/// @n @a       Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author     Rei VILO
/// @author     embedXcode.weebly.com
/// @date       Dec 10, 2013
/// @version114
///
/// @copyright  (c) Rei VILO, 2013-2016 - SPECIAL EDITION FOR ENERGIA
/// @copyright  All rights reserved
/// @n          http://embeddedcomputing.weebly.com/lcd_screen-library-suite
///
/// @n  Dual license:
/// *   For hobbyists and for personal usage: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
/// *   For professionals or organisations or for commercial usage: All rights reserved
///
/// @n  For any enquiry about license, http://embeddedcomputing.weebly.com/contact
///
/// @seeReadMe.txt for references
// Core library - IDE-based
#if defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#else
#error Platform not supported
#endif // end IDE

#ifndef LCD_SCREEN_RELEASE
#define LCD_SCREEN_RELEASE 114
#include "LCD_utilities.h"
const uint16_t blackColour    = 0x0000; //0b0000000000000000;
const uint16_t whiteColour    = 0xffff; //0b1111111111111111;
const uint16_t redColour      = 0xf800; //0b1111100000000000;
const uint16_t greenColour    = 0x07e0; //0b0000011111100000;
const uint16_t blueColour     = 0x001f; //0b0000000000011111;
const uint16_t yellowColour   = 0xffe0; //0b1111111111100000;
const uint16_t cyanColour     = 0x07ff; //0b0000011111111111;
const uint16_t orangeColour   = 0xfbe0; //0b1111101111100000;
const uint16_t magentaColour  = 0xf80f; //0b1111100000001111;
const uint16_t violetColour   = 0xf81f; //0b1111100000011111;
const uint16_t grayColour     = 0x7bef; //0b0111101111101111;
const uint16_t greyColour     = 0x7bef; //0b0111101111101111;
const uint16_t darkGrayColour = 0x39e7; //0b0011100111100111;
class LCD_screen
{
  public:
    LCD_screen();
    virtual void begin() = 0;
    virtual String WhoAmI() = 0;
    void clear(uint16_t colour = blackColour);
    virtual void setOrientation(uint8_t orientation);
    uint8_t getOrientation();
    virtual void showInformation(uint16_t x0 = 0, uint16_t y0 = 0);
    virtual uint16_t screenSizeX();
    virtual uint16_t screenSizeY();
    virtual void circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t colour);
    virtual void arc(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t start, uint16_t end, uint16_t colour);
    virtual void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);
    virtual void dLine(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);
    virtual void setPenSolid(bool flag = true);
    virtual void triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);
    virtual void rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);
    virtual void dRectangle(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);
    virtual void point(uint16_t x1, uint16_t y1, uint16_t colour);
    virtual void setFontSize(uint8_t size) = 0;
    virtual void setFontSolid(bool flag = true);
    virtual uint8_t fontSizeX() = 0;
    virtual uint8_t fontSizeY() = 0;
    virtual void gText(uint16_t x0, uint16_t y0,
                       String s,
                       uint16_t textColour = whiteColour, uint16_t backColour = blackColour,
                       uint8_t ix = 1, uint8_t iy = 1) = 0;
    uint16_t calculateColour(uint8_t red, uint8_t green, uint8_t blue);
    void splitColour(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue);
    uint16_t halveColour(uint16_t rgb);
    uint16_t averageColour(uint16_t rgb1, uint16_t rgb2);
    uint16_t reverseColour(uint16_t rgb);
    bool isReadable();
    bool isStorage();
    virtual uint16_t readPixel(uint16_t x1, uint16_t y1);
    virtual void copyPaste(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t dx, uint16_t dy);
    virtual void copyArea(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint32_t &address);
    virtual void pasteArea(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint32_t &address, bool option = false);
    void displayImage(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t fg, uint16_t bg, const uint8_t* img);
    bool isTouch();
    bool getTouch(uint16_t &x, uint16_t &y, uint16_t &z);
    void calibrateTouch();
  protected:
    uint8_t      _fontX, _fontY, _fontSize;
    uint8_t      _orientation;
    bool         _penSolid, _fontSolid, _flagRead, _flagStorage;
    uint16_t     _screenWidth, _screenHeigth;
    uint8_t      _touchTrim;
    uint16_t     _touchXmin, _touchXmax, _touchYmin, _touchYmax;
    virtual void _fastFill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour) = 0;
    virtual void _setPoint(uint16_t x1, uint16_t y1, uint16_t colour) = 0;
    virtual void _getRawTouch(uint16_t &x0, uint16_t &y0, uint16_t &z0) = 0;
    virtual void _setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) = 0;
    virtual void _writeData88(uint8_t dataHigh8, uint8_t dataLow8) = 0;
    void         _displayTarget(uint16_t x0, uint16_t y0, uint16_t colour);
    void         _swap(int16_t &a, int16_t &b);
    void         _swap(uint16_t &a, uint16_t &b);
    void         _swap(uint8_t &a, uint8_t &b);
    uint16_t     _check(uint16_t x0, uint16_t xmin, uint16_t xmax);
    void         _triangleArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);
    bool         _inValue(int16_t value, int16_t valueLow, int16_t valueHigh);
    bool         _inSector(int16_t valueStart, int16_t valueEnd, int16_t sectorLow, int16_t sectorHigh,
                           int16_t criteriaStart, int16_t criteriaEnd, int16_t criteriaLow, int16_t criteriaHigh,
                           int16_t criteria);
    bool         _inCycle(int16_t value, int16_t valueLow, int16_t valueHigh);
};
#endif

#include "UI_info_icon.h"

const unsigned char BMP_INFO1[] =
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x03,0xC0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x80,0x01,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,0x80,0x03,0x80,0x01,0xC0,0x01,0x00,0x00,0xF8,0xFF,0xFF,0x01,0x80,0x01,0x80,0xFF,0xFF,0x1F,0xFC,0xFF,0xFF,0x00,0xE0,0x01,0x00,0xFF,0xFF,0x7F,0x0E,0x00,0x70,0x00,0xF8,0x00,0x00,0x0E,0x00,0x70,0x07,0x00,0x70,0x00,0x3E,0x00,0x00,0x0E,0x00,0xE0,0x03,0x00,0x30,0x80,0x0F,0x00,0x00,0x0C,0x00,0xC0,0x03,0x00,0x38,0xE0,0x03,0x00,0x00,0x1C,0x00,0xC0,0x03,0x00,0x18,0xE0,0x03,0x00,0x00,0x18,0x00,0xC0,0x03,0x00,0x18,0xC0,0x1F,0x00,0x00,0x38,0x00,0xC0,0x03,0x00,0x1C,0x00,0xFE,0x00,0x00,0x38,0x00,0xC0,0x03,0x00,0x0C,0x00,0xF0,0x07,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x80,0x3F,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x00,0xFC,0x01,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x00,0xE0,0x03,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x00,0xF0,0x01,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x00,0x7C,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x00,0x1F,0x00,0x30,0x00,0xC0,0x03,0x00,0x8C,0x01,0xE0,0x07,0x00,0x30,0x00,0xC0,0x03,0x00,0x8C,0x01,0xF8,0x01,0x00,0x30,0x00,0xC0,0x03,0x00,0x8C,0x01,0x78,0x00,0x00,0x30,0x00,0xC0,0x03,0x00,0x1C,0x01,0xF0,0x00,0x00,0x38,0x00,0xC0,0x03,0x00,0x18,0x00,0xC0,0x03,0x00,0x18,0x00,0xC0,0x03,0x00,0x18,0x00,0x80,0x07,0x00,0x18,0x00,0xC0,0x03,0x00,0x38,0x04,0x00,0x1E,0x00,0x1C,0x00,0xC0,0x03,0x00,0x30,0x0E,0x00,0x3C,0x00,0x0C,0x00,0xC0,0x07,0x00,0x70,0x1C,0x00,0x3C,0x00,0x0E,0x00,0xE0,0xFE,0xFF,0x7F,0x38,0x80,0x1F,0x00,0xFE,0xFF,0x7F,0xFC,0xFF,0xFF,0xF0,0x80,0x03,0x00,0xFF,0xFF,0x3F,0xF0,0xFF,0xFF,0xE1,0x81,0x01,0x80,0xFF,0xFF,0x0F,0x00,0x00,0x80,0xC3,0x87,0x01,0xC0,0x01,0x00,0x00,0x00,0x00,0x00,0x07,0x87,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x80,0x01,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x07,0xE0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"E:\MANRIDY_Chen\项目（new）\HB044\UI\0605\180606切图\more\图标\7-1.bmp",0*/
/* (64 X 80 ) */
const unsigned char BMP_INFO2[] =
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"E:\MANRIDY_Chen\项目（new）\HB044\UI\0605\180606切图\more\图标\7-2.bmp",0*/
/* (64 X 80 ) */
const unsigned char BMP_INFO[] = 
{0x00,0x00,0x00,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xF8,0x0F,0x00,0x80,0xFF,0x00,0x00,0xF0,0x1F,0x00,0x00,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0xFE,0xFF,0x7F,0x0E,0x0C,0x00,0x0E,0x0C,0x00,0x0E,0x0C,0x00,0x0E,0x0C,0x00,0x0E,0x0C,0x00,0x0E,0x0C,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0x1F,0xFC,0xFF,0x3F,0x1E,0x00,0x78,0x0E,0x00,0x70,0x06,0x00,0x60,0x06,0x00,0x60,0x0E,0x00,0x70,0x1C,0x00,0x38,0xFC,0xFF,0x3F,0xF0,0xFF,0x0F,0x00,0x00,0x00};/*"E:\MANRIDY_Chen\项目（new）\HB044\UI\0605\180606切图\more\3.bmp",0*/
/* (42 X 24 ) */


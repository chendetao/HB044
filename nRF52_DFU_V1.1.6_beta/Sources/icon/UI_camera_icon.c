
#include "UI_camera_icon.h"

const unsigned char BMP_camera1[] = 
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0xC0,0x0F,0x00,0x00,0x00,0x00,0xF0,0x03,0x00,0x00,0xE0,0x03,0x00,0x00,0x00,0x00,0xC0,0x07,0x00,0x00,0xE0,0x01,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x0F,0x00,0x00,0xE0,0x1F,0x00,0x00,0x1C,0x00,0x00,0x3E,0x00,0x00,0xFE,0xFF,0x00,0x00,0x1C,0x00,0x00,0x7C,0x00,0x80,0xFF,0xFF,0x07,0x00,0x1C,0x00,0x00,0x78,0x00,0xE0,0x1F,0xF0,0x0F,0x00,0x1C,0x00,0x00,0x70,0x00,0xF0,0x03,0x00,0x3F,0x00,0x1C,0x00,0x00,0x70,0x00,0xFC,0x00,0x00,0x7C,0x00,0x1C,0x00,0x00,0x70,0x00,0x3E,0x00,0x00,0xF8,0x00,0x1C,0x00,0x00,0x70,0x00,0x1F,0x00,0x00,0xE0,0x01,0x1C,0x00,0x00,0x70,0x80,0x0F,0x00,0x00,0xC0,0x03,0x1C,0x00,0x00,0x70,0x80,0x07,0x00,0x00,0x80,0x07,0x1C,0x00,0x00,0x70,0xC0,0x03,0x00,0x00,0x00,0x07,0x1C,0x00,0x00,0x70,0xE0,0x01,0x00,0x00,0x00,0x0F,0x1C,0x00,0x00,0x70,0xE0,0x01,0x00,0x00,0x00,0x0E,0x1C,0x00,0x00,0x70,0xE0,0x00,0x00,0x00,0x00,0x1E,0x1C,0x00,0x00,0x70,0xF0,0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x70,0x70,0x00,0x00,0x00,0x00,0x3C,0x1C,0x00,0x00,0x70,0x70,0x00,0x00,0x00,0x00,0x38,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x38,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x38,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x38,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x70,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x70,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x70,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x70,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0x00,0x78,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0xC0,0x38,0x1C,0x00,0x00,0x70,0x38,0x00,0x00,0x00,0xE0,0x39,0x1C,0x00,0x00,0x70,0x70,0x00,0x00,0x00,0xE0,0x38,0x1C,0x00,0x00,0x70,0x70,0x00,0x00,0x00,0xC0,0x3C,0x1C,0x00,0x00,0x70,0xF0,0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x70,0xF0,0x00,0x00,0x00,0x38,0x1C,0x1C,0x00,0x00,0x70,0xE0,0x00,0x00,0x00,0x3C,0x0E,0x1C,0x00,0x00,0x70,0xE0,0x01,0x00,0x00,0x1E,0x0F,0x1C,0x00,0x00,0x70,0xC0,0x03,0x00,0x80,0x1F,0x07,0x1C,0x00,0x00,0x70,0x80,0x07,0x00,0xC0,0x87,0x07,0x1C,0x00,0x00,0x70,0x80,0x0F,0x00,0xF8,0xC3,0x03,0x1C,0x00,0x00,0x70,0x00,0x1F,0x00,0xFC,0xE0,0x01,0x1C,0x00,0x00,0x70,0x00,0x3E,0x00,0x7C,0xF8,0x00,0x1C,0x00,0x00,0x70,0x00,0xFC,0x00,0x00,0x7C,0x00,0x1C,0x00,0x00,0x70,0x00,0xF8,0x03,0x00,0x3F,0x00,0x1C,0x00,0x00,0x70,0x00,0xE0,0x1F,0xF0,0x1F,0x00,0x1C,0x00,0x00,0x70,0x00,0x80,0xFF,0xFF,0x07,0x00,0x1C,0x00,0x00,0x70,0x00,0x00,0xFE,0xFF,0x01,0x00,0x1C,0x00,0x00,0x70,0xF0,0x07,0xF0,0x1F,0x00,0x00,0x1C,0x00,0x00,0x70,0xF8,0x0F,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0xFC,0x1F,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x70,0xFC,0x1F,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x70,0xF8,0x0F,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0xF0,0xF0,0x07,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0xE0,0x01,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0xE0,0x03,0x00,0x00,0x00,0x00,0x80,0x07,0x00,0x00,0xC0,0x0F,0x00,0x00,0x00,0x00,0xF0,0x03,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"E:\MANRIDY_Chen\项目（new）\HB044\UI\0605\180606切图\其他\2-1.bmp",0*/
/* (120 X 80 ) */

const unsigned char BMP_camera2[] = 
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"E:\MANRIDY_Chen\项目（new）\HB044\UI\0605\180606切图\其他\2-2.bmp",0*/
/* (120 X 80 ) */


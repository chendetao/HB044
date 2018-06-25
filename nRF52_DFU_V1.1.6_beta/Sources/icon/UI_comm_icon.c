#include "UI_comm_icon.h"

const unsigned char Font_15x38[][75] = 
{
{0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0x07,0x00,0x00,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\0.bmp",0*/
{0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x38},/*"E:\BandAll\HB039\UI\UI\数字1\1.bmp",0*/
{0x07,0x00,0xFC,0xFF,0x3F,0x07,0x00,0xFC,0xFF,0x3F,0x07,0x00,0xFC,0xFF,0x3F,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0xFF,0xFF,0x1F,0x00,0x38,0xFF,0xFF,0x1F,0x00,0x38,0xFF,0xFF,0x1F,0x00,0x38},/*"E:\BandAll\HB039\UI\UI\数字1\2.bmp",0*/
{0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\3.bmp",0*/
{0xFF,0xFF,0x0F,0x00,0x00,0xFF,0xFF,0x0F,0x00,0x00,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\4.bmp",0*/
{0xFF,0xFF,0x0F,0x00,0x38,0xFF,0xFF,0x0F,0x00,0x38,0xFF,0xFF,0x0F,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0xFE,0xFF,0x3F,0x07,0x00,0xFE,0xFF,0x3F,0x07,0x00,0xFE,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\5.bmp",0*/
{0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0xFE,0xFF,0x3F,0x07,0x00,0xFE,0xFF,0x3F,0x07,0x00,0xFE,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\6.bmp",0*/
{0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\7.bmp",0*/
{0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0x07,0x00,0x1C,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\8.bmp",0*/
{0xFF,0xFF,0x0F,0x00,0x38,0xFF,0xFF,0x0F,0x00,0x38,0xFF,0xFF,0x0F,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0x07,0x00,0x0E,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F},/*"E:\BandAll\HB039\UI\UI\数字1\9.bmp",0*/
{0x00,0xFC,0x80,0x0F,0x00,0x00,0xFC,0x80,0x0F,0x00,0x00,0xFC,0x80,0x0F,0x00},/*"E:\BandAll\HB039\UI\UI\数字1\点.bmp",0*/
};
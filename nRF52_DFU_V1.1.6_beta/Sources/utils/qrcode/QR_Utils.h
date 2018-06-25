#ifndef __QR_UTILS_H__
#define __QR_UTILS_H__

#include "LCD_ST7735.h"

extern int QR_Encode_Create( unsigned char *text );
extern int QR_Copy_Image( unsigned short fb[LCD_H][LCD_W] );

#endif

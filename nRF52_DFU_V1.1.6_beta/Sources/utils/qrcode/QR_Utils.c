#include "QR_Encode.h"
#include "QR_Utils.h"
#include "LCD_ST7735.h"

struct CQR_Encode encoder;

int QR_Encode_Create( unsigned char *text )
{
    int Level 	   = 0;
    int Ver    = 1;
    int AutoExtent = 0;
    int MaskingNo  = 0;

    bool ret;

    ret = EncodeData( &encoder, Level, Ver, AutoExtent, MaskingNo, text, 0);    

    if ( ret != true )
    {
        return -1;
    }
	
	return 0;
}

int QR_Copy_Image( unsigned short fb[LCD_H][LCD_W] )
{
    int symbleSize = encoder.m_nSymbleSize;
    
    for ( int y = 0; y < LCD_H; y++)
	for ( int x = 0; x < LCD_W; x++ )
		fb[y][x] = 0XFFFF;

    #if 0
	for ( int y = 0; y < LCD_H; y++ )
	for ( int x = 0; x < 40; x++ )
		fb[y][x] = 0x00;
	
	for ( int y = 0; y < LCD_H; y++ )
	for ( int x = 86; x < LCD_W; x++ )
		fb[y][x] = 0x00;

	for ( int y = 0; y < 25; y++ )
	for ( int x = 0; x < LCD_W; x++ )
		fb[y][x] = 0x00;
 
	for ( int y = 71; y < LCD_H; y++ )
	for ( int x = 0; x < LCD_W; x++ )
		fb[y][x] = 0x00;	
    #endif
 
    for ( int y = 0; y < LCD_H; y++ )
    for ( int x = 0; x < LCD_W; x++ )
    {
		if ( ( (y < (symbleSize)) ) && (x < symbleSize) )
		if ( encoder.m_byModuleData[y][x] )
		{					
			/** Stretch 2 times */
            #if 0
			fb[(y<<1)+0+27][x*2+0+42] = 0x0;
			fb[(y<<1)+0+27][x*2+1+42] = 0x0;
			fb[(y<<1)+1+27][x*2+0+42] = 0x0;
			fb[(y<<1)+1+27][x*2+1+42] = 0x0;
            #else
			fb[y*4+0+6][x*4+0+22] = 0x0;
			fb[y*4+0+6][x*4+1+22] = 0x0;
			fb[y*4+0+6][x*4+2+22] = 0x0;
			fb[y*4+0+6][x*4+3+22] = 0x0;   

			fb[y*4+1+6][x*4+0+22] = 0x0;
			fb[y*4+1+6][x*4+1+22] = 0x0;
			fb[y*4+1+6][x*4+2+22] = 0x0;
			fb[y*4+1+6][x*4+3+22] = 0x0;

			fb[y*4+2+6][x*4+0+22] = 0x0;
			fb[y*4+2+6][x*4+1+22] = 0x0;
			fb[y*4+2+6][x*4+2+22] = 0x0;
			fb[y*4+2+6][x*4+3+22] = 0x0;

			fb[y*4+3+6][x*4+0+22] = 0x0;
			fb[y*4+3+6][x*4+1+22] = 0x0;
			fb[y*4+3+6][x*4+2+22] = 0x0;
			fb[y*4+3+6][x*4+3+22] = 0x0;
            #endif
		}
    }

	return 0;    
}

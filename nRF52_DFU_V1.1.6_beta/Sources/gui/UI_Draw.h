#ifndef __UI_DRAW_H__
#define __UI_DRAW_H__

#include "LCD_ST7735.h"

#define COLORREF(r,g,b) ((( r & 0xF8)<<8)|(( g & 0xFC)<<3)|(b >> 3))

extern unsigned short fb[LCD_H][LCD_W];

#define setpixel( x, y, color) do\
{\
	if ( x < LCD_W && y < LCD_H )\
	 fb[y][x] = color;\
}while(0)

extern void set_pixel( int x, int y, int color );

extern void draw_bitmap(int fx, int fy, int width, int height, const unsigned \
	char *bitmap );
extern void DrawUI_Bitmap( int x, int y, int w, int h, \
	const unsigned char *bitmap,unsigned long F, unsigned long B);
extern void DrawUI_Bitmap_Ex( int x, int y, int w, int h, \
	const unsigned char *bitmap,unsigned long F);

extern void DrawUI_Bitmap_Rever( int x, int y, int w, int h, \
	const unsigned char *bitmap,unsigned long F);
extern void DrawUI_Bitmap_Exx( int x, int y, int w, int h,\
	const unsigned char *bitmap, unsigned short F );

extern void UI_Draw_Vline( int fx, int fy, int width, int height, int color);

extern void draw_line(int x1, int y1, int x2, int y2, unsigned short color);


extern int GUI_Point(int x, int y, int color);
extern void  GUI_HLine(int x0, int y0, int x1, int color); 
extern void  GUI_RLine(int x0, int y0, int y1, int color); 
extern void  GUI_LineWith(int x0, int y0, int x1, int y1, int with, unsigned short color);
extern void  GUI_CircleFill(int x0, int y0, int r, unsigned short color);




extern void draw_fill(int fx, int fy, int width, int height, unsigned short val);
extern void draw_bitmap_meger(int fx, int fy, int width, int height, const unsigned char *bitmap );
extern void set_pos( int x, int y );

extern void Calc_Destination( int x0, int y0, int *x1, int *y1, int position, float length);

extern void UI_style(int x0, int y0, int hour_len, int min_len, int sec_len);

#endif

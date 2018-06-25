#ifndef __LCD_ST7735_H_
#define __LCD_ST7735_H_

#include "nrf_gpio.h"
#include "Board.h"


// LCD width and height
#define LCD_W    128
#define LCD_H    96

#define LCD_DC_SET()           nrf_gpio_pin_set(LCD_DC)
#define LCD_DC_CLR()           nrf_gpio_pin_clear(LCD_DC)

#define LCD_SPI_CS_SET()       nrf_gpio_pin_set(LCD_SPI_CS)
#define LCD_SPI_CS_CLR()       nrf_gpio_pin_clear(LCD_SPI_CS)

#define LCD_RES_SET()          nrf_gpio_pin_set(LCD_RES)
#define LCD_RES_CLR()          nrf_gpio_pin_clear(LCD_RES)

#define LCD_SDA_SET()          nrf_gpio_pin_set(LCD_SPI_SDA)
#define LCD_SDA_CLR()          nrf_gpio_pin_clear(LCD_SPI_SDA)

#define LCD_SCL_SET()          nrf_gpio_pin_set(LCD_SPI_SCL)
#define LCD_SCL_CLR()          nrf_gpio_pin_clear(LCD_SPI_SCL)

#if 0
#define LCD_BACK_LIGHT_PWR_OFF()          nrf_gpio_pin_set(LCD_PWR)
#define LCD_BACK_LIGHT_PWR_ON()          nrf_gpio_pin_clear(LCD_PWR)        
#else
#define LCD_BACK_LIGHT_PWR_OFF() pwm_stop()
#define LCD_BACK_LIGHT_PWR_ON()  pwm_start()
#endif

extern void LCD_Init(void);
extern void LCD_Config_Delay(void);
extern void LCD_Level_Set(int level);
extern void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
extern void BlockWrite(int pic);
extern void lcd_display(int enable);
extern void sync_frame(void);

extern void do_sync_frame( int from, int to );
extern void LCD_Draw( int x, int y, int w, int h, unsigned short*rect_bmp );
extern void LCD_ON(void);
extern void LCD_Fill( int x1, int y1, int x2, int y2, unsigned short color );
extern void LCD_Set_window ( int x1, int y1, int x2, int y2 );
extern void LCD_Draw_Sync( int x1, int y1, int x2, int y2 );
extern void LCD_OFF(void);

#endif



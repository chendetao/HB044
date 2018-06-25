#include "LCD_ST7735.h"
#include "nrf_delay.h"
#include "UserSetting.h"
#include "Task_Step.h"
#include "OSAL_Timer.h"
#include "Task_GUI.h"
#include "OSAL.h"
#include "Task_Battery.h"

#include "pwm.h"

unsigned short fb[LCD_H][LCD_W];
unsigned char lcd_enable_flag = 0;
unsigned long msDelay = 0;

void LCD_Config(void);

void LCD_SPI_Init(void)
{
	//1.CS
	nrf_gpio_cfg(
            LCD_SPI_CS,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	
	nrf_gpio_pin_set(LCD_SPI_CS);
	
	//2.SDA
	nrf_gpio_cfg(
            LCD_SPI_SDA,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_set(LCD_SPI_SDA);
	
	//3.SCL
	nrf_gpio_cfg(
            LCD_SPI_SCL,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_set(LCD_SPI_SCL);
	
	/*************SPI********************************************/
    
    #if 1
    NRF_SPI1->CONFIG =    (0<<0)    //MSB first
                        | (0<< 1)
                        | (0<< 2);
    NRF_SPI1->FREQUENCY = 0x80000000;     //8 Mbps
    NRF_SPI1->PSELSCK =  LCD_SPI_SCL;
    NRF_SPI1->PSELMOSI = LCD_SPI_SDA;
	
	NRF_SPI1->INTENCLR = ((1<<1)
	                    |(1<<4)
						|(1<<6)
						|(1<<8)
						|(1<<19)
						);
    
    NRF_SPI1->ENABLE = 0;
	#endif
    
	/*****************************************************************/
	
	nrf_gpio_cfg(
            LCD_DC,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_clear(LCD_DC);	  

	nrf_gpio_cfg(
            LCD_RES,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_set(LCD_RES);
}

#if 1
#define spi1_transfer(data) do\
{\
	int timeout = 0;\
	NRF_SPI1->ENABLE = 1;\
	NRF_SPI1->EVENTS_READY = 0;\
    NRF_SPI1->TXD = data;\
    while ( ( NRF_SPI1->EVENTS_READY == 0) && (timeout++<5000) );\
    NRF_SPI1->EVENTS_READY = 0;\
	NRF_SPI1->ENABLE = 0;\
}while(0)
#else
#define spi1_transfer(x) spi_write(x)
#endif

void spi_write(unsigned char val)
{
    for ( int i = 0; i < 8; i++ )
    {
        LCD_SCL_CLR();
        if ( val & 0x80 )
        {
            LCD_SDA_SET();
        }else{
            LCD_SDA_CLR();
        }
        
        val <<= 1;
        LCD_SCL_SET();
    }
    
    LCD_SCL_SET();
}

void WriteComm(unsigned char command)
{
	LCD_DC_CLR();
	
	LCD_SPI_CS_CLR();
	spi1_transfer( command );
	LCD_SPI_CS_SET();
}

void WriteData(unsigned char data)
{
	LCD_DC_SET();
	
	LCD_SPI_CS_CLR();
	spi1_transfer( data );
	LCD_SPI_CS_SET();
	
	LCD_DC_CLR();
}

void LCD_Init(void)
{
	LCD_SPI_Init();
	LCD_Config();
	
	nrf_gpio_cfg_output(LCD_PWR);
	LCD_BACK_LIGHT_PWR_OFF();

	pwm_init();
}

void LCD_Clear(void);

void LCD_Config(void)
{
	LCD_RES_SET();  
	nrf_delay_ms(2);
	
	LCD_RES_CLR();
	nrf_delay_ms(2);

	LCD_RES_SET();
	nrf_delay_ms(2);
	
	WriteComm(0x11);       // Sleep out

	nrf_delay_ms(5);       // Delay 120ms
	
	WriteComm(0x28); 	
    
	WriteComm(0xB1);     // ------------------------------------ST7735S Frame Rate-----------------------------------------//
	WriteData(0x05);   
	WriteData(0x3C);   
	WriteData(0x3C);   

	WriteComm(0xB2);     
	WriteData(0x05);   
	WriteData(0x3C);   
	WriteData(0x3C);   

	WriteComm(0xB3);     
	WriteData(0x05);   
	WriteData(0x3C);   
	WriteData(0x3C);   
	WriteData(0x05);   
	WriteData(0x3C);   
	WriteData(0x3C);     // ------------------------------------End ST7735S Frame Rate-----------------------------------------//

	WriteComm(0xB4);     //Dot inversion
	WriteData(0x03);   

	WriteComm(0xC0);     // ------------------------------------ST7735S Power Sequence-----------------------------------------//
	WriteData(0x0E);   
	WriteData(0x0E);   
	WriteData(0x04);   

	WriteComm(0xC1);     
	WriteData(0xC0);   

	WriteComm(0xC2);     
	WriteData(0x0D);   
	WriteData(0x00);   

	WriteComm(0xC3);     
	WriteData(0x8D);   
	WriteData(0x2A);   

	WriteComm(0xC4);     
	WriteData(0x8D);   
	WriteData(0xEE);   // ---------------------------------End ST7735S Power Sequence-------------------------------------//

	WriteComm(0xC5);   // VCOM
	WriteData(0x04);   

	WriteComm(0x36);   // MX, MY, RGB mode
	WriteData(0xC8);   

	WriteComm(0xE0);     
	WriteData(0x05);   
	WriteData(0x1A);   
	WriteData(0x0B);   
	WriteData(0x15);   
	WriteData(0x3D);   
	WriteData(0x38);   
	WriteData(0x2E);   
	WriteData(0x30);   
	WriteData(0x2D);   
	WriteData(0x28);   
	WriteData(0x30);   
	WriteData(0x3B);   
	WriteData(0x00);   
	WriteData(0x01);   
	WriteData(0x02);   
	WriteData(0x10);   

	WriteComm(0xE1);     
	WriteData(0x05);   
	WriteData(0x1A);   
	WriteData(0x0B);   
	WriteData(0x15);   
	WriteData(0x36);   
	WriteData(0x2E);   
	WriteData(0x28);   
	WriteData(0x2B);   
	WriteData(0x2B);   
	WriteData(0x28);   
	WriteData(0x30);   
	WriteData(0x3B);   
	WriteData(0x00);   
	WriteData(0x01);   
	WriteData(0x02);   
	WriteData(0x10); 

	WriteComm(0x3A);     //65k mode
	WriteData(0x05);

	LCD_Clear();	
}


void lcd_display( int enable)
{
	if ( enable == 0 )
	{
		WriteComm(0x28);
		WriteComm(0x10);
		LCD_BACK_LIGHT_PWR_OFF();		
		config.lcdEnable = 0;

		nrf_gpio_cfg_default(LCD_DC);
		nrf_gpio_cfg_default(LCD_SPI_SCL);
		nrf_gpio_cfg_default(LCD_SPI_SDA);
		nrf_gpio_cfg_default(LCD_RES);
		nrf_gpio_cfg_default(LCD_SPI_CS);
        // nrf_gpio_pin_set(BMA_POWER_PIN);
		
		config.enable = 0;
		lcd_enable_flag = 0;
		osal_start_timerEx( taskStepTaskId, TASK_STEP_BSTOTW_ENABLE_EVT, 500);
	} else
	{
		LCD_SPI_Init();
		LCD_Config_Delay();
	}
}

void LCD_Level_Set(int level)
{
	pwm_duty_set(level);	
}

void LCD_Config_Delay(void)
{
	LCD_Config();
	LCD_Level_Set(config.lcd_level);
	config.lcdEnable = 1;
}

void LCD_Clear(void)
{	
}

#include "Task_Motor.h"

#define COLORREF(r,g,b) ((( r & 0xF8)<<8)|(( g & 0xFC)<<3)|(b >> 3))

void LCD_Draw( int x1, int y1, int x2, int y2, unsigned short *rect_bmp )
{
    const unsigned short *p;
    
	WriteComm(0x2A); 		    // Set Column Address
	
    WriteData(2+(x1>>8));
	WriteData(2+(x1&0xFF)); 		// 00

	WriteData(2+(x2>>8));
	WriteData(2+(x2&0xFF)); 		// 127

	WriteComm(0x2B); 		    // Set Row Address
    
	WriteData(64+1+(y1>>8));
	WriteData(64+1+(y1&0xFF));
    
	WriteData(64+1+(y2>>8));	  
	WriteData(64+1+(y2&0xFF));
	
	WriteComm(0x2c);   

    p = (unsigned short *)rect_bmp;
    unsigned short val;
    
    for ( int xx = x1; xx <= x2; xx++ )
    {
        for ( int yy = y1; yy <= y2; yy++ )
        {
            val = *p++;			
			LCD_SPI_CS_CLR();
			LCD_DC_SET();
			spi1_transfer(val>>8);
			LCD_DC_CLR();
			LCD_SPI_CS_SET();
			
			LCD_SPI_CS_CLR();			
			LCD_DC_SET();			
			spi1_transfer(val&0xFF);
			LCD_DC_CLR();
			LCD_SPI_CS_SET();            
        }
    }    
}

void do_sync_frame( int from, int to )
{
	if ( config.lcdEnable == 0 ) { return; }
	
	WriteComm(0x2A); 		// Set Column Address
	WriteData(0x00);
	WriteData(0x00+2); 		// 00
	WriteData(0x00);
	WriteData(0x7F+2); 		// 127

	WriteComm(0x2B); 		// Set Page Address
	WriteData(0x00);
	WriteData(from+1);
	WriteData(0x00);	  
	WriteData(to+1);
	
	WriteComm(0x2c);	
		
	const unsigned short *p;
	unsigned short val;
	
    #if 0
	for ( int y = to-1,i=from; y >= from; y--,i++ )
	{
		p = fb[(LCD_H-1)-i]+(LCD_W-1);
        
		for ( int x = 0; x < LCD_W; x++ ) 
		{	
            val = *p--;			
			LCD_SPI_CS_CLR();
			LCD_DC_SET();
			spi1_transfer(val>>8);
			LCD_DC_CLR();
			LCD_SPI_CS_SET();
			
			LCD_SPI_CS_CLR();			
			LCD_DC_SET();			
			spi1_transfer(val&0xFF);
			LCD_DC_CLR();
			LCD_SPI_CS_SET();
		}
	}	
    #else
	for ( int y = from,i=from; y < to; y++,i++ )
	{
		p = fb[y];
        
		for ( int x = 0; x < LCD_W; x++ ) 
		{	
            val = *p++;			
			LCD_SPI_CS_CLR();
			LCD_DC_SET();
			spi1_transfer(val>>8);
			LCD_DC_CLR();
			LCD_SPI_CS_SET();
			
			LCD_SPI_CS_CLR();			
			LCD_DC_SET();			
			spi1_transfer(val&0xFF);
			LCD_DC_CLR();
			LCD_SPI_CS_SET();
		}
	}    
    #endif
	
    #if 1
	if ( lcd_enable_flag == 0 && from == 88 && to == 96 )
	{
		WriteComm(0x29);     //Display on
		
		nrf_delay_ms(50);
		{
			lcd_enable_flag = 1;
			LCD_BACK_LIGHT_PWR_ON();
		}			
	}  
    #else
	if ( lcd_enable_flag == 0 && from == 0 && to == 96 )
	{
		WriteComm(0x29);     //Display on
		
		nrf_delay_ms(50);
		{
			lcd_enable_flag = 1;
			LCD_BACK_LIGHT_PWR_ON();
		}			
	}    
    #endif
}


	
#include "string.h"
#include "Window.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_GUI.h"

#include "LCD_ST7735.h"
#include "UserSetting.h"
#include "Alarm.h"
#include "UI_Draw.h"

#include "UI_main_icon.h"
#include "ClockTick.h"
#include "UI_comm_icon.h"

#include "Task_Step.h"
#include "Task_Battery.h"
#include "Task_Motor.h"
#include "Task_Flash.h"

#include "Task_Battery.h"
#include "math.h"
#include "hufman.h"
#include "Color.h"
#include "jpeg_decode.h"

#define  PI 3.14159265      


unsigned char b_idx = 0;
unsigned char show_idx = 0;

void show_ui_version(void);
void show_ui_logo(void)
{	
    
}

/**
 * 8分法绘制圆
 */
static void draw_cicle_8( int xc, int yc, int x, int y, unsigned short c)
{
    set_pixel(xc + x , yc + y, c);
    set_pixel(xc - x , yc + y, c);
    set_pixel(xc + x , yc - y, c);
    set_pixel(xc - x , yc - y, c);
    set_pixel(xc + y , yc + x, c);
    set_pixel(xc - y , yc + x, c);
    set_pixel(xc + y , yc - x, c);
    set_pixel(xc - y , yc - x, c);    
}

void draw_cicle( int cx, int cy, int r, unsigned short c)
{
    int x = 0, y = r;
    
    float d = 3 - 2 * r;
    
    while( x <= y )
    {
        draw_cicle_8(cx, cy, x, y, c);
        
        if ( d < 0 ){
            d = d + 4 * x + 6;
        }else{
            d = d + 4 * (x-y) + 10;
            y--;
        }
        x++;
    }
}

void show_charge_battery(int x, int y )
{
	DrawUI_Bitmap_Ex((LCD_W-64)/2,(LCD_H-32)/2,64,32,charge_bmp_battery[b_idx],charge_color[b_idx]);
	DrawUI_Bitmap_Ex((LCD_W-64)/2,(LCD_H-32)/2,64,32,charge_bmp_battery[5],charge_color[5]);
	
	b_idx++;
	b_idx %= 5;
}

int get_level_idx( int level )
{
	if ( power.battery_level > 90 )
	{
		return 5;		
	}else if ( power.battery_level > 70 )
	{
		return 4;
	}else if ( power.battery_level > 50 )
	{
		return 3;
	}else if ( power.battery_level > 30 )
	{
		return 2;
	}else if ( power.battery_level > 10 )
	{
		return 1;
	}else{
		return 0;
	}
}

void UI_style_1(void)
{
	static unsigned char tick = 0;
	
	/************ 时间 **********/
	int hour = TimerHH();
	int minute = TimerMI();
	
	/********************* 电池 ********************/
	unsigned char level = get_level_idx( power.battery_level );

	if ( power.charge_flage == 1 )
	{
		DrawUI_JPEG(2,8,p_battery[b_idx]);
		b_idx++; b_idx %= 6;
	}else{
		DrawUI_JPEG(2,8,p_battery[level]);
	}	
		
	/************ 蓝牙 **********/
	if ( ble.isConnected == 1 )
	{
		DrawUI_JPEG(30,4,p_bletooth[0]);	
	}
	else
	{
		DrawUI_JPEG(30,4,p_bletooth[1]);
	}
		
	if ( config.time_format == 1 )
	{
		if ( TimerHH() > 11 )
		{
			DrawUI_Bitmap_Exx( 92, 8, 24, 16, BMP_am,0xFFFF);
			hour -= 12;
		}else{
			DrawUI_Bitmap_Exx( 92, 8, 24, 16, BMP_am,0xFFFF);
		}
		if ( hour == 0 ) hour = 12;
		
		/************ 时间 **********/
		DrawUI_Bitmap_Exx( 1, 44, 18, 40, Font_time_18x40[hour/10],0xFFFF);
		DrawUI_Bitmap_Exx( 1+18, 44, 18, 40, Font_time_18x40[hour%10],0xFFFF);	

		if(tick)
		{
			DrawUI_Bitmap_Exx( 1+18*2, 38, 18, 40, Font_time_18x40[10],0xFFFF);	
		}
		tick++;tick%=2;
				
		DrawUI_Bitmap_Exx( 1+18*3, 44, 18, 40, Font_time_18x40[minute/10],0xF800);		
		DrawUI_Bitmap_Exx( 1+18*4, 44, 18, 40, Font_time_18x40[minute%10],0xF800);		

		/************ 星期 **********/
		DrawUI_Bitmap_Exx( 92, 68, 32, 16, BMP_week[TimerWK()%7],0xFFFF);	
		
		/************ 日期 **********/
		DrawUI_Bitmap_Exx( 92, 46, 7, 16, Font_data_7x16[TimerMM()/10],0xFFFF);		
		DrawUI_Bitmap_Exx( 99, 46, 7, 16, Font_data_7x16[TimerMM()%10],0xFFFF);	
		DrawUI_Bitmap_Exx( 106, 46, 7, 16, Font_data_7x16[10],0xFFFF);		
		DrawUI_Bitmap_Exx( 113, 46, 7, 16, Font_data_7x16[TimerDD()/10],0xFFFF);		
		DrawUI_Bitmap_Exx( 120, 46, 7, 16, Font_data_7x16[TimerDD()%10],0xFFFF);	
	}
	else
	{
		/************ 时间 **********/
		DrawUI_Bitmap_Exx( 2, 32, 24, 56, Font_time_24x56[hour/10],0xFFFF);		
		DrawUI_Bitmap_Exx( 2+25, 32, 24, 56, Font_time_24x56[hour%10],0xFFFF);	
		
		if(tick)
		{
			DrawUI_Bitmap_Exx( 2+25*2, 26, 24, 56, Font_time_24x56[10],0xFFFF);		
		}
		tick++;tick%=2;
		
		DrawUI_Bitmap_Exx( 2+25*3, 32, 24, 56, Font_time_24x56[minute/10],0xF800);		
		DrawUI_Bitmap_Exx( 2+25*4, 32, 24, 56, Font_time_24x56[minute%10],0xF800);		

		/************ 星期 **********/
		DrawUI_Bitmap_Exx( 56, 8, 32, 16, BMP_week[TimerWK()%7],0xFFFF);
		
		/************ 日期 **********/
		DrawUI_Bitmap_Exx( 88, 8, 7, 16, Font_data_7x16[TimerMM()/10],0xFFFF);		
		DrawUI_Bitmap_Exx( 88+7, 8, 7, 16, Font_data_7x16[TimerMM()%10],0xFFFF);	
		DrawUI_Bitmap_Exx( 88+7*2, 8, 7, 16, Font_data_7x16[10],0xFFFF);		
		DrawUI_Bitmap_Exx( 88+7*3, 8, 7, 16, Font_data_7x16[TimerDD()/10],0xFFFF);		
		DrawUI_Bitmap_Exx( 88+7*4, 8, 7, 16, Font_data_7x16[TimerDD()%10],0xFFFF);	
	}	 
}

unsigned char fristBootFlag = 1;
unsigned char showLogoFlag = 1;
	
void UI_style_2(void)
{
	/************ 表盘 **********/
	DrawUI_JPEG_xx(0,0,jpg_main_2);

	/************ 时针分针 **********/
	UI_style(64, 48, 30, 38, 0);
	
	/************ 中心点 **********/
	GUI_CircleFill(64,48,5,0X00);		
}

/******************************************************************************
 *                  END                                                        *
 *                                                                             *
 ******************************************************************************/

unsigned long win_main_proc(unsigned short wid, unsigned long msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;  
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
		}			
		
		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_CREATE );
	}
	
	if ( msg_type & WINDOW_UPDATE )
	{
		win_ticks++;
		
		if ( win_ticks > 2 )
		{
			showLogoFlag = 0;
			fristBootFlag = 0;
		}
	
		if ( power.charge_flage == 1 )
		{
			if ( win_ticks > 30 )				
			{
				lcd_display(0);
				
				return ( msg_type ^ WINDOW_UPDATE );
			}
		}
		else 
		{
			if ( win_ticks > 10 )				
			{
				lcd_display(0);
				
				return ( msg_type ^ WINDOW_UPDATE );
			}
		}
		memset( fb, 0, sizeof(fb));	

		if ( showLogoFlag == 1 )
		{
			if ( win_ticks > 1 )
			{
				if ( fristBootFlag == 1 )
				{
					show_ui_version();
				}else{
					show_ui_logo(); 
				}
			}
		}else
		{            
            if ( power.charge_flage == 1 )
            {
                show_charge_battery(0,0);
            } else {
                if ( config.ui_style == 0 )
                {
                    UI_style_1();
                }
				else
                {
                    UI_style_2();
                }
              
                b_idx = 0;
            }               
		}
		
        sync_frame();
	        
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{	
		win_ticks = 0;
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
			msg_type |= WINDOW_UPDATE;
		}else{
			
			showLogoFlag = 0; // 显示Vxxx期间按键.           
			
			if ( power.charge_flage == 0 )
			{
				window_push(window_get(win_current));
				msg_type |= WINDOW_DISTORY;
			}
            
            msg_type |= WINDOW_UPDATE;
		}
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{
		win_ticks = 0;
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
			
			msg_type |= WINDOW_UPDATE;
			
			return ( msg_type ^ WINDOW_PRESS );
        }else {          
            if ( power.charge_flage == 0 )
            {
                config.ui_style++; 
                config.ui_style %= 2;
            }               
		}
		
		msg_type |= WINDOW_UPDATE;
		
		return ( msg_type ^ WINDOW_PRESS );
	}
	
	if ( msg_type & WINDOW_NOTIFY )
	{           
		if ( power.charge_flage == 1 )
		{
			return ( msg_type ^ WINDOW_NOTIFY );
		}
		
        window_push( win_current );
        win_current = NOTIFY_WIN_ID_GET();
        window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0);
		
		return ( msg_type ^ WINDOW_NOTIFY );
	}
	
	if ( msg_type & WINDOW_DISTORY )
	{
		window_pop(&win_current);

		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}

    return 0;
}


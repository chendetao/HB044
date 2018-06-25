
#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"

#include "UI_info_icon.h"
#include "UI_comm_icon.h"
#include "UI_Comm_Draw.h"
#include "UI_main_icon.h"
#include "UI_win_info.h"
#include "UI_alarm_icon.h"
#include "HFMA2Ylib.h"
#include "version.h"
#include "UI_win_more.h"
#include "UI_sport_icon.h"

#define COLOR_B      0X0000
#define COLOR_F      0X072E

extern void generate_mac_2_hex(unsigned char *mac_buf);
extern unsigned char DZ[32];
extern void DoRect8x16( int cx, int cy, const unsigned char pic[32]);
unsigned char showInfoFlag;

extern void EntryDeepSleepMode(void);
extern void ExitDeepSleepMode(void);

void show_information_val(int x, int y )
{
    unsigned char mac_buf[18];
    
    generate_mac_2_hex(mac_buf);
    
	ExitDeepSleepMode();
    
    const char *p = "MAC";
    
    for ( int i = 0; i < 3; i++ )
    {
        ASCII_GetData(*p++,ASCII_8X16, DZ);
        DoRect8x16(52+i*8, 0+16, DZ);        
    }

    for ( int i = 0; i < 8; i++ )
    {
        ASCII_GetData(mac_buf[i],ASCII_8X16, DZ);
        DoRect8x16( 8+24+i*8, 16+16, DZ);        
    }
    for ( int i = 9; i < 17; i++)
    {
        ASCII_GetData(mac_buf[i],ASCII_8X16, DZ);
        DoRect8x16( 8+24+(i-9)*8, 32+16, DZ);        
    }	

	// VX.Y.Z
    
    mac_buf[0] = 'V';
    mac_buf[1] = '0'+VERSION_MAJOR;
    mac_buf[2] = '.';
    mac_buf[3] = '0'+VERSION_MINOR;
    mac_buf[4] = '.';
    mac_buf[5] = '0'+VERSION_REVISON;
    
    for ( int i = 0; i < 6; i++ )
    {
        ASCII_GetData(mac_buf[i],ASCII_8X16, DZ);
        DoRect8x16(40+i*8, 48+16, DZ);        
    }
    
	EntryDeepSleepMode();
}

unsigned char show_info_ui = 0;

extern void show_qr(void);

void show_app_qr(void)
{
	
}

#include "jpeg_decode.h"

void show_information(int x, int y )
{	
	draw_fill(0,0,LCD_W,LCD_H,COLOR_B);
	
	if ( showInfoFlag == 1 )
	{
		switch ( show_info_ui )
		{
		case 0:
				show_qr();
				break;
		case 1:

				show_information_val( 56, 29 );

				break;
		default:
				break;
		}		
		
	}else{
		if ( more_type == MORE_TYPE_INFO )
		{	
			DrawUI_Bitmap_Exx( 6, 8,64,80,BMP_INFO2,RED);
			DrawUI_Bitmap_Exx( 6, 8,64,80,BMP_INFO1,0xFFFF);
			DrawUI_Bitmap_Exx( 76,36,42,24,BMP_INFO,0xFFFF);
		}
		if ( more_type ==  MORE_TYPE_BACK )
		{
			DrawUI_Bitmap_Exx(5,16,64,64,BMP_more_back2, RED);	
			DrawUI_Bitmap_Exx(5,16,64,64,BMP_more_back1, 0XFFFF);	
			DrawUI_Bitmap_Exx(79,36,44,24,BMP_more_back, 0XFFFF);			
		}
	}
}

unsigned long win_info_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;  showInfoFlag = 0;more_type = MORE_TYPE_INFO;

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
		
		if ( win_ticks > 10 )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}
           		
		show_information( 28, 20 );
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
			
			if ( showInfoFlag == 0 )
			{		
				if( more_type == MORE_TYPE_INFO )
				{
					more_type = MORE_TYPE_BACK;
					msg_type |= WINDOW_UPDATE;
				}
				else if ( more_type == MORE_TYPE_BACK )
				{
					more_type = MORE_TYPE_SLEEP;
					window_push(5);
					msg_type |= WINDOW_DISTORY;	
				}
				
			
			}else{
				show_info_ui++; show_info_ui %= 2;
				msg_type |= WINDOW_UPDATE;
			}				
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
		}

		if ( showInfoFlag == 0 )
		{
			if( more_type == MORE_TYPE_INFO )
			{
				showInfoFlag = 1;
			}
			else
			{
				window_push(4);
				msg_type |= WINDOW_DISTORY;
				more_type = MORE_TYPE_SLEEP;
			}
							
		}else{
			showInfoFlag = 0;
		}
		
		msg_type |= WINDOW_UPDATE;
		
		return ( msg_type ^ WINDOW_PRESS );
	}
	
	if ( msg_type & WINDOW_NOTIFY )
	{   
        /* 当前窗体入栈 */
        window_push( win_current );
        
        /* 通知界面作为当前界面 */
        win_current = NOTIFY_WIN_ID_GET();
        
        /* 调用窗体回调函数以便创建窗体  */
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

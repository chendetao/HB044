#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_win_findphone.h"
#include "UI_Draw.h"
#include "UI_main_icon.h"
#include "jpeg_decode.h"
#include "UI_win_more.h"

#include "UI_findphone_icon.h"
#include "Task_Finder.h"

#define COLOR_B      0X0000
#define COLOR_F      0X77E0

unsigned char showFlag;

void show_findphone_icon(int x, int y )
{		
	if ( finder.isFound == 1 )
	{
		DrawUI_Bitmap_Exx( 19,0,90,96,BMP_find_ok2, RED);
		DrawUI_Bitmap_Exx( 19,0,90,96,BMP_find_ok1, 0xFFFF);
	} else {
		
		if ( finder.state == FIND_PHONE_STATE_STOP )
		{	
			DrawUI_Bitmap_Exx( 6,8,64,80,BMP_main2, RED);
			DrawUI_Bitmap_Exx( 6,8,64,80,BMP_main1, 0xFFFF);
			DrawUI_Bitmap_Exx( 80,36,42,24,BMP_FIND, 0xFFFF);
		}else{                  
			DrawUI_Bitmap_Exx( 31,4,66,64,BMP_find2, RED);
			DrawUI_Bitmap_Exx( 31,4,66,64,BMP_find1, 0xFFFF);
			DrawUI_Bitmap_Exx( 34,76,60,16,BMP_finding, 0xFFFF);
		}
	}
}

unsigned long win_findphone_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0; showFlag = 0; 
		finder.state = FIND_PHONE_STATE_STOP;
		
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
		
        /* 当前不处于查找状态中，3秒自动灭屏 */
        if ( (win_ticks > 10) && (finder.state != FIND_PHONE_STATE_FINDING ))
        {
            lcd_display(0); 
            finder.isFound = 0;
			
			return ( msg_type ^ WINDOW_UPDATE );
        }
        
        /* 11秒后自动停止查找 */
        if ( (win_ticks > 22) ) 
        {
			lcd_display(0); 
			
			finder.isFound = 0;
			
			if (finder.state == FIND_PHONE_STATE_FINDING )
			{
				osal_set_event ( taskFinderTaskId, FIND_HONE_TASK_STOP_EVT );
			}
            finder.state = FIND_PHONE_STATE_STOP;
			
			return ( msg_type ^ WINDOW_UPDATE );
        }		
				
		memset(fb, 0, sizeof(fb));
		show_findphone_icon( 28, 20 );
		sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);			
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
			
			if (finder.state != FIND_PHONE_STATE_STOP )
			{
				return ( msg_type ^ WINDOW_TOUCH );
			}else
            {
                finder.state = FIND_PHONE_STATE_STOP;
                osal_set_event ( taskFinderTaskId, FIND_HONE_TASK_STOP_EVT );                
//                window_push(window_get(win_current));
				window_push(9);
                msg_type |= WINDOW_DISTORY;
            }   
			
		}
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{		
		/***********************************************
		 *                                             *
		 * 长按开始查找/取消查找手机                   *
		 *                                             *
		 **********************************************/                                             
		 
		win_ticks = 0;
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);			
			msg_type |= WINDOW_UPDATE;

			return ( msg_type ^ WINDOW_PRESS );
		}
		
		if ( finder.state == FIND_PHONE_STATE_STOP )
		{
			finder.state = FIND_PHONE_STATE_FINDING;
			showFlag = 0;  
			finder.isFound = 0;
			osal_set_event ( taskFinderTaskId, FIND_HONE_TASK_START_EVT );
		}else
		{
			finder.state = FIND_PHONE_STATE_STOP;
			osal_set_event ( taskFinderTaskId, FIND_HONE_TASK_STOP_EVT );
		}
		
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
		finder.isFound = 0;
        // 退出该界面时，发现状态更改为 0，以便下次可进入发现在状态.
        finder.state = FIND_PHONE_STATE_STOP;		
		
		window_pop(&win_current);
		
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}	
	
	return 0;
}

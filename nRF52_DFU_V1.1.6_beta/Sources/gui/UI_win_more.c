#include "string.h"
#include "Window.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_GUI.h"

#include "LCD_ST7735.h"
#include "UserSetting.h"
#include "Alarm.h"
#include "UI_Draw.h"

#include "UI_more_icon.h"
#include "UI_main_icon.h"
#include "ClockTick.h"
#include "UI_comm_icon.h"
#include "UI_win_more.h"
#include "UI_sport_icon.h"

#include "Task_Step.h"
#include "Task_Battery.h"
#include "Task_Motor.h"
#include "Task_Flash.h"

#include "math.h"
#include "hufman.h"
#include "Color.h"
#include "jpeg_decode.h"

unsigned char showMoreFlag;
unsigned char showBackFlag = 0;
More_Type more_type;

void show_more(void)
{
	if (showMoreFlag == 0)
	{
        DrawUI_JPEG( 2, 12, ipeg_more);  
		DrawUI_Bitmap_Exx( 70, 36,56,24,BMP_more,0xFFFF);
	}
}


unsigned long win_more_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;  showMoreFlag = 0;

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

		memset( fb, 0, sizeof(fb));
		
		show_more();
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
		}
		else
		{
			if ( showMoreFlag == 0 )
			{
			window_push(window_get(win_current));
			msg_type |= WINDOW_DISTORY;	
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
		
		if( showMoreFlag == 0 )
		{
			showMoreFlag = 1;
			window_push(5);
			msg_type |= WINDOW_DISTORY;	
		}
		else if( showMoreFlag ==1 )
		{
            if ( more_type == MORE_TYPE_BACK )
            {
              showMoreFlag = 0;
            }
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
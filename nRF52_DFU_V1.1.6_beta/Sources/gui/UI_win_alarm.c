#include "string.h"
#include "Window.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_GUI.h"
#include "LCD_ST7735.h"
#include "QR_Utils.h"
#include "Alarm.h"

#include "UI_win_hr.h"
#include "UserSetting.h"
#include "UI_Draw.h"

#include "UI_win_alarm.h"
#include "UI_alarm_icon.h"
#include "UI_comm_icon.h"
#include "UI_sport_icon.h"
#include "UI_main_icon.h"
#include "UI_pedometer_icon.h"
#include "UI_win_more.h"

#define COLOR_B      0X0000
#define COLOR_F      0XF3E0

#include "jpeg_decode.h"

void show_alarm(int x, int y, int hour, int minute )
{
    DrawUI_Bitmap_Exx( 2, 16, 56, 64, BMP_alarm2,BLUE);	
	DrawUI_Bitmap_Exx( 2, 16, 56, 64, BMP_alarm1,0XFFFF);	

	DrawUI_Bitmap_Exx( 62, 32, 12, 32, font_12x32[hour/10],0XFFFF);	
	DrawUI_Bitmap_Exx( 75, 32, 12, 32, font_12x32[hour%10],0XFFFF);
	DrawUI_Bitmap_Exx( 88, 32, 12, 32, font_12x32[10],0XFFFF);
	DrawUI_Bitmap_Exx( 101, 32, 12, 32, font_12x32[minute/10],0XFFFF);
	DrawUI_Bitmap_Exx( 114, 32, 12, 32, font_12x32[minute%10],0XFFFF);
}

unsigned long win_alarm_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{	
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;

		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
		}
		
		show_alarm(0,0,alarm.g_Ahour_next, alarm.g_Amin_next);
		
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
						
		memset ( fb,0,sizeof(fb) );
		
		show_alarm(0,0,alarm.g_Ahour_next, alarm.g_Amin_next);
		sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{	
		if ( config.lcdEnable == 0)
		{
			lcd_display(1);
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
//			window_push(window_get(win_current));
			window_push(8);
			msg_type |= WINDOW_DISTORY;
		}			
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{		
		win_ticks = 0;		
	
		if ( config.lcdEnable == 0)
		{
			lcd_display(1);
			msg_type |= WINDOW_UPDATE;
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
		window_pop(&win_current);
		window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
		
		return ( msg_type ^ WINDOW_DISTORY );
	}

    return 0;
}

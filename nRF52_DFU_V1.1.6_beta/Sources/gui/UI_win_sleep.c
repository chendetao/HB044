#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"

#include "UI_sleep_icon.h"
#include "UI_comm_icon.h"

#include "sleep_algorithm.h"
#include "UI_comm_icon.h"
#include "UI_main_icon.h"
#include "UI_win_sleep.h"
#include "jpeg_decode.h"
#include "UI_pedometer_icon.h"
#include "UI_win_more.h"

void DrawSleepTimer( int x, int y, int deep_time, int light_time )
{
    float val_deep = (int)deep_time/60.0f + 0.05f;
    float val_light = (int)light_time/60.0f + 0.05f;
    
    int dh = (int)val_deep;
    int dl = (int)((val_deep-dh)*10);
    int lh = (int)val_light;
    int ll = (int)((val_light-lh)*10);
    
    int vh = dh+lh;
    int vl = dl + ll;
    if ( vl > 9 )
    {
      vl -= 10;
      vh ++;
    }
	
	DrawUI_Bitmap_Exx( 2, 16, 68, 64, BMP_sleep2,SLEEP);
	DrawUI_Bitmap_Exx( 2, 16, 68, 64, BMP_sleep1,0XFFFF);

	y = 32;

	if ( vh > 9 )
	{
		DrawUI_Bitmap_Exx( 72, y, 12, 32, font_12x32[vh/10],0XFFFF);

		x = 83;
	}else{
		x = 76;
	}
		
	DrawUI_Bitmap_Exx( x, y, 12, 32, font_12x32[vh%10],0XFFFF);
	DrawUI_Bitmap_Exx( x+12, y, 12, 32, font_12x32[11],0XFFFF);
	DrawUI_Bitmap_Exx( x+24, y, 12, 32, font_12x32[vl%10],0XFFFF);
	
	DrawUI_Bitmap_Exx( x+38,32+14 , 6, 16, BMP_sleep_h,0XFFFF);
}

unsigned long win_sleep_proc(unsigned short wid, unsigned short msg_type, 
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
		
		if ( win_ticks > 10 )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}
				
		memset(fb,0,sizeof(fb));
		DrawSleepTimer(0,0,AutoSleep.out_TotalDeepTime, AutoSleep.out_TotalLightTime );
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
//			window_push(window_get(win_current));
			window_push(6);
			msg_type |= WINDOW_DISTORY;		
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

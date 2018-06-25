#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Motor.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_win_shutdown.h"
#include "UI_Draw.h"
#include "UI_shutdown_icon.h"
#include "bma253.h"
#include "Task_Battery.h"
#include "UI_main_icon.h"
#include "UI_win_more.h"
#include "UI_sport_icon.h"


#define COLOR_B      0X0000
#define COLOR_F      0x1F<<11

extern void ConnectionTerminate( int enable );
extern unsigned char showLogoFlag;
/**
 * 关机开机回调方法.
 */
void shutdown_cb( int shutdown )
{
    if ( shutdown == 1 )
    {
        /* 关机 */
        
        ConnectionTerminate(1);  // 终止连接
        
        /* 关闭蓝牙广播 */
        
        make_bma250_to_deep_sleep(1);
    }else
    {
        /* 开机 */
        
        /* 打开蓝牙广播 */    
        
        ConnectionTerminate(0);
        
        make_bma250_to_deep_sleep(0); 
    }
	
	osal_set_event( taskMotorTaskId, TASK_MOTOR_ACTION_DONE_EVT );	
}


#include "jpeg_decode.h"

void show_shutdown_icon(int x, int y )
{		
		DrawUI_Bitmap_Exx( 4, 16,60,64,BMP_power2,RED);
		DrawUI_Bitmap_Exx( 4, 16,60,64,BMP_power1,0xFFFF);
		DrawUI_Bitmap_Exx( 68, 36,56,24,BMP_power,0xFFFF);
}

unsigned long win_shutdown_proc(unsigned short wid, unsigned short msg_type, 
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
 		
		memset(fb, 0x00, sizeof(fb));

		show_shutdown_icon( 28, 20 );
		sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{		
		if ( config.shutdown == 1 )
		{
			return ( msg_type ^ WINDOW_TOUCH );
		}
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);			
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
			window_push(window_get(win_current));
			msg_type |= WINDOW_DISTORY;	
		}
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{			
		if ( config.shutdown == 0 )
		{
			if ( config.lcdEnable == 0 )
			{
				lcd_display(1);
				win_ticks = 0;
				msg_type |= WINDOW_UPDATE;
			}
			else
			{
				shutdown_cb(1);
				lcd_display(0);
				config.shutdown = 1;
				osal_stop_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT );
				osal_clear_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
			}
		}else 
		{
			if ( (power.battery_level >= 1) ||
				(power.charge_flage == 1) )
			{
			shutdown_cb(0);
			lcd_display(1);
			config.shutdown = 0;
				
			window_tack_reset();
			window_push(0);   // 开机跳转主页面
			msg_type |= WINDOW_DISTORY;
			}
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

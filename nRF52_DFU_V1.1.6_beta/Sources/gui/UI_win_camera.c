
#include "string.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Window.h"
#include "UI_Draw.h"
#include "LCD_ST7735.h"
#include "UserSetting.h"
#include "btprotocol.h"
#include "Task_GUI.h"

#include "UI_win_camera.h"
#include "UI_camera_icon.h"
#include "jpeg_decode.h"
#include "UI_main_icon.h"

#define COLOR_B      0X0000
#define COLOR_F      0xFFFF

void show_camera( int x, int y )
{
	draw_fill(0,0,LCD_W,LCD_H,COLOR_B);
	
	DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_camera2,RED);
	DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_camera1,0xFFFF);
}

unsigned long win_camera_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
	unsigned char take_photo_cmd[20] = {0xFC,0x19,};
	
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
		
		if ( win_ticks > 45 )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}

		show_camera( 28, 20 );
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
			// Todo : 拍照	
			take_photo_cmd[2] = 0x00;
			take_photo_cmd[3] = 0x81;			
		
			bt_protocol_tx( take_photo_cmd, sizeof(take_photo_cmd) );
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
		}else{
			// Todo : 退出
			
			take_photo_cmd[2] = 0x80;
			take_photo_cmd[3] = 0x00;
			
			bt_protocol_tx( take_photo_cmd, sizeof(take_photo_cmd) );
						
			msg_type |= WINDOW_DISTORY;
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


#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"

#include "UI_pedometer_icon.h"
#include "UI_comm_icon.h"
#include "UI_Comm_Draw.h"
#include "QR_Utils.h"
#include "UI_win_pedometer.h"
#include "UI_main_icon.h"

#define COLOR_B      0X0000
#define COLOR_F      0xFFFF

#include "jpeg_decode.h"

void show_pedometer(int x, int y )
{
	DrawUI_JPEG(0,12,jpg_pedometer);

	int val = pedometer.counter % 100000;
	DrawUI_Bitmap_Exx(63,y,12,32,font_12x32[val/10000],0xFFFF);
	val %= 10000;
	DrawUI_Bitmap_Exx(76,y,12,32,font_12x32[val/1000],0xFFFF);
	val %= 1000;
	DrawUI_Bitmap_Exx(89,y,12,32,font_12x32[val/100],0xFFFF);
	val %= 100;
	DrawUI_Bitmap_Exx(102,y,12,32,font_12x32[val/10],0xFFFF);
	val %= 10;
	DrawUI_Bitmap_Exx(115,y,12,32,font_12x32[val],0xFFFF);
}

void show_qr(void)
{
	 QR_Copy_Image(fb);
}

extern void load_pedometer(unsigned long last_pedometer);

unsigned char show_qr_flag = 0;
unsigned long win_pedometer_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;  show_qr_flag = 0;

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
		
		if (( (win_ticks > 5) && (show_qr_flag == 0) )
		|| ( win_ticks > 30 ) )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}
		
		memset( fb, 0, sizeof(fb));
		if ( (show_qr_flag == 1) && (ble.isConnected == 0))
		{
            show_qr();
		}else{

			show_pedometer( 0, 32);

            
            if ( show_qr_flag == 1 )
            {
                show_qr_flag = 0;
            }            
		}
        
        sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 1000);
				
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
			
			if ( show_qr_flag == 0 )
			{
				window_push(window_get(win_current));
				msg_type |= WINDOW_DISTORY;		
				osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
				return ( msg_type ^ WINDOW_TOUCH );	
			}else 
			{
				if ( ble.isConnected == 1)
				{
					show_qr_flag = 0;
					osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
				}
			}
		}
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{	
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
			
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
			
			return ( msg_type ^ WINDOW_PRESS );
		}
		
		memset( fb, 0, sizeof(fb));
		if ( (show_qr_flag == 0) &&
			(ble.isConnected == 0) ){
			show_qr_flag = 1;
		}else{
			show_qr_flag = 0;
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
		show_qr_flag = 0;		
		window_pop(&win_current);
        
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}	
	
	return 0;
}

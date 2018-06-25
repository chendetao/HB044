#include "string.h"
#include "Window.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_GUI.h"
#include "Task_Hr.h"

#include "LCD_ST7735.h"
#include "QR_Utils.h"

#include "UI_win_hr.h"
#include "UserSetting.h"
#include "UI_Draw.h"
#include "jpeg_decode.h"

#include "UI_hr_icon.h"
#include "UI_comm_icon.h"
#include "UI_Comm_Draw.h"
#include "UI_main_icon.h"
#include "UI_sport_icon.h"

#define COLOR_B      0X0000
#define COLOR_F      0xFFFF

#define HR_COLOR_B   0x0000
#define HR_COLOR_F


void ui_win_hr_ready(void)
{
	DrawUI_Bitmap_Exx( 28, 4,72,64,BMP_hr_seach2,RED);
	DrawUI_Bitmap_Exx( 28, 4,72,64,BMP_hr_seach1,0xFFFF);
	DrawUI_Bitmap_Exx( 32, 76,74,16,BMP_hr_checking,0xFFFF);
}

void ui_win_hr_done(void)
{
	int val_1 = (int)hr.hr;
	
	DrawUI_Bitmap_Exx( 8, 2,24,24,BMP_hr_hurt,BLUE);
	
	DrawUI_Bitmap_Exx( 48, 2,8,24,Font_hr_8x24[val_1/100],0xFFFF);
	DrawUI_Bitmap_Exx( 57, 2,8,24,Font_hr_8x24[(val_1/10)%10],0xFFFF);
	DrawUI_Bitmap_Exx( 66, 2,8,24,Font_hr_8x24[val_1%10],0xFFFF);	
	
	DrawUI_Bitmap_Exx( 75, 10,24,16,BMP_hr_bpm,0xFFFF);

	int val_2 = (int)hr.hp;
	int val_3 = (int)hr.lp;

	DrawUI_Bitmap_Exx( 8, 36,24,24,BMP_hr_pressure,GREEN);

	DrawUI_Bitmap_Exx(47,36,8,24,Font_hr_8x24[(val_2/100)%10],0xFFFF);
	DrawUI_Bitmap_Exx(55,36,8,24,Font_hr_8x24[(val_2/10)%10],0xFFFF);	
	DrawUI_Bitmap_Exx(64,36,8,24,Font_hr_8x24[(val_2%10)%10],0xFFFF);	
	
	DrawUI_Bitmap_Exx(72,36,8,24,Font_hr_8x24[10],0xFFFF);
	
	DrawUI_Bitmap_Exx(80,36,8,24,Font_hr_8x24[(val_3/10)%10],0xFFFF);	
	DrawUI_Bitmap_Exx(88,36,8,24,Font_hr_8x24[(val_3%10)%10],0xFFFF);	
	
	DrawUI_Bitmap_Exx(97,44, 24, 16, BMP_hr_mmhg, 0xFFFF);

	
	int val_4 = (int)hr.sp_h;
	DrawUI_Bitmap_Exx( 8, 70,24,24,BMP_hr_spo2,RED);

	DrawUI_Bitmap_Exx(48,70,8,24,Font_hr_8x24[(val_4/10)%10],0xFFFF);
	DrawUI_Bitmap_Exx(57,70,8,24,Font_hr_8x24[val_4%10],0xFFFF);		

	DrawUI_Bitmap_Exx(66,78, 24, 16, BMP_hr_percent, 0xFFFF);
}

void ui_win_hr_error(void)
{	
	DrawUI_Bitmap_Exx(0,0, 128, 96, BMP_hr_error2, RED);
	DrawUI_Bitmap_Exx(0,0, 128, 96, BMP_hr_error1, 0xFFFF);
}

void ui_win_hr_none(void)
{	
	DrawUI_JPEG(4,12,jpg_hr_hurt);
	DrawUI_Bitmap_Exx( 70, 36,56,24,BMP_hr_health,0xFFFF);
}

void ui_win_hr_stop(void)
{
	ui_win_hr_done();
}

unsigned long win_hr_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{	
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0; last_hr = 0; need_mTicks = 8000;
		to_close = 0;
        
		draw_fill(0,0,96,94,COLOR_B);

		hr.stat = HR_DECT_STAT_NONE;		
		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
		}
		
		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_CREATE );
	}
	
	if ( msg_type & WINDOW_UPDATE )
	{
		win_ticks++; to_close++;

        if ( (win_ticks > 250) || ((hr.stop == 1) && (to_close > 10)) )
        {
            lcd_display(0);
            
            return ( msg_type ^ WINDOW_UPDATE );
        }
		
		memset(fb,0,sizeof(fb));
	
        switch ( hr.stat )
        {         
        case HR_DECT_STAT_NONE:
            ui_win_hr_none();
		    break;			
        case HR_DECT_STAT_STOP:
            ui_win_hr_stop();
            break;
		case HR_DECT_STAT_DECTING:
        case HR_DECT_STAT_NORMAL:
            ui_win_hr_ready();
            break;
        case HR_DECT_STAT_ERROR:
            ui_win_hr_error();
            break;
        case HR_DECT_STAT_DONE:
            ui_win_hr_done();
            break;
        default:
            break;
        }
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		if ( last_hr != hr.hr || hr.stat == HR_DECT_STAT_NORMAL
				|| hr.stat == HR_DECT_STAT_DONE
				|| hr.stat == HR_DECT_STAT_ERROR 
				|| hr.stat == HR_DECT_STAT_NONE
				|| hr.stat == HR_DECT_STAT_STOP )
		{		
			sync_frame();
			
//			last_hr = hr.hr;
		}
				
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{	
		if ( hr.stat != HR_DECT_STAT_ERROR
			&& hr.stat != HR_DECT_STAT_NONE 
			&& hr.stat != HR_DECT_STAT_STOP
			&& hr.stop != 1)
		{
			return ( msg_type ^ WINDOW_TOUCH );
		}		
		
		if ( config.lcdEnable == 0)
		{
			lcd_display(1);
			win_ticks = 0; to_close = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
			window_push(window_get(win_current));
			msg_type |= WINDOW_DISTORY;
		}			
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{
		win_ticks = 0; to_close = 0;
		
		if ( config.lcdEnable == 0)
		{
			lcd_display(1);
			
			// fix this bug
			msg_type |= WINDOW_UPDATE;

			return ( msg_type ^ WINDOW_PRESS );
		}
		
		if ( hr.stop == 1 )
		{
			need_mTicks = 8000; last_hr = 0;
			hr.measure = (0x1<<0)|(0x1<<2);
			osal_set_event ( taskHrTaskId, TASK_HR_START_EVT );
		} else
		{
			hr.stop = 1;
			hr.stat = HR_DECT_STAT_NONE;
			osal_set_event ( taskHrTaskId, TASK_HR_STOP_EVT );
		}
	
		osal_set_event ( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_PRESS );
	}
	
	if ( msg_type & WINDOW_NOTIFY )
	{  
		if ( ( hr.stat == HR_DECT_STAT_DECTING ) || ( hr.stat == HR_DECT_STAT_NORMAL )
			|| ( hr.stat == HR_DECT_STAT_DONE ) )
		{
			osal_set_event( taskHrTaskId, TASK_HR_STOP_EVT ); 
		}		
		
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
		if ( hr.stop != 1 )
		{
			osal_set_event ( taskHrTaskId, TASK_HR_STOP_EVT );
		}
		
		if ( hr.stat != HR_DECT_STAT_NONE )
		{
			hr.stat = HR_DECT_STAT_NONE;
		}
		
		window_pop(&win_current);
		
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}

    return 0;
}

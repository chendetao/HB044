//#include "string.h"
//#include "Window.h"

//#include "OSAL.h"
//#include "OSAL_Timer.h"
//#include "Task_GUI.h"
//#include "Task_Hr.h"

//#include "LCD_ST7735.h"
//#include "QR_Utils.h"

//#include "UI_win_hr.h"
//#include "UserSetting.h"
//#include "UI_Draw.h"

//#include "UI_hr_icon.h"
//#include "UI_comm_icon.h"
//#include "UI_Comm_Draw.h"
//#include "UI_main_icon.h"
//#include "UI_sport_icon.h"
//#include "UI_win_bpressure.h"


//static char c = 0;
//	
//void ui_win_bp_ready(void)
//{	
//	switch(c)
//	{
//	case 0:
//		DrawUI_Bitmap_Exx((LCD_W-104)/2-5, (LCD_H-89)/2,104,89,BMP_presure_1,0XF800);	
//		c = 1;
//		break;
//	case 1:			
//		DrawUI_Bitmap_Exx((LCD_W-104)/2-5, (LCD_H-89)/2,104,89,BMP_presure_2,0XF800);	
//		c = 0;
//		break;
//	}
//	
//	DrawUI_Bitmap_Exx(LCD_W-26,8+1,28,55,BMP_presure_3,0xFFFF);	
//}



//void ui_win_bp_done(void)
//{		
//	DrawUI_Bitmap_Exx( LCD_W-52,(LCD_H-45)/2,52,45,BMP_presure_4,0x1F<<11);
//	
//	int val = (int)hr.hp;
//	DrawUI_Bitmap_Ex( 0, 4,15,40,Font_15x38[val/100],0xFFFF);
//	DrawUI_Bitmap_Ex(16, 4,15,40,Font_15x38[(val/10)%10],0xFFFF);
//	DrawUI_Bitmap_Ex(32, 4,15,40,Font_15x38[val%10],0xFFFF);	
//	
//	DrawUI_Bitmap_Exx( 0,47,67,3,BMP_presure_line,0x1F<<11);
//	
//	val = (int)hr.lp;
//	
//	DrawUI_Bitmap_Ex(16-7,55,15,40,Font_15x38[(val/10)%10],0xFFFF);
//	DrawUI_Bitmap_Ex(32-7,55,15,40,Font_15x38[val%10],0xFFFF);	
//	
//	DrawUI_Bitmap_Exx(48,72,21,10,BMP_Hr_mmHg,0xFFFF);
//}

//extern const unsigned char BPM_Error[];
//	
//void ui_win_bp_error(void)
//{	
//	DrawUI_Bitmap_Exx((LCD_W-104)/2-5, (LCD_H-89)/2,104,89,BMP_presure_1,0XF800);	
//	DrawUI_Bitmap_Exx(LCD_W-26,8+1,28,55,BMP_presure_3,0xFFFF);		
//}

//void ui_win_bp_none(void)
//{	
//	DrawUI_Bitmap_Exx((LCD_W-104)/2-5, (LCD_H-89)/2,104,89,BMP_presure_1,0XF800);
//	DrawUI_Bitmap_Exx(LCD_W-26,8+1,28,55,BMP_presure_3,0XFFE0);	
//}

//void ui_win_bp_stop(void)
//{	
//	DrawUI_Bitmap_Exx( LCD_W-52,(LCD_H-45)/2,52,45,BMP_presure_4,0x1F<<11);
//	
//	int val = (int)hr.hp;
//	DrawUI_Bitmap_Ex( 0, 4,15,40,Font_15x38[val/100],0xFFFF);
//	DrawUI_Bitmap_Ex(16, 4,15,40,Font_15x38[(val/10)%10],0xFFFF);
//	DrawUI_Bitmap_Ex(32, 4,15,40,Font_15x38[val%10],0xFFFF);	
//	
//	DrawUI_Bitmap_Exx( 0,47,67,3,BMP_presure_line,0x1F<<11);
//	
//	val = (int)hr.lp;
//	
//	DrawUI_Bitmap_Ex(16-7,55,15,40,Font_15x38[(val/10)%10],0xFFFF);
//	DrawUI_Bitmap_Ex(32-7,55,15,40,Font_15x38[val%10],0xFFFF);	
//	
//	DrawUI_Bitmap_Exx(48,72,21,10,BMP_Hr_mmHg,0xFFFF);	
//}

//unsigned long win_bp_proc(unsigned short wid, unsigned short msg_type, 
//                            unsigned short msg_param, unsigned char *p)
//{	
//	if ( msg_type & WINDOW_CREATE )
//	{
//		win_ticks = 0; last_hr = 0; need_mTicks = 8000;
//		to_close = 0;
//        
//		hr.stat = HR_DECT_STAT_NONE;		
//		
//		if ( config.lcdEnable == 0 )
//		{
//			lcd_display(1);
//		}
//		
//		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
//		
//		return ( msg_type ^ WINDOW_CREATE );
//	}
//	
//	if ( msg_type & WINDOW_UPDATE )
//	{
//		win_ticks++; to_close++;

//        if ( (win_ticks > 250) || ((hr.stop == 1) && (to_close > 6)) )
//        {
//            lcd_display(0);
//            
//            return ( msg_type ^ WINDOW_UPDATE );
//        }
//		
//		memset(fb,0,sizeof(fb));
//	
//        switch ( hr.stat )
//        {         
//        case HR_DECT_STAT_NONE:
//            ui_win_bp_none();
//		    break;			
//        case HR_DECT_STAT_STOP:
//            ui_win_bp_stop();
//            break;
//		case HR_DECT_STAT_DECTING:
//        case HR_DECT_STAT_NORMAL:
//            ui_win_bp_ready();
//            break;
//        case HR_DECT_STAT_ERROR:
//            ui_win_bp_error();
//            break;
//        case HR_DECT_STAT_DONE:
//            ui_win_bp_done();
//            break;
//        default:
//            break;
//        }
//		
//		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
//		
//		if ( last_hr != hr.hr || hr.stat == HR_DECT_STAT_NORMAL
//				|| hr.stat == HR_DECT_STAT_DONE
//				|| hr.stat == HR_DECT_STAT_ERROR 
//				|| hr.stat == HR_DECT_STAT_NONE
//				|| hr.stat == HR_DECT_STAT_STOP )
//		{		
//			sync_frame();
//			
//			last_hr = hr.hr;
//		}
//				
//		return ( msg_type ^ WINDOW_UPDATE );
//	}
//	
//	if ( msg_type & WINDOW_TOUCH )
//	{	
//		if ( hr.stat != HR_DECT_STAT_ERROR
//			&& hr.stat != HR_DECT_STAT_NONE 
//			&& hr.stat != HR_DECT_STAT_STOP
//			&& hr.stop != 1)
//		{
//			return ( msg_type ^ WINDOW_TOUCH );
//		}		
//		
//		if ( config.lcdEnable == 0)
//		{
//			lcd_display(1);
//			win_ticks = 0; to_close = 0;
//			msg_type |= WINDOW_UPDATE;
//		}else{
//			window_push(window_get(win_current));
//			msg_type |= WINDOW_DISTORY;
//		}			
//		
//		return ( msg_type ^ WINDOW_TOUCH );
//	}
//	
//	if ( msg_type & WINDOW_PRESS )
//	{
//		win_ticks = 0; to_close = 0;
//		
//		if ( config.lcdEnable == 0)
//		{
//			lcd_display(1);

//			msg_type |= WINDOW_UPDATE;
//			
//			return ( msg_type ^ WINDOW_PRESS );
//		}
//		
//		if ( hr.stop == 1 )
//		{
//			need_mTicks = 8000;
//			hr.measure = 0x1<<1;
//			osal_set_event ( taskHrTaskId, TASK_HR_START_EVT );
//		} else
//		{
//			hr.stop = 1;
//			hr.stat = HR_DECT_STAT_NONE;
//			osal_set_event ( taskHrTaskId, TASK_HR_STOP_EVT );
//		}
//		
//		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
//		
//		return ( msg_type ^ WINDOW_PRESS );
//	}
//	
//	if ( msg_type & WINDOW_NOTIFY )
//	{   
//        window_push( win_current );
//        
//        win_current = NOTIFY_WIN_ID_GET();
//        window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0);
//		
//		return ( msg_type ^ WINDOW_NOTIFY );
//	}	
//	
//	if ( msg_type & WINDOW_DISTORY )
//	{
//		if ( hr.stop != 1 )
//		{
//			osal_set_event ( taskHrTaskId, TASK_HR_STOP_EVT );
//		}
//		
//		if ( hr.stat != HR_DECT_STAT_NONE )
//		{
//			hr.stat = HR_DECT_STAT_NONE;
//		}
//		
//		window_pop(&win_current);
//		
//		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
//	}

//    return 0;
//}

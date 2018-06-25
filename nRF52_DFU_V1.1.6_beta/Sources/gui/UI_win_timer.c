//#include "string.h"

//#include "OSAL.h"
//#include "OSAL_Timer.h"
//#include "Window.h"
//#include "UI_Draw.h"
//#include "LCD_ST7735.h"
//#include "UserSetting.h"
//#include "btprotocol.h"
//#include "Task_GUI.h"
//#include "Task_Touch.h"

#include "UI_win_timer.h"
//#include "UI_timer_icon.h"  
//#include "UI_main_icon.h"
//#include "UI_comm_icon.h"


unsigned char timer_flag = 0;
Timer_Stat timer_stat = TIMER_STAT_PAUSE;
unsigned long timer_cnt = 0;

//const unsigned char ms_table[] = {20,30,10,20,40,50,60,30,80,90,70};
//unsigned char table_indx = 0;

//#include "jpeg_decode.h"

//void show_timer(int x, int y, unsigned long timer_cnt)
//{
//	int m,s,ms;
//	unsigned long temp;	
//	
//	if ( timer_flag == 0 )
//	{
//        #if 1
//        #if 0
//        DrawUI_Bitmap_Exx((LCD_W-73)/2,0, 73, 57, BMP_timer, 0X07E0);
//		DrawUI_Bitmap_Exx((LCD_W-23)/2+2,(LCD_H-23-1)/2-4, 23, 23-1, BMP_tiemr_2, 0X3F<<5);
//        #else
//        
//        DrawUI_JPEG((LCD_W-74)/2,0,jpeg_timer_2);
//        #endif
//		m = 0; s = 0; ms = 0;
//        
//		DrawUI_Bitmap_Ex(  0+8, (LCD_H-41), 15, 40, Font_15x38[m/10],0XFFFF);	
//		DrawUI_Bitmap_Ex( 18+8, (LCD_H-41), 15, 40, Font_15x38[m%10],0XFFFF);	
//		
//		DrawUI_Bitmap_Ex( 36+7, (LCD_H-41), 4, 40, Font_15x38[10],0XFFFF);
//		
//		DrawUI_Bitmap_Ex( 40+8, (LCD_H-41), 15, 40, Font_15x38[s/10],0XFFFF);
//		DrawUI_Bitmap_Ex( 58+8, (LCD_H-41), 15, 40, Font_15x38[s%10],0XFFFF);
//		
//		DrawUI_Bitmap_Ex( 76+7, (LCD_H-41), 4, 40, Font_15x38[10],0XFFFF);
//		
//		DrawUI_Bitmap_Ex( 80+8, (LCD_H-41), 15, 40, Font_15x38[ms/10],0XFFFF);
//		DrawUI_Bitmap_Ex( 98+8, (LCD_H-41), 15, 40,  Font_15x38[ms%10],0XFFFF);
//		#else
//        DrawUI_JPEG((LCD_W-88)/2,(LCD_H-88)/2,jpeg_ui_timer);
//        #endif        
//	}else{
//		if ( timer_stat == TIMER_STAT_RUNNING )
//		{
//			timer_cnt += ms_table[table_indx];
//			table_indx++; table_indx %= SIZEOF(ms_table);
//			
//			DrawUI_Bitmap_Ex((LCD_W-24)/2, (LCD_H-28), 24,24,pause_icon,0x3F<<5);
//		}else if ( timer_stat == TIMER_STAT_STOP )
//        {
//            DrawUI_Bitmap_Ex((LCD_W-24)/2, (LCD_H-28), 24,24,exit_icon,0x3F<<5);
//        }else
//		{
//			DrawUI_Bitmap_Ex((LCD_W-24)/2, (LCD_H-28), 24,24,start_icon,0x1F<<11);
//		}
//		
//		temp = timer_cnt/1000;
//		
//		m = (temp/60)%60;
//		s = temp%60;
//		ms = (timer_cnt/10)%100;
//        
//		DrawUI_Bitmap_Ex(  0+8, 24, 15, 40, Font_15x38[m/10],0X1F<<11);
//		DrawUI_Bitmap_Ex( 18+8, 24, 15, 40, Font_15x38[m%10],0X1F<<11);
//		
//		DrawUI_Bitmap_Ex( 36+7, 24, 4, 40, Font_15x38[10],0XFFFF);
//		
//		DrawUI_Bitmap_Ex( 40+8, 24, 15, 40, Font_15x38[s/10],(0X1F<<11)|(0x3F<<5));
//		DrawUI_Bitmap_Ex( 58+8, 24, 15, 40, Font_15x38[s%10],(0X1F<<11)|(0x3F<<5));
//		
//		DrawUI_Bitmap_Ex( 76+7, 24, 4, 40, Font_15x38[10],0XFFFF);
//		
//		DrawUI_Bitmap_Ex( 80+8, 24, 15, 40, Font_15x38[ms/10],0X1F);
//		DrawUI_Bitmap_Ex( 98+8, 24, 15, 40, Font_15x38[ms%10],0X1F);			       
//	}

//}

//unsigned long win_timer_proc(unsigned short wid, unsigned short msg_type, 
//                            unsigned short msg_param, unsigned char *p)
//{	
//	if ( msg_type & WINDOW_CREATE )
//	{
//		win_ticks = 0; timer_stat = TIMER_STAT_PAUSE;
//		timer_flag = 0; timer_cnt = 0;

//		if ( config.lcdEnable == 0 )
//		{
//			lcd_display(1);
//		}
//		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
//		
//		return ( msg_type ^ WINDOW_CREATE );
//	}
//	
//	if ( msg_type & WINDOW_UPDATE )
//	{
//		win_ticks++;
//		
//		if ( (win_ticks > 30) && (timer_stat != TIMER_STAT_RUNNING) )
//		{
//			lcd_display(0);
//			
//			return ( msg_type ^ WINDOW_UPDATE );
//		}
//			
//		memset ( fb,0,sizeof(fb) );			
//		show_timer(0,0,timer_cnt);
//		sync_frame();
//		
//		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 100);
//		
//		return ( msg_type ^ WINDOW_UPDATE );
//	}
//	
//	if ( msg_type & WINDOW_TOUCH )
//	{	
//		win_ticks = 0;
//		
//		if ( config.lcdEnable == 0)
//		{
//			lcd_display(1);
//			msg_type |= WINDOW_UPDATE;
//		}else{
//			
//			if ( timer_flag == 0 )
//			{
//				window_push(window_get(win_current));
//				msg_type |= WINDOW_DISTORY;
//			}else{
//				
//				/* if ( touch_flag & TOUCH_FLAG_DOUBLE_TAP )
//				{
//					if ( timer_stat == TIMER_STAT_PAUSE )
//					{
//						timer_cnt = 0;
//					}
//					
//					touch_flag &= ~TOUCH_FLAG_DOUBLE_TAP;
//					
//					msg_type |= WINDOW_UPDATE;
//					
//					return ( msg_type ^ WINDOW_TOUCH );
//				} */
//				
//				if ( timer_stat == TIMER_STAT_RUNNING ){
//					timer_stat = TIMER_STAT_PAUSE;
//				}else if ( (timer_stat == TIMER_STAT_PAUSE) 
//					|| (timer_stat == TIMER_STAT_STOP) )
//				{
//					timer_stat = TIMER_STAT_RUNNING;
//				}
//			}
//		}	

//		msg_type |= WINDOW_UPDATE;
//		
//		return ( msg_type ^ WINDOW_TOUCH );
//	}
//	
//	if ( msg_type & WINDOW_PRESS )
//	{		
//		win_ticks = 0;		
//	
//		if ( config.lcdEnable == 0)
//		{
//			lcd_display(1);
//			msg_type |= WINDOW_UPDATE;
//		}else{
//			if ( timer_flag == 1 )
//			{
//				if ( timer_stat == TIMER_STAT_PAUSE )
//				{
//					timer_cnt  = 0;
//					timer_stat = TIMER_STAT_STOP;
//				}else if ( timer_stat == TIMER_STAT_STOP )
//				{
//					timer_cnt  = 0;
//					timer_flag = 0;
//				}
//			}else{
//				timer_flag = 1;
//				timer_stat = TIMER_STAT_STOP;
//			}
//		}			
//		
//		return ( msg_type ^ WINDOW_PRESS );
//	}
//	
//	if ( msg_type & WINDOW_NOTIFY )
//	{   
//        /* 当前窗体入栈 */
//        window_push( win_current );
//        
//        /* 通知界面作为当前界面 */
//        win_current = NOTIFY_WIN_ID_GET();
//        
//        /* 调用窗体回调函数以便创建窗体  */
//        window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0);
//		
//		return ( msg_type ^ WINDOW_NOTIFY );
//	}
//	
//	if ( msg_type & WINDOW_DISTORY )
//	{
//		window_pop(&win_current);
//		window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
//		
//		return ( msg_type ^ WINDOW_DISTORY );
//	}

//    return 0;
//}

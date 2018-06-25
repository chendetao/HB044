#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "Task_Store.h"
#include "Task_Touch.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"
#include "ClockTick.h"
#include "UI_hr_icon.h"
#include "ClockTick.h"

#include "UI_comm_icon.h"
#include "UI_Comm_Draw.h"
#include "QR_Utils.h"
#include "UI_main_icon.h"
#include "Ui_win_running.h"
#include "Task_Flash.h"
#include "UI_sport_icon.h"
#include "UI_win_sport.h"
#include "UI_main_icon.h"

#define COLOR_B      0X0000
#define COLOR_F      0xFFFF

#define SPORT_WIN_ID_NR      5

unsigned char sport_enable;
//unsigned char sport_done;
Sport_Type sport_type;

unsigned char show_yes_no_main;
unsigned char choose_yes_or_no;
#include "jpeg_decode.h"

void DrawSportIconMain(void)
{
	DrawUI_JPEG(4,8,jpeg_sport_main);
	DrawUI_Bitmap_Exx(70,36,56,24,BMP_sport_main, 0XFFFF);	
}

void show_bycle_val( int calurie, int utc_length )
{
	
	int utc = utc_length;
	int m = (utc/60)%60;
	int s = utc%60;	
	
	
	DrawUI_Bitmap_Exx(6,54,10,24,Font_10x24[m/10],0x0000);	
	DrawUI_Bitmap_Exx(17,54,10,24,Font_10x24[m%10],0x0000);
	
	DrawUI_Bitmap_Exx(27,54,10,24,Font_10x24[10],0x0000);
	
	DrawUI_Bitmap_Exx(37,54,10,24,Font_10x24[s/10],0x0000);	
	DrawUI_Bitmap_Exx(48,54,10,24,Font_10x24[s%10],0x0000);	
	
	DrawUI_Bitmap_Exx(19,78,26,16,BMP_sport_time,0x0000);
	
	
	int vh;
	// draw value
	vh = calurie;
	if ( vh > 9999 )
	{
		vh = 9999;
	}
	
	if ( vh < 0 )
	{
		vh = 0;
	}

	DrawUI_Bitmap_Exx(74, 54,10,24,Font_10x24[vh/1000],0xFFFF);
	vh %= 1000;
	DrawUI_Bitmap_Exx(85, 54,10,24,Font_10x24[vh/100],0xFFFF);
	vh %= 100;
	DrawUI_Bitmap_Exx(96, 54,10,24,Font_10x24[vh/10],0xFFFF);
	vh %= 10;
	DrawUI_Bitmap_Exx(107,54,10,24,Font_10x24[vh],0xFFFF);	
	
	DrawUI_Bitmap_Exx(83,78,26,16,BMP_sport_kcal,0xFFFF);
	
	
	if ( show_yes_no_main == 1 )
		{ 
			draw_fill(0,0,128,96, 0X0000);
			
			DrawUI_Bitmap_Exx(24, 16, 16, 32, sport_exit_e, 0XFFFF);
			DrawUI_Bitmap_Exx(40, 16, 16, 32, sport_exit_x, 0XFFFF);
			DrawUI_Bitmap_Exx(56, 16, 16, 32, sport_exit_i, 0XFFFF);
			DrawUI_Bitmap_Exx(72, 16, 16, 32, sport_exit_t, 0XFFFF);
			DrawUI_Bitmap_Exx(88, 16, 16, 32, sport_exit_, 0XFFFF);

			if ( choose_yes_or_no == 1 )
			{
				draw_fill(24,64,24,16, 0XF800);			
			}
			else
			{
				draw_fill(88,64,16,16, 0XF800);			
			}
			
			DrawUI_Bitmap_Exx(24, 64, 8, 16, sport_yes_y, 0XFFFF);
			DrawUI_Bitmap_Exx(32, 64, 8, 16, sport_yes_e, 0XFFFF);
			DrawUI_Bitmap_Exx(40, 64, 8, 16, sport_yes_s, 0XFFFF);
			DrawUI_Bitmap_Exx(88, 64, 8, 16, sport_no_n, 0XFFFF);
			DrawUI_Bitmap_Exx(96, 64, 8, 16, sport_no_o, 0XFFFF);
		}
	
}


void DrawSportIconBycle(void)
{		
	if ( sport_enable == 0 )
	{
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_ride2, BLUE);	
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_ride1, 0XFFFF);
	}else{			
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_background, BLUE);	
		DrawUI_Bitmap_Exx(32,0,64,48,BMP_sport_ride22, BLUE);	
		DrawUI_Bitmap_Exx(32,0,64,48,BMP_sport_ride11, 0XFFFF);	
		
		show_bycle_val(pedometer.calorie - config.train_calorie, 
						getUTC()-config.train_utc);
	}
}

void DrawSportIconRunning(void)
{
	if ( sport_enable == 0 )
	{
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_run2, GREEN);			
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_run1, 0XFFFF);	
	}else
	{			
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_background, GREEN);	
		DrawUI_Bitmap_Exx(32,0,64,48,BMP_sport_run22, GREEN);	
		DrawUI_Bitmap_Exx(32,0,64,48,BMP_sport_run11, 0XFFFF);
		
		show_bycle_val(pedometer.calorie - config.train_calorie, 
						getUTC()-config.train_utc);
	}		
}

void DrawSportIconSwimming(void)
{
	if ( sport_enable == 0 )
	{
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_swim2, RED);	
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_swim1, 0XFFFF);	
	}else{
		DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_background, RED);	
		DrawUI_Bitmap_Exx(32,0,64,48,BMP_sport_swim22, RED);	
		DrawUI_Bitmap_Exx(32,0,64,48,BMP_sport_swim11, 0XFFFF);
		
		show_bycle_val(pedometer.calorie - config.train_calorie, 
						getUTC()-config.train_utc);
	}		
}

void DrawSportIconBack(void)
{
	DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_back2, RED);	
	DrawUI_Bitmap_Exx(0,0,128,96,BMP_sport_back1, 0XFFFF);		
}

void ui_win_sport(void)
{       
    switch ( sport_type )
    {
    case SPORT_TYPE_NONE:             	/* 运动界面(主界面) */
    	DrawSportIconMain();
        break;
    case SPORT_TYPE_BYCLE:				/* 自行车 */
        DrawSportIconBycle();
        break;
    case SPORT_TYPE_RUNNING:			/* 跑步 */
        DrawSportIconRunning();
        break;
	case SPORT_TYPE_SWIMMING:           /* 游泳 */
		DrawSportIconSwimming();
		break;
    case SPORT_TYPE_BACK:  				/* 返回 */
        DrawSportIconBack();
        break;
    default:
        break;
    }
}

unsigned char select_enable;
unsigned char leave_here = 0;

unsigned long win_sport_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{	
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0; select_enable = 0; 
		
		if ( leave_here == 0 )
		{
			sport_type = SPORT_TYPE_NONE;
		}else{
			leave_here = 0;
		}
		
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

		ui_win_sport();

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
		}else{
			
            if ( select_enable == 0 )
            {
                window_push(window_get(win_current));
                msg_type |= WINDOW_DISTORY;
            }else if ( sport_enable == 0 )
            {
                sport_type++; 
                sport_type %= SPORT_WIN_ID_NR;
                if ( sport_type == SPORT_TYPE_NONE )
                {
                  sport_type = SPORT_TYPE_BYCLE;
                }
				
				config.train_pedometer = 0;
				config.train_calorie   = 0;
				config.train_distance  = 0;
            }
			if ( show_yes_no_main == 1)
			{		
				choose_yes_or_no++;
				choose_yes_or_no %= 2;
			}
		}
		
		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{	
        win_ticks = 0;
        
		if ( config.lcdEnable == 0 )
    	{
            lcd_display(1);
            osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );

            return ( msg_type ^ WINDOW_PRESS );
    	}
        
    	if ( select_enable == 0 )
    	{
            select_enable = 1;
    	}else
        {
            if ( sport_type == SPORT_TYPE_BACK )
            {
              select_enable = 0;
            }
        }

    	if ( sport_enable == 1 && sport_type != SPORT_TYPE_BACK )
    	{                   
            switch ( sport_type )
            {
            case SPORT_TYPE_BYCLE:
                if(show_yes_no_main == 0)
				{
					show_yes_no_main = 1;
					choose_yes_or_no = 0;
					
					msg_type |= WINDOW_UPDATE;
				}
				else 
				{
					if(choose_yes_or_no == 1)
					{
						sport_enable = 0;
						show_yes_no_main = 0;
						
						msg_type |= WINDOW_UPDATE;
						osal_set_event(taskStoreTaskId,TASK_STORE_SAVE_BYCLE_EVT);
					}
					else
					{
						show_yes_no_main = 0;
						msg_type |= WINDOW_UPDATE;
					}
				}
                break;
            case SPORT_TYPE_RUNNING:
				if(show_yes_no_main == 0)
				{
					show_yes_no_main = 1;
					choose_yes_or_no = 0;
					
					msg_type |= WINDOW_UPDATE;
				}
				else 
				{
					if(choose_yes_or_no == 1)
					{
						sport_enable = 0;
						show_yes_no_main = 0;
						
						msg_type |= WINDOW_UPDATE;
						osal_set_event(taskStoreTaskId,TASK_STORE_SAVE_RUNNING_EVT);
					}
					else
					{
						show_yes_no_main = 0;
						msg_type |= WINDOW_UPDATE;
					}
				}				break;
			case SPORT_TYPE_SWIMMING:
				if(show_yes_no_main == 0)
				{
					show_yes_no_main = 1;
					choose_yes_or_no = 0;
					
					msg_type |= WINDOW_UPDATE;
				}
				else 
				{
					if(choose_yes_or_no == 1)
					{
						sport_enable = 0;
						show_yes_no_main = 0;
						
						msg_type |= WINDOW_UPDATE;
						osal_set_event(taskStoreTaskId,TASK_STORE_SAVE_SWIMMING_EVT); 
					}
					else
					{
						show_yes_no_main = 0;
						msg_type |= WINDOW_UPDATE;
					}
				}
				break;
			default:
				break;
            }
		            
            return ( msg_type ^ WINDOW_PRESS );
    	}
		
        switch ( sport_type )
        {
        case SPORT_TYPE_NONE:             		/* 运动界面(主界面) */	
            sport_type = SPORT_TYPE_BYCLE;
            break;
        case SPORT_TYPE_BYCLE:					/* 自行车(开始) */
        case SPORT_TYPE_RUNNING:			    /* 步行(开始) */
		case SPORT_TYPE_SWIMMING:				/* 游泳(开始)*/
            sport_enable = 1;
            config.train_utc = getUTC();
            config.train_pedometer = pedometer.counter;
            config.train_distance  = pedometer.distance;
            config.train_calorie   = pedometer.calorie;	
			break;	
        case SPORT_TYPE_BACK:					/* 返回 */
            sport_type = SPORT_TYPE_NONE;
            sport_enable = 0;
            select_enable = 0;
            break;
        default:
            break;
        } 
		
     
        // For update the lcd immediately
        osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_PRESS );
	}
	
	if ( msg_type & WINDOW_NOTIFY )
	{   
		leave_here = 1;
		
        window_push( win_current );       
        win_current = NOTIFY_WIN_ID_GET(); 
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

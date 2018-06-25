#include "OSAL.h"
#include "OSAL_Timer.h"
#include "OSAL_Task.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "Window.h"

#include "LCD_ST7735.h"
#include "Button.h"
#include "UI_win_notify.h"
#include "SPI.h"
#include "UserSetting.h"
#include "Alarm.h"
#include "ClockTick.h"
#include "MsgQueue.h"
#include "Task_Motor.h"
#include "UI_win_sport.h"
#include "FontChip.h"

unsigned char taskGUITaskId;

unsigned long taskGUI( unsigned char task_id, unsigned long events )
{
	if ( events & TASK_GUI_UPDATE_EVT )
	{
		window[win_current].msg_type = WINDOW_UPDATE;
		
		osal_set_event( task_id, TASK_GUI_UI_EVT );
		
		return ( events ^ TASK_GUI_UPDATE_EVT );
	}
	
	if ( events & TASK_GUI_TOUCH_EVT )
	{
		window[win_current].msg_type |= WINDOW_TOUCH;
		
		osal_set_event( task_id, TASK_GUI_UI_EVT );

		return ( events ^ TASK_GUI_TOUCH_EVT );
	}
	
	if ( events & TASK_GUI_PRESS_EVT )
	{
		window[win_current].msg_type |= WINDOW_PRESS;
		
		osal_set_event( task_id, TASK_GUI_UI_EVT );
		
		return ( events ^ TASK_GUI_PRESS_EVT );		
	}
	
	if ( events & TASK_GUI_NOTIFY_EVT )
	{
		window[win_current].msg_type |= WINDOW_NOTIFY;
		
		osal_set_event( task_id, TASK_GUI_UI_EVT );
		
		return ( events ^ TASK_GUI_NOTIFY_EVT );
	}
	
    if ( events & TASK_GUI_UI_EVT )
    {
        unsigned long msg_type = window[win_current].msg_type;
        
        while( msg_type )
        {
            unsigned char *arg = window[win_current].arg;
            unsigned long param = window[win_current].param;
			
            msg_type = window[win_current].wproc( win_current, msg_type, param, arg ); 
			window[win_current].msg_type = msg_type;
        }
        
        return ( events ^ TASK_GUI_UI_EVT );
    }	
	
	if ( events & TASK_GUI_LCD_CONFIG_DELAY_EVT )
	{
		LCD_Config_Delay();
		
		return ( events ^ TASK_GUI_LCD_CONFIG_DELAY_EVT );
	}	
	
	/** 
	 * Check The Alarm Everay Minute.
	 */
    if ( events & TASK_UI_MINUTE_TIMEOUT_EVT )
    {
        if (( alarm.g_Ahour_next == TimerHH()) &&
            ( alarm.g_Amin_next == TimerMI())
               && (alarm.g_AlarmIsOn_next == 1) )
        {
            if ( config.shutdown == 0 )
			{
                /* 添加闹钟提醒 */
				NOTICE_ADD (NOTIFY_ID_ALARM);
            }
        }
        
        calc_next_Alarm(0);
		
		/**
		 *  久坐提醒事件重新计时.
		 */
		if ( ((monitor.ss & 0x1) && 
			( (TimerHH() + TimerMI()) == monitor.start ) )
			|| (((monitor.ss>>1) & 0x1) && 
			((TimerHH() + TimerMI()) == monitor.sedentary_end)) )
		{
			osal_set_event( taskStepTaskId, TASK_STEP_SED_INIT_EVT);
		}
        
        return ( events ^ TASK_UI_MINUTE_TIMEOUT_EVT );
    }	
	
	if ( events & TASK_GUI_TAKE_PHOTO_EVT )
	{
		if ( win_current != WIN_ID_TAKE_PHOTO )
		{
			if ( (win_current == WIN_ID_SPORT) && (sport_enable == 1) )
			{
				leave_here = 1;
			}
			
			window_push(win_current);
		
			win_current = WIN_ID_TAKE_PHOTO; // Id for task photo
		}
		
		window[win_current].msg_type = WINDOW_CREATE;
		
		osal_set_event( task_id, TASK_GUI_UI_EVT );
		
		return ( events ^ TASK_GUI_TAKE_PHOTO_EVT );
	}
	
	if ( events & TASK_GUI_EXIT_PHOTO_EVT )
	{
		/**
  		 * If current window Id is photo task,
		 * we distory it
		 */
		if ( win_current == WIN_ID_TAKE_PHOTO ){
			window[win_current].msg_type = WINDOW_DISTORY;
		}
		
		osal_set_event( task_id, TASK_GUI_UI_EVT );
		
		return ( events ^ TASK_GUI_EXIT_PHOTO_EVT );
	}
	
	if ( events & TASK_GUI_TEST_EVT )
	{	
		return ( events ^ TASK_GUI_TEST_EVT );
	}
	
	if ( events & TASK_GUI_BLE_DISCONNECT_EVT )
	{
		if ( ble.isConnected == 0 && config.shutdown == 0){
			NOTICE_ADD(NOTIFY_ID_BLE);			
		}
		return ( events ^ TASK_GUI_BLE_DISCONNECT_EVT );
	}
	
	if ( events & TASK_GUI_LCD_LEVEL_UPDATE_EVT )
	{
		if ( config.lcdEnable == 0 )
		{
			events |= TASK_GUI_TOUCH_EVT;
		}else
		{
			LCD_Level_Set(config.lcd_level);
			win_ticks = 0;
		}
		
		return ( events ^ TASK_GUI_LCD_LEVEL_UPDATE_EVT );
	}
	
	if ( events & TASK_GUI_HR_START_EVT )
	{
		/** 切换到心率测试界面 */
		
		if ( win_current == WIN_ID_BP && hr.stop == 0 && config.lcdEnable == 1 )
		{
			hr.stop = 1;
		}
		
		if ( win_current != WIN_ID_HR )
		{
			win_current = WIN_ID_HR;
			window[win_current].msg_type = WINDOW_CREATE;
			osal_set_event( task_id, TASK_GUI_UI_EVT );			
			osal_start_timerEx( task_id, TASK_GUI_PRESS_EVT, 100 );
		} else {
			if ( config.lcdEnable == 0 )
			{
				window[win_current].msg_type = WINDOW_TOUCH;
				osal_set_event( task_id, TASK_GUI_UI_EVT );			
				osal_start_timerEx( task_id, TASK_GUI_PRESS_EVT, 100 );				
			}else{
				if ( hr.stop == 1 ){
				 osal_set_event( task_id,TASK_GUI_PRESS_EVT ); 
				}
			}			
		}
				
		return ( events ^ TASK_GUI_HR_START_EVT );
	}
	
	if ( events & TASK_GUI_HR_STOP_EVT )
	{
		/** 如果当前界面是心率界面,且正在测试中,则模拟一个长按事件,
		 * 触发停止测量 */
		if ( win_current != WIN_ID_HR || hr.stop == 1 )
		{
			return ( events ^ TASK_GUI_HR_STOP_EVT );
		}
			
		// Mybe a bug
		if ( config.lcdEnable == 0 )
		{
			window[win_current].msg_type = WINDOW_TOUCH;
			osal_set_event( task_id, TASK_GUI_UI_EVT );			
			osal_start_timerEx( task_id, TASK_GUI_PRESS_EVT, 100 );
		}else{
			osal_set_event( task_id,TASK_GUI_PRESS_EVT ); 
		}
		
		return ( events ^ TASK_GUI_HR_STOP_EVT );
	}	
	
	if ( events & TASK_GUI_STOP_SPORT_EVT )
	{
		// 00:00 在数据清零前,强制退出运动模式
		if ( (win_current != WIN_ID_SPORT ) || (sport_enable != 1 ) )
		{
			return ( events ^ TASK_GUI_STOP_SPORT_EVT );
		}
		
		// Mybe a bug
		if ( config.lcdEnable == 0 )
		{
			window[win_current].msg_type = WINDOW_TOUCH;
			osal_set_event( task_id, TASK_GUI_UI_EVT );			
			osal_start_timerEx( task_id, TASK_GUI_PRESS_EVT, 100 );
		}else{
			osal_set_event( task_id,TASK_GUI_PRESS_EVT ); 
		}		
		
		return ( events ^ TASK_GUI_STOP_SPORT_EVT );
	}
	
	if ( events & TASK_GUI_INIT_EVT )
	{
		osal_set_event( task_id, TASK_GUI_UI_EVT );
		osal_start_timerEx ( task_id, TASK_GUI_FONT_TSET_EVT, 700);
		
		button_init();
		LCD_Init();
				
		Font_init();
		
		EntryDeepSleepMode();
		
		return ( events ^ TASK_GUI_INIT_EVT );
	}
	
	if ( events & TASK_GUI_FONT_TSET_EVT )
	{
		ExitDeepSleepMode();
		if ( font_is_ok() == true )
		{
			EntryDeepSleepMode();
			if ( config.motor_test_enable == 1 )
			{
				osal_set_event( taskMotorTaskId, TASK_MOTOR_BMA_DONE_EVT );
			}
		}
		
		EntryDeepSleepMode();
		
		return ( events ^ TASK_GUI_FONT_TSET_EVT );
	}
	
	if ( events & TASK_GUI_SYS_POWEROFF_EVT )
	{
		win_current = WIN_ID_POWER;
		ui_window_manager( WINDOW_CREATE, 0, 0);
		ui_window_manager( WINDOW_PRESS, 0, 0);
		
		return ( events ^ TASK_GUI_SYS_POWEROFF_EVT );
	}
	
	return ( 0 );
}

void taskGUIInit( unsigned char task_id )
{
	taskGUITaskId = task_id;
	
	window_init();	
	calc_next_Alarm(1);
	
    osal_set_event(task_id, TASK_GUI_INIT_EVT );
	
	osal_start_timerEx ( task_id, TASK_GUI_TEST_EVT, 2000 );
}


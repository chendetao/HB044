#include "OSAL.h"
#include "OSAL_Task.h"
#include "OSAL_Timer.h"
#include "Task_Frame.h"
#include "LCD_ST7735.h"
#include "Task_Motor.h"

void sync_frame(void)
{
	osal_set_event ( taskFrameTaskId, FRAME_TASK_SYNC_FRAME_EVT_0 );
}

unsigned char taskFrameTaskId;

void taskFrameInit(unsigned char task_id)
{
    taskFrameTaskId = task_id;
}

/**
 * 1，由于同步整个FrameBuffer的内容将花费过长的时间，可能会导致蓝牙
 *    连接事件得不到处理，所以此处将FrameBuffer分为4次同步，使得OSAL有
 *    机会去执行更为紧急的任务.
 * 2，同时，需要在OLED屏幕上绘图的任务可以刷新指定的区域，减少没有必要
 *    的绘图时间，提升效率。
 */

unsigned long taskFrame( unsigned char task_id, unsigned long events )
{
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_0 )
    {	
        #if 1
		do_sync_frame( 0, 8);		
        
        events |= FRAME_TASK_SYNC_FRAME_EVT_1;
		#else
        do_sync_frame( 0, 96);
        #endif
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_0 );
    }    
    
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_1 )
    {
        do_sync_frame(8,16);
        
        events |= FRAME_TASK_SYNC_FRAME_EVT_2;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_1 );
    }
    
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_2 )
    {
        do_sync_frame(16,24);
        
        events |= FRAME_TASK_SYNC_FRAME_EVT_3;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_2 );
    }

    if ( events & FRAME_TASK_SYNC_FRAME_EVT_3 )
    {
        do_sync_frame(24,32);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_4;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_3 );
    } 
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_4 )
    {
        do_sync_frame(32,40);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_5;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_4 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_5 )
    {
        do_sync_frame(40,48);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_6;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_5 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_6 )
    {
        do_sync_frame(48,56);		
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_7;
		
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_6 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_7 )
    {
        do_sync_frame(56,64);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_8;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_7 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_8 )
    {
        do_sync_frame(64,72);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_9;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_8 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_9 )
    {
        do_sync_frame(72,80);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_10;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_9 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_10 )
    {
        do_sync_frame(80,88);
		
		events |= FRAME_TASK_SYNC_FRAME_EVT_11;
        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_10 );
    }	
	
    if ( events & FRAME_TASK_SYNC_FRAME_EVT_11 )
    {
        do_sync_frame(88,96);
		        
        return ( events ^ FRAME_TASK_SYNC_FRAME_EVT_11 );
    }	
      
    return 0;
}

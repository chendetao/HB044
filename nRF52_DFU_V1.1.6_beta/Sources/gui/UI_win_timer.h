#ifndef __UI_TIMER_H__
#define __UI_TIMER_H__

typedef enum
{
	TIMER_STAT_RUNNING = 1,
	TIMER_STAT_PAUSE   = 2,
	TIMER_STAT_STOP    = 3,
}Timer_Stat;

extern unsigned char timer_flag;
extern Timer_Stat timer_stat;
extern unsigned long timer_cnt;

extern 
unsigned long win_timer_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);

#endif

#ifndef __UI_WIN_SPORT_H__
#define __UI_WIN_SPORT_H__

typedef enum
{
	SPORT_TYPE_NONE     = 0,
	SPORT_TYPE_BYCLE,
	SPORT_TYPE_RUNNING,
	SPORT_TYPE_SWIMMING,
	SPORT_TYPE_BACK,
}Sport_Type;

extern Sport_Type sport_type;
extern unsigned char select_enable;
extern unsigned char sport_enable;
extern unsigned char leave_here;
extern unsigned char show_yes_no_main;
extern unsigned char choose_yes_or_no;

extern 
unsigned long win_sport_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);

#endif

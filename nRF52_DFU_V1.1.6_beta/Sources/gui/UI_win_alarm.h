
#ifndef __UI_WIN_ALARM_H__
#define __UI_WIN_ALARM_H__

extern 
unsigned long win_alarm_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);

void show_alarm(int x, int y, int hour, int minute );

#endif

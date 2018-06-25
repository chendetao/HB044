#ifndef __UI_WIN_HR_H__
#define __UI_WIN_HR_H__

extern unsigned long win_hr_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);

extern void show_error(int x, int y);
extern void show_ready(void);

#endif

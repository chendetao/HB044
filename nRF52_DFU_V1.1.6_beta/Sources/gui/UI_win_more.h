#ifndef __UI_WIN_MORE_H__
#define __UI_WIN_MORE_H__

typedef enum
{
	MORE_TYPE_SLEEP,       
	MORE_TYPE_INFO,
	MORE_TYPE_BACK,    
}More_Type;

extern More_Type more_type;

extern unsigned long win_more_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);

#endif
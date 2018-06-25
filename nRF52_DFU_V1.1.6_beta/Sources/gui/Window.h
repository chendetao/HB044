#ifndef __WINDOW_H__
#define __WINDOW_H__

#define NOTIFY_WIN_ID_GET() (winCnt-1)

#define WINDOW_CREATE           0x00000001
#define WINDOW_UPDATE           0x00000002
#define WINDOW_TOUCH            0x00000004
#define WINDOW_NOTIFY           0x00000008
#define WINDOW_PRESS            0x00000010
#define WINDOW_DISTORY          0x00000020
#define WINDOW_SWITCH           0x00000040

#define MAKE_MESSAGE(x) (x)
#define GET_MESSAGE(x) (x)

#define WIN_MSG_KEY_TOUCH      0
#define WIN_MSG_KEY_LONG_TOUCH 1

#define WIN_ID_SPORT           2
#define WIN_ID_HR              3
#define WIN_ID_BP              3
#define WIN_ID_TIMER           6
#define WIN_ID_TAKE_PHOTO      7
#define WIN_ID_POWER          10
#define WIN_ID_NOTIFY         11


typedef unsigned long (*window_proc)(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);
struct window_struct
{
    unsigned short wid;
    unsigned short msg_type;
    unsigned short param;
    unsigned char *arg;
	unsigned short flag;
    window_proc wproc;
};

struct window_map
{
	unsigned char app_id;
	unsigned char dev_id;
};

extern struct window_struct window[];
extern unsigned char win_current;
extern unsigned short win_ticks;
extern const unsigned char winCnt;

extern void window_init(void);

extern void window_push( unsigned char wid );
extern int window_pop( unsigned char *wid );
extern void window_tack_reset(void);

extern unsigned long window_get( unsigned long win_current );
extern int window_show_set( unsigned long win_id, int show );
extern int ui_window_manager(unsigned long msg_type, 
                            unsigned long msg_param, unsigned char *p);
extern int ui_window_set_param( unsigned long win_id, unsigned long msg_param );

extern int window_set(unsigned long enable, const unsigned char *pVal );

#endif


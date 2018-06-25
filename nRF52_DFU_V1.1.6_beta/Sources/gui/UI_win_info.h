#ifndef __UI_INFO_ICON_H__
#define __UI_INFO_ICON_H__

#include "OSAL.h"
#include "OSAL_Timer.h"

#include "Task_GUI.h"
#include "Task_Step.h"
#include "LCD_ST7735.h"

#include "string.h"
#include "Window.h"
#include "UserSetting.h"
#include "UI_Draw.h"

extern unsigned long win_info_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p);

#endif

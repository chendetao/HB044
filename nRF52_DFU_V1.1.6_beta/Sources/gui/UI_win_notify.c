
#include "string.h"
#include "Window.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_GUI.h"
#include "LCD_ST7735.h"
#include "QR_Utils.h"
#include "Ancs.h"
#include "UserSetting.h"
#include "UI_Draw.h"
#include "btprotocol.h"
#include "UI_pedometer_icon.h"
#include "UI_main_icon.h"

#include "UI_win_notify.h"
#include "Window.h"
#include "UI_notify_icon.h"
#include "MsgQueue.h"
#include "jpeg_decode.h"

#define COLOR_B      0x0000
#define COLOR_F      0xFFFF

void NOTICE_ADD(unsigned char notify_id)
{
    mq.notify_id = notify_id;
    osal_set_event(taskGUITaskId, TASK_GUI_NOTIFY_EVT);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "MsgQueue.h"
#include "Alarm.h"
#include "HFMA2Ylib.h"

extern void EntryDeepSleepMode(void);
extern void ExitDeepSleepMode(void);
int x = 0;
unsigned char DZ[32] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x18,};

 /**
 * uint8 LengthCount( uint8 *pVal, uint8 length);
 * @bref 计算字符(Ascii、GBK)所占宽度.
 * @pVal Buffer pointer the store the chars.
 * @lenght length of buffer
 * return 所有字符宽度的像素值.
 */
unsigned int LengthCount( unsigned char *pVal, int length)
{
    unsigned int x = 0;
    
    for ( int j = 0; j < length; j += 2 )
    {
        if ( pVal[j] == 0x0 )
        {
            x += 8;
        }else{
            x += 16;
        }
    }
             
    return x;
}

void DoRect16x16( int cx, int cy, const unsigned char pic[32])
{   
    unsigned char temp;
    
    for ( int k = 0; k < 16 ; k++)
    {        
		temp = pic[k+0];	
		for ( int i = 0; i < 8; i++ )
		{
			if ( (temp >> i) & 0x1 )
			setpixel(cx, cy+i+0, 0xFFFF);
		}
		
		temp = pic[k+16];
		for ( int i = 0; i < 8; i++ )
		{
			if ( (temp >> i) & 0x1 )
			setpixel(cx, cy+i+8, 0xFFFF);
		}		
      
        cx++;
    }
}

void DoRect8x16( int cx, int cy, const unsigned char pic[32])
{   
    unsigned char temp;
    
    for( int k = 0; k < 8 ; k++)
    {        
		temp = pic[k+0];	
		for ( int i = 0; i < 8; i++ )
		{
			if ( (temp >> i) & 0x1 )
			setpixel(cx, cy+i+0, 0xFFFF);
		}
		
		temp = pic[k+8];
		for ( int i = 0; i < 8; i++ )
		{
			if ( (temp >> i) & 0x1 )
			setpixel(cx, cy+i+8, 0xFFFF);
		}		
		
        cx++;
    }
}

/**
 * static void DrawTitle(void);
 *
 * Note : Show the notification Message Title( sender )
 *
 */
static void DrawTitle(void)
{
    /*计算出中心对称显示时的起始坐标 */
    int x,y,len;
	unsigned short gbk;
	unsigned short unicode;
	
    len = LengthCount(mq.title, mq.title_len);
    if ( len <= LCD_W )
    {
      x = (LCD_W - len)/2;
      y = (LCD_H-16)/2;
    }else
    {
      x = 0; y = (LCD_H-16)/2;
    }
    
    for ( int j = 0; j < mq.title_len; j += 2 )
    {
		if ( ((mq.title[j] == 0x20) && (mq.title[j+1] == 0x2D)) 
			|| ( (mq.title[j] == 0x20) && (mq.title[j+1] == 0x2C)) 
			|| ( (mq.title[j] == 0x20) && (mq.title[j+1] == 0x0E))
			|| ( (mq.title[j] == 0x26) && (mq.title[j+1] == 0x0E)) )
		{
			continue;
		}		
		
        if ( mq.title[j] == 0x0 )
        {
			if ( mq.title[j+1] < 0X20 || mq.title[j+1] > 0x7E ){
				continue;
			}
			{
				ASCII_GetData(mq.title[j+1],ASCII_8X16,DZ);
				DoRect8x16(x, y, DZ);
				x += 8; len -= 8;
			}
        }else{
            unicode = (unsigned short)(mq.title[j]<<8)
				+ (unsigned short)mq.title[j+1];
			
			// add
			if (  (unicode>=0x2E80 && unicode<=0x2FDF) ||
				( (unicode>=0x3400) && (unicode <= 0x4DBE)) ||
			    ( (unicode>=0x4E00) && (unicode<=0x9FFF) ) )
			{
				// 中文区
				gbk = U2G(unicode );
				hzbmp16( SEL_GB, gbk ,0, 16, DZ ); 
				
				DoRect16x16(x,y,DZ);
				x += 16;len -= 16;
				
			}else		
			if ( (unicode >= 0x1100 && unicode <= 0x11FF) ||
                (unicode>=0x3130 && unicode <= 0x318F) ||
                  (unicode >= 0xAC00 && unicode <= 0xD7AF) )
            {
				// 韩文区
				unsigned short ksc;
				
				ksc = U2K(unicode);
			    hzbmp16( SEL_KSC, ksc ,0, 16, DZ );
				
				DoRect16x16(x,y,DZ);
				x += 16;len -= 16;
				
            }else if ( (unicode>=0x3040 && unicode<=0x30FF) ||
				( (unicode>=0x31F0) && (unicode <= 0x31FF)) ){
				// 日文区
				unsigned short jis;
					
				jis = U2J(unicode);
			    hzbmp16( SEL_JIS, jis ,0, 16, DZ );
				
				DoRect16x16(x,y,DZ);
				x += 16;len -= 16;		
				mq.pageLength += 2;
			}else{
				// 其他外国文字
				if ( (unicode>=0x0080 && unicode<=0x02AF) ||
					( (unicode>=0x1E00) && (unicode<=0x1EFF)) )
				{
					// 拉丁文
					// 包含但不限于：德语、法语、西班牙语、葡萄牙语
					//               意大利语
					LATIN_GetData(unicode,DZ);  // 不等宽
					DoRect8x16(x,y,DZ);
					x += 8;len -= 8;
					
				}else if ( (unicode >= 0x0400) && (unicode <= 0x052F) )
				{
					// 西里尔文
					// 包含但不限于：俄语
					CYRILLIC_GetData(unicode,DZ); // // 不等宽
					DoRect8x16(x,y,DZ);
					x += 8;len -= 8;
					
				}else
				{
					// 按照汉字处理
					gbk = U2G(unicode );
					hzbmp16( SEL_GB, gbk ,0, 16, DZ ); 
					
					DoRect16x16(x,y,DZ);
					x += 16;len -= 16;
				}
            }
			// end
        }
		
//		if ( (j+2) >= mq.title_len ) { break; }
        
        if ( mq.title[j+2] == 0x0 ){
            if ( (x+8) > LCD_W ) 
			{ 
				y += 16; 
				if ( len <= LCD_W )  
				{
					x = (LCD_W-len)/2;
				}
				else
				{
					x = 0;
				}
			}
        }else{
            if ( (x+16) > LCD_W )
			{ 
				y += 16;
				if ( len <= LCD_W )  
				{
					x = (LCD_W-len)/2;
				}
				else
				{
					x = 0;
				}
			}
        }        
    } 
}

/**
 * static void DrawBody( int line );
 *
 * Note : Show the notification Message Body( Content )
 *
 */
static void DrawBody( int x, int line )
{
    int y = line*16;
	unsigned short gbk;
	unsigned short unicode, len = 0;
	
	mq.pageLength = 0;
        
    for ( int i = mq.offset; i < mq.body_len; i += 2)
    {		
		len += 2;
		
		if ( ((mq.body[i] == 0x20) && (mq.body[i+1] == 0x2D)) 
			|| ( (mq.body[i] == 0x20) && (mq.body[i+1] == 0x2C)) 
			|| ( (mq.body[i] == 0x20) && (mq.body[i+1] == 0x0E)) 
			|| ( (mq.body[i] == 0x26) && (mq.body[i+1] == 0x0E)) 
			|| ( (mq.body[i] == 0x20) && (mq.body[i+1] == 0x2A)) 
			|| ( (mq.body[i] == 0xF3) && (mq.body[i+1] == 0xA4)) )
		{
			continue;
		}		
		
        if ( mq.body[i] == 0x0 /* && (mq.body[i+1] < 0x80)*/ )
        {
			if ( mq.body[i+1] < 0X20 || mq.body[i+1] > 0x7E ){
				continue;
			}
			
			{
				ASCII_GetData(mq.body[i+1],ASCII_8X16,DZ);
				DoRect8x16(x, y, DZ);
				x += 8;
				mq.pageLength += 2;
			}
        }else{
            unicode = (unsigned short)(mq.body[i]<<8) + mq.body[i+1];
            
			// add
			if (  (unicode>=0x2E80 && unicode<=0x2FDF) ||
				( (unicode>=0x3400) && (unicode <= 0x4DBE)) ||
			    ( (unicode>=0x4E00) && (unicode<=0x9FFF) ) )
			{
				// 中文区
				gbk = U2G(unicode );
				hzbmp16( SEL_GB, gbk ,0, 16, DZ ); 
				
				DoRect16x16(x,y,DZ);
				x += 16;
				mq.pageLength += 2;
			}else		
			if ( (unicode >= 0x1100 && unicode <= 0x11FF) ||
                (unicode>=0x3130 && unicode <= 0x318F) ||
                  (unicode >= 0xAC00 && unicode <= 0xD7AF) )
            {
				// 韩文区
				unsigned short ksc;
				
				ksc = U2K(unicode);
			    hzbmp16( SEL_KSC, ksc ,0, 16, DZ );
				
				DoRect16x16(x,y,DZ);
				x += 16;
				mq.pageLength += 2;
            }else if ( (unicode>=0x3040 && unicode<=0x30FF) ||
				( (unicode>=0x31F0) && (unicode <= 0x31FF)) ){
				// 日文区
				unsigned short jis;
					
				jis = U2J(unicode);
			    hzbmp16( SEL_JIS, jis ,0, 16, DZ );
				
				DoRect16x16(x,y,DZ);
				x += 16;	
				mq.pageLength += 2;
			}else{
				// 其他外国文字
				if ( (unicode>=0x0080 && unicode<=0x02AF) ||
					( (unicode>=0x1E00) && (unicode<=0x1EFF)) )
				{
					// 拉丁文
					// 包含但不限于：德语、法语、西班牙语、葡萄牙语
					//               意大利语
					LATIN_GetData(unicode,DZ);  // 不等宽
					DoRect8x16(x,y,DZ);
					x += 8;
					mq.pageLength += 2;
					
				}else if ( (unicode >= 0x0400) && (unicode <= 0x052F) )
				{
					// 西里尔文
					// 包含但不限于：俄语
					CYRILLIC_GetData(unicode,DZ); // // 不等宽
					DoRect8x16(x,y,DZ);
					x += 8;
					mq.pageLength += 2;					
				}else
				{
					// 按照汉字处理
					gbk = U2G(unicode );
					hzbmp16( SEL_GB, gbk ,0, 16, DZ ); 
					
					DoRect16x16(x,y,DZ);
					x += 16;
					mq.pageLength += 2;
				}
            }
			// end			
        }

//		if ( (i+2) >= mq.body_len ) { break; }
		
        if ( mq.body[i+2] == 0x0 ){
            if ( x+8 > LCD_W ) 
			{ 
				y += 16; x = 0; 			  
				if ( y >= LCD_H )
				{
					break;
				}
			} 
        }else{
            if ( (x+16) > LCD_W ) 
			{ 
				y += 16; x = 0;
				if ( y >= LCD_H )
				{
					break;
				}
			}
        }
    }    
	
	mq.last_show_cnt = len;	
}

#include "version.h"

void show_ui_version(void)
{
	mq.title_len = 12;
	
	mq.title[0] = 0x00;
	mq.title[1] = 'V';
	mq.title[2] = 0x00;
	mq.title[3] = '0' + VERSION_MAJOR;
	mq.title[4] = 0x00;
	mq.title[5] = '.';
	mq.title[6] = 0x00;	
	mq.title[7] = '0' + VERSION_MINOR;
	mq.title[8] = 0x00;
	mq.title[9] = '.';
	mq.title[10]= 0x00;
	mq.title[11]= '0' + VERSION_REVISON;
	
	ExitDeepSleepMode();
	
	DrawTitle();
	
	EntryDeepSleepMode();	
}

#include "UI_notify_icon.h"
void DrawIcon(void);

unsigned char ccflag = 0;
///////////////////////////////////通知界面(子界面：来电) //////////////////////

void ui_calling_notify( int msg_id, unsigned long arg)
{
    draw_fill(0,0,LCD_W,LCD_H,COLOR_B);
	
	ExitDeepSleepMode();	

	if ( (++ccflag %2 ) == 0){
		DrawIcon();
	}else
	{    
		if ( mq.title_len != 0 )
		{
			DrawTitle();
		}else if ( !(ccflag %2) )
		{
			DrawIcon();
		}    
	}
	
	EntryDeepSleepMode();	
	
    sync_frame();
}

void ui_erase_calling_notify(int msg_id, unsigned long arg)
{
    draw_fill(0,0,LCD_W,LCD_H,0x0000);
	
    sync_frame();
}

///////////////////////////////////通知界面(子界面:消息) //////////////////////

void DrawIcon(void)
{	
	if ( mq.type == NOTIFY_TYPE_CALL )
	{
		DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_Message2,RED);
		DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_Message1,0xFFFF);
	}else if ( mq.type == NOTIFY_TYPE_MSG )
	{
		DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_Message2,RED);
		DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_Message1,0xFFFF);	
	}else if ( mq.type == NOTIFY_TYPE_QQ)
	{
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_qq1,QQ);
	}else if ( mq.type == NOTIFY_TYPE_WX )
	{	
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_wx1,WEIXIN);
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_wx2,0xFFFF);
	}else if ( mq.type == NOTIFY_TYPE_WHATSAPP )
	{		
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_whatsapp1,WHATSAPP);
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_whatsapp2,0xFFFF);
	}else if ( mq.type == NOTIFY_TYPE_FACEBOOK )
	{		
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_facebook1,FACEBOOK);
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_facebook2,0xFFFF);	
	}else if ( mq.type == NOTIFY_TYPE_LINE )
	{
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_line1,0xFFFF);
		DrawUI_Bitmap_Exx( 28, 16,72,64,BMP_line2,LINE);	
	}
	else if ( mq.type == NOTIFY_TYPE_TT )
	{
		DrawUI_Bitmap_Exx( (LCD_W-83)/2, (LCD_H-84)/2, 83, 84, BMP_notify_cycle,0X633F);
		DrawUI_Bitmap_Exx( (LCD_W-64)/2, (LCD_H-52)/2, 64, 52, BMP_TT, 0xFFFF);
	}else if ( mq.type ==  NOTIFY_TYPE_SKYPE)
	{
		DrawUI_Bitmap_Exx( (LCD_W-83)/2, (LCD_H-84)/2, 83, 84, BMP_notify_cycle,0X633F);
		DrawUI_Bitmap_Exx( (LCD_W-58)/2, (LCD_H-60)/2, 58, 60, BMP_Skype, 0xFFFF);
	}else if ( mq.type ==  NOTIFY_TYPE_INS)
	{
		DrawUI_Bitmap_Exx( (LCD_W-86)/2, (LCD_H-86)/2, 86, 86, BMP_Ins, 0X6AD9);
	}
}

///////////////////////// APP 消息通知 /////////////////////////////////////////

void ui_app_notify( int msg_id, unsigned long arg )
{
    memset(fb, 0, sizeof(fb));

	ExitDeepSleepMode();
	
	if ( !( arg & 0x1) )
	{
		if ( (++ccflag %2 ) == 0){
			DrawIcon();
		}else
		{    
			if ( mq.title_len != 0 )
			{
				if ( ( (mq.push_by_ios == 1 
					&& mq.type == NOTIFY_TYPE_WHATSAPP ) ) 
                || ( (mq.type == NOTIFY_TYPE_WX) && (ancs_ancs_flag == 1))
                || ( mq.type == NOTIFY_TYPE_MSG )
				|| ((mq.push_by_ios == 1) && (mq.type == NOTIFY_TYPE_LINE)))
				{
					DrawTitle();
				}
			}else if ( !(ccflag %2) )
			{
				DrawIcon();
			}    
		}
	
	}else{

		DrawBody(0,0);
	}
	
	EntryDeepSleepMode();	
	
    sync_frame(); 
}

void ui_earse_app_notify( int msg_id, unsigned long arg ){}

///////////////////////////////////通知界面(子界面：闹钟) //////////////////////

#include "Ui_alarm_icon.h"	
#include "UI_comm_icon.h"
#include "UI_win_alarm.h"
#include "ClockTick.h"
#include "UI_main_icon.h"
	
static void DrawAlarmTimer(int x, int y, int hour, int minute )
{	
	draw_fill(0,0,LCD_W,LCD_H,0x0000);

	DrawUI_Bitmap_Ex( 2, 16, 56, 64, BMP_alarm2,BLUE);	
	DrawUI_Bitmap_Ex( 2, 16, 56, 64, BMP_alarm1,0XFFFF);	

	DrawUI_Bitmap_Ex( 62, 32, 12, 32, font_12x32[hour/10],0XFFFF);	
	DrawUI_Bitmap_Ex( 75, 32, 12, 32, font_12x32[hour%10],0XFFFF);
	DrawUI_Bitmap_Ex( 88, 32, 12, 32, font_12x32[10],0XFFFF);
	DrawUI_Bitmap_Ex( 101, 32, 12, 32, font_12x32[minute/10],0XFFFF);
	DrawUI_Bitmap_Ex( 114, 32, 12, 32, font_12x32[minute%10],0XFFFF);
}	
	
void ui_alarm_notify( int msg_id, unsigned long arg )
{
    draw_fill(0,0,LCD_W,LCD_H,0x0000);
    
    /* 绘制当前闹钟而不是下一个闹钟时间 */
    		
	if ( config.showFlag++ & 0x1 )
	{
		DrawAlarmTimer((80-53)/2,(160-42)/2, alarm.g_Ahour_cur, alarm.g_Amin_cur);
	}
    sync_frame();
}

void ui_erase_alarm_notify( int msg_id, unsigned long arg ){}

///////////////////////////////// 通知界面（子界面：手机找设备）////////////////


#include "UI_findphone_icon.h"	
	
void ui_find_me_notify( int msg_id, unsigned long arg )
{   
    draw_fill(0,0,LCD_W,LCD_H,0x0000);
    
	if ( config.showFlag++ & 0x1 )
	{
		DrawUI_Bitmap_Exx( 6,8,64,80,BMP_phonefind2, RED);
		DrawUI_Bitmap_Exx( 6,8,64,80,BMP_phonefind1, 0xFFFF);
		DrawUI_Bitmap_Exx( 80,36,42,24,BMP_FIND, 0xFFFF);	
//		if(x ==0)
//		{
//			
//			x++;
//		}
//		else if(x == 1)
//		{
//			
//			x++;
//		}
//		else if(x == 2){
//			
//			x++;
//		}
//		x%=3;
	}
	
    sync_frame();
}

void ui_erase_find_me_notify( int msg_id, unsigned long arg ){}

////////////////// 通知子界面 (蓝牙断开) ///////////////////////////////////////
void ui_ble_notify( int msg_id, unsigned long arg )
{  
    draw_fill(0,0,LCD_W,LCD_H,0x0000);

	if ( config.showFlag++ & 0x1 )
	{
		DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_ble_lose2,RED);	
		DrawUI_Bitmap_Exx( 4, 8,120,80,BMP_ble_lose1,0xFFFF);	
	}
	
    sync_frame();
}

void ui_erase_ble_notify( int msg_id, unsigned long arg ){}

////////////////// 通知子界面 (久坐提醒) ///////////////////////////////////////
void ui_sedentary_notify( int msg_id, unsigned long arg )
{  
    draw_fill(0,0,LCD_W,LCD_H,0x0000);

	if ( config.showFlag++ & 0x1 )
	{
		DrawUI_Bitmap_Exx( 8, 8,48,80,BMP_sedentary2,RED);	
		DrawUI_Bitmap_Exx( 8, 8,48,80,BMP_sedentary1,0xFFFF);	
		DrawUI_Bitmap_Exx( 64, 36,56,24,BMP_NOTICE,0xFFFF);	
	}
	
    sync_frame();
}
                                
void ui_erase_sedentary_notify( int msg_id, unsigned long arg ){}
	
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define NOTIFY_ID_TOINDEX(id) ((id)-1)

/* 根据通知类型的不同使用不同的提醒时长 */
static const int notify_max[7] =
{
    30, /* calling 15s */
    10, /* MESSAGE EMAIL 5s */
    4,  /* APP_MSG 2s */
    60, /* ALARM 30s */
    14, /* FINDME 7s */   
    8, /* BLE Disconnnected 2s */
    8, /* Sedentary notification 3s */    
};

typedef void (*notify_cb)(int msg_id, unsigned long arg);
struct notify
{
    notify_cb update;
    notify_cb close;
};

const struct notify ncb[7] = 
{
  [0] = {.update = ui_calling_notify,.close= ui_erase_calling_notify,},
  [1] = {.update = ui_app_notify,.close= ui_earse_app_notify,},
  [2] = {.update = ui_app_notify,.close = ui_earse_app_notify,},
  [3] = {.update = ui_alarm_notify,.close= ui_erase_alarm_notify,},
  [4] = {.update = ui_find_me_notify,.close= ui_erase_find_me_notify,},
  [5] = {.update = ui_ble_notify,.close= ui_erase_ble_notify,},
  [6] = {.update = ui_sedentary_notify,.close= ui_erase_sedentary_notify,},  
};

#include "LCD_ST7735.h"
#include "Task_Motor.h"
#include "Task_Finder.h"

unsigned char hangup_cmd[20] = {0xFC,0x08,0x03,00};

extern void LCD_Clear(void);

/***
 * 通知窗口消息处理函数
 */
unsigned long win_notify_proc(unsigned short wid, unsigned short msg_type, 
                            unsigned short msg_param, unsigned char *p)
{
    static unsigned char notify_id, flag = 0;
    
    /**
     * 创建窗体：绘制窗体本身的UI元素
     */
    if ( msg_type & WINDOW_CREATE )
    {  
		win_ticks = 0; flag = 0;
		
		if ( config.lcdEnable == 0 ){
			lcd_display(1);
		}
        
        notify_id = mq.notify_id;
		
		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
                
        return ( msg_type ^ WINDOW_CREATE );
    }
    
    /**
     * 更新窗体：根据参数更新整个窗体或者某些区域
     */
    if ( msg_type & WINDOW_UPDATE )
    {                
        if ( notify_id == NOTIFY_ID_INVALID )
        {
            msg_type |= WINDOW_DISTORY; // 结束被窗体，从窗体栈恢复上个窗体
            return ( msg_type ^ WINDOW_UPDATE );
        }
        
        if ( win_ticks++ < notify_max[notify_id-1] )
        {
			// 要调试来电通知，需要注释掉下面的#If语句;
			// #warning "test code enable ........."
			#if  1
			if ( notify_id == NOFIFY_ID_CALLING && ble.isConnected == 0)
			{
				// 来电提醒时间较长，直到挂断时才结束,若蓝牙在提醒过程中断开,
				// 则提醒结束,避免无法退出提醒.
				win_ticks = notify_max[notify_id-1];
				osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 1);
				return ( msg_type ^ WINDOW_UPDATE );
			}
			#endif
			
            ncb[NOTIFY_ID_TOINDEX(notify_id)].update(notify_id, flag);
           
            if ( flag == 0 )
            {
                if ( (win_ticks % 2 ) == 0 ) 
                {
                    if ( notify_id != NOFIFY_ID_CALLING 
						&& notify_id != NOTIFY_ID_EMAIL
						&& notify_id != NOTIFY_ID_APP_MSG
						&& notify_id != NOTIFY_ID_ALARM
						&& notify_id != NOTIFY_ID_BLE )
                    {   /* lcd_display(0); LCD_Clear(); */ }
                    // MOTOR_ENABLE(1);
					osal_set_event( taskMotorTaskId, TASK_MOTOR_ACTION_NOTIFY_EVT);
                }else {
                    // MOTOR_ENABLE(0);
                    if ( notify_id != NOFIFY_ID_CALLING 
						&& notify_id != NOTIFY_ID_EMAIL
						&& notify_id != NOTIFY_ID_APP_MSG
					    && notify_id != NOTIFY_ID_ALARM 
					    && notify_id != NOTIFY_ID_BLE )
                    {  /* lcd_display(1);*/ }
                }
            }
			osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
        }else{
            
            /* 本轮消息通知结束，查看是否有下一轮 */
            
            /** 一轮通知结束,查看是否有下一通知,如果有，则清除当前变量状态,退出当前
             *  通知,然后返回上一个界面，由上一个界面再进入通知界面
             * 否则，停留在当前通知界面
             */
            mq.notify_id = 0;   
           
            {
				if ( !((flag>>7) & 0x1) )
				{
					win_ticks = 0;
					osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 1);
				
					msg_type |= WINDOW_TOUCH;
				} else
				{
					ncb[NOTIFY_ID_TOINDEX(notify_id)].close(notify_id, 0);
					lcd_display(0);					
				}
			}				
            
            MOTOR_ENABLE(0);
        }
        
        return ( msg_type ^ WINDOW_UPDATE );
    }
    
    /**
     * Touch窗体
     */
    if ( msg_type & WINDOW_TOUCH )
    {
        /* 确保马达停止震动 */
            
        MOTOR_ENABLE(0);  
        
        if ( win_ticks < notify_max[notify_id-1] ) /** 提醒过程中触摸按键 */
        {
            if ( (notify_id == NOTIFY_ID_EMAIL) || (notify_id == NOTIFY_ID_APP_MSG)
				|| (notify_id == NOFIFY_ID_CALLING) )
            {				
				// 有Title或者Body的通知(来电、短信、QQ、微信)：
                if ( config.lcdEnable == 0 ){ 
					lcd_display(1); win_ticks = 0;
					osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
					return ( msg_type ^ WINDOW_TOUCH );
				}
                // 显示内容
                if ( ((flag >>7) & 0x1 ) != 1 )
                {
                  if ( (mq.body_len > 0) && (notify_id != NOFIFY_ID_CALLING)){
                    flag = (0x1<<7) | 0x1;  win_ticks = 0;
                  }else{  // 无内容：退出提醒
                    mq.notify_id = 0;
                    msg_type |= WINDOW_DISTORY; // 结束被窗体，从窗体栈恢复上个窗体                     
                  }
                }else{   
                  
                  if ( (mq.body_len == 0) || (notify_id == NOFIFY_ID_CALLING ) )
                  {
                    mq.notify_id = 0;
                    msg_type |= WINDOW_DISTORY; // 结束被窗体，从窗体栈恢复上个窗体                     
                  }
                  
                  if (GET_MESSAGE(msg_param) == WIN_MSG_KEY_LONG_TOUCH ){
                    mq.notify_id = 0;
                    msg_type |= WINDOW_DISTORY; // 结束被窗体，从窗体栈恢复上个窗体      
                  }else
                  {
					  /* 继续更新屏幕,显示内容 */
					  win_ticks = 0;
					  if ( MessageUpdatePage() == true )
					  {
						 msg_type |= WINDOW_DISTORY; 
						 return ( msg_type ^ WINDOW_TOUCH );
					  }
					  osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 50);
                  }
                }
            }else{
                // 无Title且无Body的通知其他通知(闹钟、手机防丢)：退出提醒界面
                if ( finder.cancelFindMe == 1 ) /* FindPhone任务模拟的"Touch"事件,她想提前结束提醒 */
                {
                    finder.cancelFindMe = 0;
                }else{
            
                    if ( notify_id == NOTIFY_ID_FINDME ) /* 手机查找设备中,发送一个确认 */
                    {
                        osal_set_event( taskFinderTaskId, FINDPHONE_TASK_FINDME_RESPONSE_EVT );
                    }
                }

                mq.notify_id = 0;
                msg_type |= WINDOW_DISTORY; // 结束被窗体，从窗体栈恢复上个窗体               
            }
            
        }else{        /** 提醒结束了才触摸按键: 重新点亮屏幕 */
           
            if ( config.lcdEnable == 0 ) /* LCD is off, Power on It */
            {
                lcd_display(1);
				osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
                mq.notify_id = notify_id;
            }else
			{   
				
			}  

			win_ticks = 0;
        }
		
		
		return ( msg_type ^ WINDOW_TOUCH );
    }
	
	/**
	 * 长按事件
	 */
	if ( msg_type & WINDOW_PRESS )
	{
		if ( config.lcdEnable == 0 )
		{
			win_ticks = 0;
            lcd_display(1);
			osal_set_event ( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		}else{
			
			if ( notify_id == NOFIFY_ID_CALLING )
			{
				if ( ancs_perform_notification_action(false) == false)
				{
					bt_protocol_tx(hangup_cmd, sizeof(hangup_cmd));
				}
			}
			
			mq.notify_id = 0;
			msg_type |= WINDOW_DISTORY; // 结束被窗体，从窗体栈恢复上个窗体			
		}
		
		return ( msg_type ^ WINDOW_PRESS );
	}

    /* 进入消息通知界面(来电,短信,邮件等.) */
    if ( msg_type & WINDOW_NOTIFY )
    {    
		win_ticks = 0, flag = 0;
		
		window[win_current].wproc(win_current, WINDOW_CREATE, 0, 0);
		
		return ( msg_type ^ WINDOW_NOTIFY );
    } 
    
    /**
     * 销毁窗体：擦除自己修改过的区域.
     */
    if ( msg_type & WINDOW_DISTORY )
    {
        MOTOR_ENABLE(0);
      
		window[win_current].arg = 0;
		window[win_current].msg_type = 0;
		window[win_current].param = 0;
		
		window_pop(&win_current);
		
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
    }
    
    return (0);
}
#ifndef __UI_MAIN_ICON_H__
#define __UI_MAIN_ICON_H__

#define  BLUE      COLORREF(  0, 159, 232)
#define  RED       COLORREF(255,   0,   0)
#define  GREEN     COLORREF(181, 255,   0)
#define WEIXIN     COLORREF( 69, 170, 105)
#define QQ         COLORREF( 51, 122, 183)
#define FACEBOOK   COLORREF( 40,  75, 136)
#define LINE       COLORREF( 64, 164,  55)
#define WHATSAPP   COLORREF( 42, 159, 119)
#define SLEEP      COLORREF(244, 217,  36)

extern const unsigned char *p_battery[];
extern const unsigned char battery_jpg_0[];
extern const unsigned char battery_jpg_1[];
extern const unsigned char battery_jpg_2[];
extern const unsigned char battery_jpg_3[];
extern const unsigned char battery_jpg_4[];
extern const unsigned char battery_jpg_5[];

extern const unsigned char *p_bletooth[];
extern const unsigned char bluetooth_jpg_yes[];
extern const unsigned char bluetooth_jpg_no[];

extern const unsigned char BMP_am[];
extern const unsigned char BMP_pm[];

extern const unsigned char Font_data_7x16[][16];
extern const unsigned char Font_time_18x40[][90];
extern const unsigned char Font_time_24x56[][168];

extern const unsigned char *p_main_week[];
extern const unsigned char jpg_week_7[];
extern const unsigned char jpg_week_1[];
extern const unsigned char jpg_week_2[];
extern const unsigned char jpg_week_3[];
extern const unsigned char jpg_week_4[];
extern const unsigned char jpg_week_5[];
extern const unsigned char jpg_week_6[];

extern const unsigned char jpg_main_2[];

extern const unsigned char BMP_week[][64];

// 旧
extern const unsigned char charge_bmp_battery[][296];
extern const unsigned short charge_color[];

#endif

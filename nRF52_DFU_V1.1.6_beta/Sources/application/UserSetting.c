
#include "UserSetting.h"

Configure_Typef config = {
    .viborate_enable  = 1,
    .sleepEnable = 0,
    .action_occur= 1,
    .hr_auto_enable  = 0,
    .autoSleepEnable = 0,
	.notify_enable = 0,
	.delay_timeout = 5,
	.control = 1,
	.lcdEnable = 0,
	.hrWaveUploadEnable = 0,
	.weight = DEFAULT_WEIGHT,
	.height = DEFAULT_HEIGHT,
	.unit = 0,
	.time_format = 1,
	.lcd_level = LCD_LEVEL,
	.ui_style = 0,
	.enable = 1,
	.hflag = 0,
	.sleep_mode = 0, .last_sleep_mode = 0,
	.gsensor_debug = 0,
};

SportMonitor_Typdef monitor = 
{
    .ss = 0x00,
    .interval = 0,
    .sedentary_start = 0x0,
    .sedentary_end = 0x0,
    .start = 0x0,
    .end = 0x0,
    .pedometer = 100,
};

#define DEFAULT_TOUCH_LEVEL     1300

HerateTypdef hr = {
	.hr = 75,                         	// 默认心率
	.hp = 125,                        	// 默认高压
	.lp = 75,                         	// 默认低压
	.sp_h = 99, 	                   	// 默认血氧整数
	.sp_l = 5,                          // 默认血氧小数
	.stop = 1,                        	// 初始状态：停止
	.stat = HR_DECT_STAT_NONE,        	// 初始测试：NONE
	.auto_flag = 0,
	.auto_measure_enable = 1,         	// 定时测量：使能
	.auto_measure_interval = 0x1E,    	// 定时间隔：30分钟
	.touch_level = DEFAULT_TOUCH_LEVEL, // 脱手识别等级
	.measure = 0,
};

BLE_Typdef ble = {
	.isConnected = 0,
	.ancs_notify_enable = 0,
};

unsigned char ancs_ancs_flag = 0;

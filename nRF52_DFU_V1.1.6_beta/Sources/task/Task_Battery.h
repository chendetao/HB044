#ifndef __TASK_BATTERY_H__
#define __TASK_BATTERY_H__

#define TASK_BATTERY_QUERY_EVT  		0x00000001
#define TASK_MINITE_TIMEOUT_EVT 		0x00000002
#define TASK_BATTERY_DECT_EVT   		0x00000004
#define TASK_BATTERY_CHARGE_EVT 		0x00000008
#define TASK_BATTERY_INIT_EVT   		0x00000010
#define TASK_BATTERY_RESET_FLAG_EVT 	0x00000020
#define TASK_BATTERY_FEED_ARRAY_EVT     0x00000040
#define TASK_BATTERY_PROTECT_EVT        0x00000080

#define TASK_BATTERY_COMFIRM_EVT        0x00000100

#define BATTERY_RATE 	1

typedef struct
{
	unsigned char battery_level;
	unsigned char battery_low:1;
	unsigned char charge_flage:1;
	unsigned char ble_signal:6;
	unsigned char compelete:1;
	unsigned char ok:1;    
	unsigned int time_after_last;    
}Power_Typdef;

extern Power_Typdef power;
extern short current_adc;

extern unsigned char taskBatteryTaskId;

extern unsigned long taskBattery( unsigned char task_id, unsigned long events );
extern void taskBatteryInit( unsigned char task_id );

#endif

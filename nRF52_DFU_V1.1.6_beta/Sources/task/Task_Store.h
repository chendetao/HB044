#ifndef __TASK_SOTRE_H__
#define __TASK_SOTRE_H__


#define TASK_STORE_SAVE_PRESS_UPS_EVT       0x00000800
#define TASK_STORE_SAVE_ROPO_SKIPPING_EVT   0x00000400
#define TASK_STORE_MEASURE_EVT          	0x00000200
#define TASK_STORE_UPLOAD_RUNNING_EVT   	0x00000100
#define TASK_STORE_SAVE_SWIMMING_EVT    	0x00000080
#define TASK_STORE_SAVE_RUNNING_EVT     	0x00000040
#define TASK_STORE_SAVE_BYCLE_EVT       	0x00000020
#define TASK_STORE_SAVE_SEG_PEDO_EVT    	0x00000010
#define TASK_STORE_SAVE_SPO2_EVT       		0x00000008
#define TASK_STORE_SAVE_B_PRESSURE_EVT 		0x00000004
#define TASK_STORE_SAVE_HR_EVT     			0x00000002
#define TASK_STORE_SAVE_PEDO_EVT       		0x00000001

extern unsigned char taskStoreTaskId;

extern unsigned long taskStore( unsigned char task_id, unsigned long events );
extern void taskStoreInit( unsigned char task_id );

#endif

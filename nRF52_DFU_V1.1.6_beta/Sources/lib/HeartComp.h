/*******************************************************************************
* Copytight 2016 Mandridy Tech.Co., Ltd. All rights reserved 
*
* Filename : HeartComp.h
* Author : Wen Shifang
* Version : 1.0
*
* Decription : File HeartComp.c implements the heart compensate function.
* Function-list:
* History:
*       <author>     <time>    <version>  <desc>
*       Wen Shifang  2017-3.2  1.0        build this moudle
*
* Created : 2017-3.2 
* Last modified : 2017-12.1 
*******************************************************************************/

#ifndef __HEART_COMP_H__
#define __HEART_COMP_H__
   
#define MINUTE                   2     /* update every 4 minutes */   
#define UPDATE_RATE              15    /* update every 15 minutes */
   
#define COM_ARRAY_SIZE          ((60*MINUTE)/UPDATE_RATE)
#define MAX_PEDOMETER_AT_MINUTES ((1000/250)*60*MINUTE)

extern void heart_comp_pedometer( unsigned long val );
extern void heart_comp_gsensor( short x, short y, short z);
extern unsigned char heart_get_comp_val(void);
extern unsigned short heart_get_comp_blood_pressure_val(int hr);
extern void heart_set_base_heart( unsigned char val );
extern void heart_comp_init(unsigned char year, unsigned char height,
	unsigned char weight );
extern float heart_get_comp_spo2( int hr);

#endif

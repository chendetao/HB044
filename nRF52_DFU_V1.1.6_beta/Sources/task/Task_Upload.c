#include "string.h"
#include "time.h"
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_Step.h"
#include "Task_Upload.h"
#include "Task_Flash.h"

#include "ClockTick.h"
#include "btprotocol.h"
#include "UserSetting.h"
	
unsigned char taskUploadTaskId;

unsigned char pedo_all;
unsigned char pedo_done;
unsigned char sleep_all;
unsigned char sleep_done;
unsigned short hr_all;
unsigned short hr_done;
unsigned char bp_all;
unsigned char bp_done;
unsigned char sp_all;
unsigned char sp_done;    
unsigned char seg_pedo_all;
unsigned char seg_pedo_done;
unsigned char running_all;
unsigned char running_done; 

unsigned long taskUpload( unsigned char task_id, unsigned long events )
{
    static unsigned char txbuf[20]  = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};   
    
    unsigned char buf[16];
	int fret;
		
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the pedometer data saved in NV Flash to the app                 //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////	

    if( events & TASK_UPLOAD_PEDO_1_EVT )
    {
        /** Dont' send if bluetooth is disconnected */
		
        if( ble.isConnected != 1){
            return (events ^ TASK_UPLOAD_PEDO_1_EVT );
        }
		
		memset( txbuf, 0, sizeof(txbuf));
 
        txbuf[0] = 0x03;
        txbuf[1] = 0xC0;
        txbuf[2] = pedo_all;
        txbuf[3] = pedo_done;
        txbuf[19]= 0x0;
        
        if ( pedo_all != 0 )
        {            
            fret = flash_memory_get ( FM_ID_PEDOMETER, buf, 16, false );
            if ( fret == 0 ) {
                memcpy( txbuf+4, buf, 16 );
            }else if ( fret == -1 ){
                osal_start_timerEx( task_id, TASK_UPLOAD_PEDO_1_EVT, 50);
                return (events ^ TASK_UPLOAD_PEDO_1_EVT);
            }else{
                return (events ^ TASK_UPLOAD_PEDO_1_EVT);
            }                
        }else
        {
            memset( txbuf+4, 0, 8);
        }
        
        bt_protocol_tx ( txbuf, sizeof(txbuf) );
        
        if ( ++pedo_done < pedo_all )
        {  /* Done */
            osal_start_timerEx( task_id, TASK_UPLOAD_PEDO_1_EVT, 50);
        }else{
            pedo_done = 0;
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );
        }
        
        return (events ^ TASK_UPLOAD_PEDO_1_EVT);
    }
    	
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the sleep data saved in NV Flash to the app                     //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////	
    
    if( events & TASK_UPLOAD_SL_1_EVT )
    {
        /** Dont' send if bluetooth is disconnected */
        if( ble.isConnected != 1){
            return ( events ^ TASK_UPLOAD_SL_1_EVT );
        }
		
		memset( txbuf, 0, sizeof(txbuf));
 
        txbuf[0] = 0x0C; 
		txbuf[1] = 0x01;
        txbuf[2] = sleep_all;
        txbuf[3] = sleep_done;
        txbuf[19] = 0x0;
        
        if ( sleep_done < sleep_all )
        {
        	fret = flash_memory_get( FM_ID_SLEEP, buf, 16, false );
			if ( fret == -1 )
			{
                osal_start_timerEx( task_id, TASK_UPLOAD_SL_1_EVT, 50);
				return ( events ^ TASK_UPLOAD_SL_1_EVT ); 
			}else if ( fret == -2 )
            {
                return (events ^ TASK_UPLOAD_SL_1_EVT);
            }else{
                memcpy( txbuf+4, buf, 16);
            }
        }else
        {
            memset( txbuf+4, 0, 16);
        }
        
        bt_protocol_tx ( txbuf, sizeof(txbuf) ); 
        
        if ( ++sleep_done < sleep_all ){  /* Done ? */
            osal_start_timerEx( task_id, TASK_UPLOAD_SL_1_EVT, 50);
        }else{
            sleep_done = 0;
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );
        }
        
        return (events ^ TASK_UPLOAD_SL_1_EVT);
    }
        
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the heart rate saved in NV Flash to the app                     //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////	
	
    if( events & TASK_UPLOAD_HR_1_EVT )
    {        
        /** Dont' send if bluetooth is disconnected */
        if( ble.isConnected != 1){
            return (events ^ TASK_UPLOAD_HR_1_EVT);
        }
		
		memset( txbuf, 0, sizeof(txbuf));
        
		// 心率
		// 0x0A 01 00 00 00 00 YY MM DD hh mm ss Hr 00 00 00 00 00 00 00
        txbuf[0] = 0x0A;
        txbuf[1] = 0x01;
        txbuf[2] = hr_all  / 256;
        txbuf[3] = hr_all  % 256;
        txbuf[4] = hr_done / 256;
        txbuf[5] = hr_done % 256;
        txbuf[19]= 0x0;
        
        if ( hr_all != 0 )
        {
        	fret = flash_memory_get(FM_ID_HR, buf, 16, false );
			if ( fret == -1 )
            {
                osal_start_timerEx( task_id, TASK_UPLOAD_HR_1_EVT, 50);
				return ( events ^ TASK_UPLOAD_HR_1_EVT );                 
            }else if ( fret == -2 )
            {
                return ( events ^ TASK_UPLOAD_HR_1_EVT );
            }else{
                memcpy( txbuf+6, buf, 7);	
            }                
        }else
        {
            memset( buf, 0, 16);
        }
        
        bt_protocol_tx ( txbuf, sizeof(txbuf) ); 
			
        if ( ++hr_done < hr_all ){  /* Done */
            
            osal_start_timerEx( task_id, TASK_UPLOAD_HR_1_EVT, 50);
        }else{
            hr_done = 0;
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );
        }     

		return ( events ^ TASK_UPLOAD_HR_1_EVT );
	}
		
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the blood pressure saved in NV Flash to the app                 //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////
	
	if ( events & TASK_UPLOAD_B_PRESSURE_1_EVT )
	{
        /** Dont' send if bluetooth is disconnected */
        if ( ble.isConnected != 1 )
        {
            return ( events ^ TASK_UPLOAD_B_PRESSURE_1_EVT );
        } 
		
		memset( txbuf, 0, sizeof(txbuf));

		// 血压 0x11 01 Ah Al Ch Cl YY MM DD hh mm ss Hp Lp Hr 00 00 00 00 00
        txbuf[0] = 0x11;
        txbuf[1] = 0x01;
        txbuf[2] = bp_all  / 256;
        txbuf[3] = bp_all  % 256;
        txbuf[4] = bp_done /256;
        txbuf[5] = bp_done % 256;
        txbuf[19] = 0x0;

        if ( bp_all != 0 )
        {
        	fret = flash_memory_get( FM_ID_B_PRESSURE, buf, 16, false );
			if ( fret == -1 )
			{
                osal_start_timerEx( task_id, TASK_UPLOAD_B_PRESSURE_1_EVT, 50);
				return ( events ^ TASK_UPLOAD_B_PRESSURE_1_EVT ); 
			}else if ( fret == -2 )
            {
                return (events ^ TASK_UPLOAD_B_PRESSURE_1_EVT);
            }else{

                memcpy(txbuf+6, buf, 9);
            }
        }		
        
        bt_protocol_tx ( txbuf, sizeof(txbuf) ); 
        
        if ( ++bp_done < bp_all ){  /* Done */

            osal_start_timerEx( task_id, TASK_UPLOAD_B_PRESSURE_1_EVT, 50);
        }else{
            bp_done = 0;
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );            
        }
        
        return (events ^ TASK_UPLOAD_B_PRESSURE_1_EVT);
    }
	    
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the SP02 saved in NV Flash to the app                           //
    //                                                                        //
    //////////////////////////////////////////////////////////////////////////// 	
	
    if( events & TASK_UPLOAD_SP02_1_EVT )
    {
        /** Dont' send if bluetooth is disconnected */
        if( ble.isConnected != 1){
            return (events ^ TASK_UPLOAD_SP02_1_EVT );
        }
		
		memset( txbuf, 0, sizeof(txbuf));
        
		// 血氧
        txbuf[0] = 0x12;
        txbuf[1] = 0x01;
        txbuf[2] = sp_all / 256;
        txbuf[3] = sp_all % 256;
        txbuf[4] = sp_done/256;
        txbuf[5] = sp_done % 256;
        txbuf[19] = 0x0;
		
        if ( sp_all != 0 )
        {
        	fret = flash_memory_get( FM_ID_SPO2, buf, 16, false );
			if ( fret == -1  )
			{
                osal_start_timerEx( task_id, TASK_UPLOAD_SP02_1_EVT, 50);
				return ( events ^ TASK_UPLOAD_SP02_1_EVT ); 
			}else if ( fret == -2 ){
                return ( events ^ TASK_UPLOAD_SP02_1_EVT ); 
            }else{
                memcpy( txbuf + 6, buf, 8);
            }
        }else
        {
            memset( txbuf + 6, 0, 8);
        }
        		
        bt_protocol_tx( txbuf, sizeof(txbuf) ); 
		        
        if ( ++sp_done < sp_all ){  /* Done ? */

            osal_start_timerEx( task_id, TASK_UPLOAD_SP02_1_EVT, 50);
        }else{
            sp_done = 0;
            
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );  
        }
        
        return (events ^ TASK_UPLOAD_SP02_1_EVT);
    }

    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the segment pedometer data to app                               //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////	
    if( events & TASK_UPLOAD_SEG_PEDO_1_EVT )
    {
		unsigned long temp;
        
        /** Dont' send if bluetooth is disconnected */
        if( ble.isConnected != 1){
            return (events ^ TASK_UPLOAD_SEG_PEDO_1_EVT );
        }
		
		memset( txbuf, 0, sizeof(txbuf));

		// Segment pedometer
		// 0x1A EN A3 A2 A1 00 00 00  00 00 00 00 00 00 t1  t2  t3  t4  CN   00
        txbuf[0] = 0x1A;
        txbuf[1] = 0x04;
		
		temp = (seg_pedo_all << 12) | (seg_pedo_done & 0xFFF);
		txbuf[2] = (temp>>16) & 0xFF;
		txbuf[3] = (temp>>8) & 0xFF;
		txbuf[4] = (temp>>0) & 0xFF;
		
        if ( seg_pedo_all != 0 )
        {
			fret = flash_memory_get( FM_ID_SEG_PEDO, buf, 16, false );
			if ( fret == -1 )
			{
                osal_start_timerEx( task_id, TASK_UPLOAD_SEG_PEDO_1_EVT, 50);
				return ( events ^ TASK_UPLOAD_SEG_PEDO_1_EVT ); 
			}else if ( fret == -2 )
            {
                return ( events ^ TASK_UPLOAD_SEG_PEDO_1_EVT ); 
            }else{
                memcpy( txbuf + 5, buf, 14);
            }
        }else
        {
            memset( txbuf + 5, 0, 16);
        }
		
        bt_protocol_tx( txbuf, sizeof(txbuf) ); 
		
        if ( ++seg_pedo_done < seg_pedo_all ){  /* Done ? */      
            osal_start_timerEx( task_id, TASK_UPLOAD_SEG_PEDO_1_EVT, 50);
        }else{
            seg_pedo_done = 0;
            
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );  
        }
        
        return (events ^ TASK_UPLOAD_SEG_PEDO_1_EVT);
    }
    	
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // Upload the running data to app                                         //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////	
    if ( events & TASK_UPLOAD_STORE_RUNNING_1_EVT )
    {
        // 运动数据
        // 格式：1B EN SS C2 C1 C0 D6 D5 D4 D3 D2 D1 D0 U3 U2 U1 U0 TH TL CRC
        
        /** 蓝牙断开,不发送 */
        if ( ble.isConnected != 1 ){
            return (events ^ TASK_UPLOAD_STORE_RUNNING_1_EVT);
        }
		
		memset( txbuf, 0, sizeof(txbuf));
        
        txbuf[0] = 0x1B;
        txbuf[1] = 0x01;    // EN
        txbuf[2] = 0x00;    // SS
        
        txbuf[3] = running_all>>4;
        txbuf[4] = ((running_all & 0Xf)<<4) | ((running_done>>8)&0xF);
        txbuf[5] = running_done & 0xFF;
       		
        if ( running_all != 0 )
        {
			fret = flash_memory_get( FMC_ID_RUNNING, buf, 16, false );
			if ( fret == -1 )
			{
                osal_start_timerEx( task_id, TASK_UPLOAD_STORE_RUNNING_1_EVT, 50);
				return ( events ^ TASK_UPLOAD_STORE_RUNNING_1_EVT ); 
			}else if ( fret == -2 )
            {
                return (events ^ TASK_UPLOAD_STORE_RUNNING_1_EVT);
            }
        }
		
		txbuf[1] |= (buf[0] & 0xF0); // EN
		txbuf[2] = buf[1]; // SS
		memcpy( txbuf+6, buf+2, 7+4+2);                 
        
        bt_protocol_tx(txbuf, 20); 
        
        if ( ++running_done < running_all ){  /* Done ? */
            osal_start_timerEx( task_id, TASK_UPLOAD_STORE_RUNNING_1_EVT, 50);
        }else{
            running_done = 0;
            
            osal_start_timerEx ( taskFlashTaskId, TASK_FLASH_UPDATE_EVT, 3000 );  
        }           
        
        return (events ^ TASK_UPLOAD_STORE_RUNNING_1_EVT);
    }
    
		
    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    //  上传本次(最近一次)的结果                                              //
    //                                                                        //
    //////////////////////////////////////////////////////////////////////////// 
	
	/* Upload the current pedometer data to app */

	if ( events & TASK_UPLOAD_PEDO_EVT )
	{
		if ( ble.isConnected != 1 )
		{
			return ( events ^ TASK_UPLOAD_PEDO_EVT );
		}
		
		memset( txbuf, 0, sizeof(txbuf));
		
		txbuf[0] = 0x03;
		txbuf[1] = 0x07;

		txbuf[2] = pedometer.counter>>16;
		txbuf[3] = pedometer.counter>>8;
		txbuf[4] = pedometer.counter>>0;
		
		txbuf[5] = pedometer.distance>>16;
		txbuf[6] = pedometer.distance>> 8;
		txbuf[7] = pedometer.distance>> 0;

		txbuf[8] = pedometer.calorie>>16;
		txbuf[9] = pedometer.calorie>> 8;
		txbuf[10]= pedometer.calorie>> 0;
			
		bt_protocol_tx( txbuf, 20 );
		
		return ( events ^ TASK_UPLOAD_PEDO_EVT );
	}
	
	/** 上传心率值 */
    if ( events & TASK_UPLOAD_HR_EVT )
    {
        memset( txbuf, 0, sizeof(txbuf) );
        
        txbuf[0]  = 0x0A;
		txbuf[1]  = 0x00;
		
        txbuf[6]  = DECToBCD(TimerYY());
        txbuf[7]  = DECToBCD(TimerMM());
        txbuf[8]  = DECToBCD(TimerDD());
        txbuf[9]  = DECToBCD(TimerHH());
        txbuf[10] = DECToBCD(TimerMI());
        txbuf[11] = DECToBCD(TimerSE());
        
        // 心率 0x0A 00 00 00 00 00 YY MM DD hh mm ss Hr 00 00 00 00 00 00 00
        
        txbuf[12] = hr.hr;
        
        bt_protocol_tx( txbuf, sizeof(txbuf) );
		
		return ( events ^ TASK_UPLOAD_HR_EVT );
	}
	        
	/* 上传血压数据 */
	if ( events & TASK_UPLOAD_B_PRESSURE_EVT )
    {
        memset( txbuf, 0, sizeof(txbuf) );

        txbuf[0]  = 0x11;
		txbuf[1]  = 0x00;
		
        txbuf[6]  = DECToBCD(TimerYY());
        txbuf[7]  = DECToBCD(TimerMM());
        txbuf[8]  = DECToBCD(TimerDD());
        txbuf[9]  = DECToBCD(TimerHH());
        txbuf[10] = DECToBCD(TimerMI());
        txbuf[11] = DECToBCD(TimerSE());

        // 血压 0x11 00 00 00 00 00 YY MM DD hh mm ss HP LP Hr 00 00 00 00 00
        
        txbuf[12] = hr.hp;
        txbuf[13] = hr.lp;
        txbuf[14] = hr.hr;
        
        bt_protocol_tx( txbuf, sizeof(txbuf) );
		
		return ( events ^ TASK_UPLOAD_B_PRESSURE_EVT );
	}

	/** 上传血氧数据 */
	if ( events & TASK_UPLOAD_SPO2_EVT )
    {
        memset( txbuf, 0, sizeof(txbuf) );
        
        txbuf[0]  = 0x12;
		txbuf[1]  = 0x00;
		
        txbuf[6]  = DECToBCD(TimerYY());
        txbuf[7]  = DECToBCD(TimerMM());
        txbuf[8]  = DECToBCD(TimerDD());
        txbuf[9]  = DECToBCD(TimerHH());
        txbuf[10] = DECToBCD(TimerMI());
        txbuf[11] = DECToBCD(TimerSE());
		
        // 血氧 0x12 00 00 00 00 00 YY MM DD hh mm ss SH SL 00 00 00 00 00 00
        
        txbuf[12] = hr.sp_h;
        txbuf[13] = hr.sp_l;
            
        bt_protocol_tx( txbuf, sizeof(txbuf) );
        
        return ( events ^ TASK_UPLOAD_SPO2_EVT );
    }
	
	/* 上传睡眠数据 */
	if ( events & TASK_UPLOAD_SL_EVT )
	{
		// 睡眠 0x0C Ty AL CU YY MM DD hh mm YY MM DD hh mm Dh Dl Lh Ll 00 00
		
        memset( txbuf, 0, sizeof(txbuf) );
        
        txbuf[0] = 0x0C;
        txbuf[1] = 0x00;
        txbuf[2] = 0x00;
        txbuf[3] = 0x00;
        
		bt_protocol_tx( txbuf, sizeof(txbuf) );
		
		return ( events ^ TASK_UPLOAD_SL_EVT );
	}
	
	/** 新增iBand支持，测量完成时,通知APP读取 */
    if ( events & TASK_UPLOAD_HR_DONE_EVT )
    {
		// 0xFC 09 00 00 00 00 YY MM DD hh mm ss Hr 00 00 00 00 00 00 00
        memset( txbuf, 0, sizeof(txbuf) );
        
        txbuf[0]  = 0xFC;
		txbuf[1]  = 0x09;
        txbuf[2]  = 0X00;	
		txbuf[3]  = hr.measure;
       
        bt_protocol_tx( txbuf, sizeof(txbuf) );
		
		return ( events ^ TASK_UPLOAD_HR_DONE_EVT );
	}	
	
	/** 新增iBand支持，测量中,上报心率数据 */
    if ( events & TASK_UPLOAD_iBand_HR_DECT_EVT )
    {
		// 0x0A 03 00 00 00 00 YY MM DD hh mm ss Hr 00 00 00 00 00 00 00
        memset( txbuf, 0, sizeof(txbuf) );
        
        txbuf[0]  = 0x0A;
		txbuf[1]  = 0x03;
		
        txbuf[6]  = DECToBCD(TimerYY());
        txbuf[7]  = DECToBCD(TimerMM());
        txbuf[8]  = DECToBCD(TimerDD());
        txbuf[9]  = DECToBCD(TimerHH());
        txbuf[10] = DECToBCD(TimerMI());
        txbuf[11] = DECToBCD(TimerSE());

        txbuf[12] = hr.hr;
       
        bt_protocol_tx( txbuf, sizeof(txbuf) );
		
		return ( events ^ TASK_UPLOAD_iBand_HR_DECT_EVT );
	}	
	
	/** 新增iBand支持，测量中,上报血压数据 */
	if ( events & TASK_UPLOAD_iBand_B_PRUESSURE_EVT )
	{
		// 0x11 03 00 00 00 00 YY MM DD hh mm ss HP LP Hr 00 00 00 00 00
		
        memset( txbuf, 0, sizeof(txbuf) );

        txbuf[0]  = 0x11;
		txbuf[1]  = 0x03;
		
        txbuf[6]  = DECToBCD(TimerYY());
        txbuf[7]  = DECToBCD(TimerMM());
        txbuf[8]  = DECToBCD(TimerDD());
        txbuf[9]  = DECToBCD(TimerHH());
        txbuf[10] = DECToBCD(TimerMI());
        txbuf[11] = DECToBCD(TimerSE());
        
        txbuf[12] = hr.hp;
        txbuf[13] = hr.lp;
        txbuf[14] = hr.hr;
        
        bt_protocol_tx( txbuf, sizeof(txbuf) );
		
		return ( events ^ TASK_UPLOAD_iBand_B_PRUESSURE_EVT ); 
	}
	
	/** 新增iBand支持，测量中,上报血氧数据 */
	if ( events & TASK_UPLOAD_iBand_SPO2_EVT )
    {
        memset( txbuf, 0, sizeof(txbuf) );
        
        txbuf[0]  = 0x12;
		txbuf[1]  = 0x03;
		
        txbuf[6]  = DECToBCD(TimerYY());
        txbuf[7]  = DECToBCD(TimerMM());
        txbuf[8]  = DECToBCD(TimerDD());
        txbuf[9]  = DECToBCD(TimerHH());
        txbuf[10] = DECToBCD(TimerMI());
        txbuf[11] = DECToBCD(TimerSE());
		
        // 血氧 0x12 03 00 00 00 00 YY MM DD hh mm ss SH SL 00 00 00 00 00 00
        
        txbuf[12] = hr.sp_h;
        txbuf[13] = hr.sp_l;
            
        bt_protocol_tx( txbuf, sizeof(txbuf) );
        
        return ( events ^ TASK_UPLOAD_iBand_SPO2_EVT );
    }	
	
	/** 新增iBand支持，上报分段计步数据 */
	if ( events & TASK_UPLOAD_iBand_SEG_PEDO_EVT )
    {
		// 0x1A 01 00 00 00 00 00 00 00 00 00 00 00 00 t1 t2 t3 t4 CN 00
		if ( ble.isConnected != 1 )
		{
			return ( events ^ TASK_UPLOAD_iBand_SEG_PEDO_EVT );
		}
		
		unsigned long utc;
		struct tm time;
		
		time.tm_hour = TimerHH();
		time.tm_min = TimerMI();
		time.tm_sec = TimerSE();
		time.tm_mday = TimerDD();
		time.tm_mon = TimerMM()-1;
		time.tm_year = TimerYY()+2000 - 1900;
		utc = mktime(&time);		
		
		memset( txbuf, 0, sizeof(txbuf));
		
		txbuf[0] = 0x1A;
		txbuf[1] = 0x01;
		txbuf[2] = 0x00;
		txbuf[3] = 0x00;
		txbuf[4] = 0x00;

		txbuf[5] = pedometer_last.counter>>16;
		txbuf[6] = pedometer_last.counter>>8;
		txbuf[7] = pedometer_last.counter>>0;
		
		txbuf[8]  = pedometer_last.distance>>16;
		txbuf[9]  = pedometer_last.distance>> 8;
		txbuf[10] = pedometer_last.distance>> 0;

		txbuf[11] = pedometer_last.calorie>>16;
		txbuf[12] = pedometer_last.calorie>> 8;
		txbuf[13] = pedometer_last.calorie>> 0;
		
		txbuf[14] = (utc>>24) & 0xFF;
		txbuf[15] = (utc>>16) & 0xFF;
		txbuf[16] = (utc>>8) & 0xFF;
		txbuf[17] = (utc>>0) & 0xFF;
		txbuf[18] = 0x3C;		
			
		bt_protocol_tx( txbuf, 20 );
        
        return ( events ^ TASK_UPLOAD_iBand_SEG_PEDO_EVT );
    }	
	    	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载计步数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_PEDO_EVT )
	{
        pedo_all = fm.erea[FM_ID_PEDOMETER].items;
        pedo_done = 0;
        
        if ( fm.erea[FM_ID_PEDOMETER].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
			memset( txbuf, 0, sizeof(txbuf));
 
			txbuf[0] = 0x03;
			txbuf[1] = 0xC0;            
        }else if ( pedo_all == 0 )
        {
			memset( txbuf, 0, sizeof(txbuf));
 
			txbuf[0] = 0x03;
			txbuf[1] = 0xC0;	

			bt_protocol_tx( txbuf, sizeof(txbuf) );            
        }else{
            osal_start_timerEx ( task_id, TASK_UPLOAD_PEDO_1_EVT, 50);
        }		
		
		return ( events ^ TASK_UPLOAD_STORE_PEDO_EVT );
	}	
	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载睡眠数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_SL_EVT )
	{        
        sleep_all = fm.erea[FM_ID_SLEEP].items;
        sleep_done = 0;
        
        if ( fm.erea[FM_ID_SLEEP].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
            memset( txbuf, 0, sizeof(txbuf));

            txbuf[0] = 0x0C; 
            txbuf[1] = 0x01;

            bt_protocol_tx( txbuf, sizeof(txbuf) );
        }else if ( fm.erea[FM_ID_SLEEP].items == 0 )
        {
            memset( txbuf, 0, sizeof(txbuf));

            txbuf[0] = 0x0C; 
            txbuf[1] = 0x01;
            
            bt_protocol_tx( txbuf, sizeof(txbuf) );            
        }else{
			osal_set_event ( task_id, TASK_UPLOAD_SL_1_EVT );
		}
        
		return ( events ^ TASK_UPLOAD_STORE_SL_EVT );
	}	
	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载心率数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_HR_EVT )
	{   
        hr_done = 0;
        hr_all = fm.erea[FM_ID_HR].items;
        
        if ( fm.erea[FM_ID_HR].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x0A;
            txbuf[1] = 0x01;   
            
            bt_protocol_tx( txbuf, sizeof(txbuf) );			
        }else if ( fm.erea[FM_ID_HR].items == 0 ){  

            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x0A;
            txbuf[1] = 0x01;                
            bt_protocol_tx( txbuf, sizeof(txbuf) );	
            
        }else{
            osal_set_event ( task_id, TASK_UPLOAD_HR_1_EVT );
        }
				
		return ( events ^ TASK_UPLOAD_STORE_HR_EVT );
	}
	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载血压数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_B_P_EVT )
	{        
        bp_done = 0;
        bp_all = fm.erea[FM_ID_B_PRESSURE].items;
        
        if ( fm.erea[FM_ID_B_PRESSURE].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x11;
            txbuf[1] = 0x01;   
            
            bt_protocol_tx( txbuf, sizeof(txbuf) );			
        }else if ( fm.erea[FM_ID_B_PRESSURE].items == 0 ){  

            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x11;
            txbuf[1] = 0x01;                
            bt_protocol_tx( txbuf, sizeof(txbuf) );	
            
        }else{
            osal_set_event ( task_id, TASK_UPLOAD_B_PRESSURE_1_EVT );
        }        
		
		return ( events ^ TASK_UPLOAD_STORE_B_P_EVT );
	}
	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载血氧数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_SPO2_EVT )
	{
        sp_done = 0;
        sp_all = fm.erea[FM_ID_SPO2].items;
        
        if ( fm.erea[FM_ID_SPO2].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x12;
            txbuf[1] = 0x01;   
            
            bt_protocol_tx( txbuf, sizeof(txbuf) );			
        }else if ( fm.erea[FM_ID_SPO2].items == 0 ){  

            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x12;
            txbuf[1] = 0x01;                
            bt_protocol_tx( txbuf, sizeof(txbuf) );	
            
        }else{
            osal_set_event ( task_id, TASK_UPLOAD_SP02_1_EVT );
        }		
		
		return ( events ^ TASK_UPLOAD_STORE_SPO2_EVT );
	}	
	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载分段计步数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_SEG_PEDO_EVT )
	{
        unsigned long temp;
        seg_pedo_all = fm.erea[FM_ID_SEG_PEDO].items;
        seg_pedo_done = 0;
        
        if ( fm.erea[FM_ID_SEG_PEDO].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
			memset( txbuf, 0, sizeof(txbuf));
             
            txbuf[0] = 0x1A;
            txbuf[1] = 0x04;
            
            temp = (seg_pedo_all << 12) | (seg_pedo_done & 0xFFF);
            txbuf[2] = (temp>>16) & 0xFF;
            txbuf[3] = (temp>>8) & 0xFF;
            txbuf[4] = (temp>>0) & 0xFF;
            
        }else if ( fm.erea[FM_ID_SEG_PEDO].items == 0 )
        {
			memset( txbuf, 0, sizeof(txbuf));
            
            txbuf[0] = 0x1A;
            txbuf[1] = 0x04;
            
            temp = (seg_pedo_all << 12) | (seg_pedo_done & 0xFFF);
            txbuf[2] = (temp>>16) & 0xFF;
            txbuf[3] = (temp>>8) & 0xFF;
            txbuf[4] = (temp>>0) & 0xFF;	

			bt_protocol_tx( txbuf, sizeof(txbuf) );            
        }else{
            osal_start_timerEx ( task_id, TASK_UPLOAD_SEG_PEDO_1_EVT, 50);
        }	
		
		return ( events ^ TASK_UPLOAD_STORE_SEG_PEDO_EVT );
	}	
	
	/*************************************************************************** 
	 *                                                                         *
 	 * 加载运动数据到队列中                                                    *
	 *                                                                         *
	 **************************************************************************/
	
	if ( events & TASK_UPLOAD_STORE_RUNNING_EVT )
	{
        running_done = 0;
        running_all = fm.erea[FMC_ID_RUNNING].items;
        
        if ( fm.erea[FMC_ID_RUNNING].items > 255 )
        {
            // A fatal Error Ocurr
            // There is a fatal mistake. We are about to execute the rescue operation
            // then make a notification to app mean no data
            
            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x1B;
            txbuf[1] = 0x04;   
            
            bt_protocol_tx( txbuf, sizeof(txbuf) );			
        }else if ( fm.erea[FMC_ID_RUNNING].items == 0 ){  

            memset ( txbuf, 0, sizeof(txbuf) );

            txbuf[0] = 0x1B;
            txbuf[1] = 0x04;                
            bt_protocol_tx( txbuf, sizeof(txbuf) );	
            
        }else{
            osal_set_event ( task_id, TASK_UPLOAD_STORE_RUNNING_1_EVT );
        } 		
		
		return ( events ^ TASK_UPLOAD_STORE_RUNNING_EVT );
	}	
	
    return 0;
}

void taskUploadInit( unsigned char task_id )
{
	taskUploadTaskId = task_id;
}


#include "SkippingAlg.h"

struct accelDevice accel;
unsigned int skip_mTicks = 0;

////////////////////////////////////////////////////////////////////////////////

#define FILTER_NR    9

static int filter_arr[3][FILTER_NR];

/** 
 * func void accel_filter_init(void);
 * To init the filter array.
 */
static void accel_filter_init(void)
{
	for ( int i = 0; i < 2; i++ )
	{
		for ( int j = 0; j < FILTER_NR; j++ )
		{
			filter_arr[i][j] = 0;
		}
	}
}

static int accel_filter_( int idx, int value )
{
	int sum = 0;

	for ( int i = 0; i < FILTER_NR-1; i++ )
	{
		filter_arr[idx][i] = filter_arr[idx][i+1];
        sum += filter_arr[idx][i+1]; 
	}

	filter_arr[idx][FILTER_NR-1] = value;
    sum += value;
	
	return sum / FILTER_NR;
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

static int X[3];
int bMax_X[3];
int bMin_X[3];
int xh_flag = 0, xl_flag = 0;
int fx_max = 0;

unsigned int ProcessX( int value )
{
	int n = value;

	X[0] = X[1];
	X[1] = X[2];
	X[2] = n;

	if ( n > accel.vMax_X )
	{
		accel.vMax_X = n; accel.max_c_x = 0;
	}

	if ( n < accel.vMax_X )
	{
		accel.max_c_x++; 
		if ( (accel.max_c_x >= 2) && (xh_flag == 0) 
			&& (X[0] > X[1]) && (X[1] > X[2]) )         // find highest point
		{
			accel.max_c_x = 0;
			bMax_X[0] = bMax_X[1];
			bMax_X[1] = bMax_X[2];
			bMax_X[2] = accel.vMax_X; 
			accel.aMax[0] = (bMax_X[0]+bMax_X[1]+bMax_X[2])/3;
			accel.max_x_tick = skip_mTicks;

			xh_flag = 1; xl_flag = 0;
			accel.vMax_X = 0;

			accel.hightCnt[0]++;
		}
	}

	if ( n < accel.vMin_X )
	{
		accel.vMin_X = n; accel.min_c_x = 0;
	}

	if ( n > accel.vMin_X )
	{
		accel.min_c_x++;  
		if ( (accel.min_c_x >= 2) && (xl_flag == 0)
			&& (X[0] < X[1]) && (X[1] < X[2]))		// find lowest point
		{
			accel.min_c_x = 0;
			bMin_X[0] = bMin_X[1];
			bMin_X[1] = bMin_X[2];
			bMin_X[2] = accel.vMin_X; 
			accel.aMin[0] = (bMin_X[0]+bMin_X[1]+bMin_X[2])/3;

			xl_flag = 1; xh_flag = 0;
			accel.vMin_X = 2047;

			accel.lowCnt[0]++;
		}
	}

	{
		if ( (accel.aMax[0] > accel.aMin[0]) && !(skip_mTicks % 50))        // update The extreme array
		{
			for ( int i = 0; i < 3; i++ )
			{
				bMax_X[i] -= 1;
			}

			accel.aMax[0] = (bMax_X[0]+bMax_X[1]+bMax_X[2])/3;
		}

		if ( (accel.aMin[0] < accel.aMax[0]) && !(skip_mTicks % 50) )
		{
			for ( int i = 0; i < 3; i++ )
			{
				bMin_X[i] += 1;
			}

			accel.aMin[0] = (bMin_X[0]+bMin_X[1]+bMin_X[2])/3;
		}
	}

	{
		int diff =  accel.aMax[0] - accel.aMin[0];
		int bl = (accel.aMax[0]+accel.aMin[0])/2;

		if ( (diff > 35 ) && (n >bl ) && (fx_max == 0) )
		{
			fx_max = 1;

			if ( ( (skip_mTicks -accel.min_x_tick ) > 150) && ((skip_mTicks - accel.min_x_tick) < 2100) )
			{
				accel.c[0]++;
				accel.ic[0]++;

				int max = (accel.ic[1] > accel.ic[2])?(accel.ic[1]):(accel.ic[2]);

				if ( accel.ic[0] < max )
				{
					accel.ic[0] = max;
					accel.aCounter  = max;
				} else {
					accel.aCounter = accel.ic[0];				
				}
			}
					
			accel.min_x_tick = skip_mTicks;
		}
	}

	if ( (n < ((accel.aMin[0] + accel.aMax[0])/2 )) && (fx_max == 1 ) )
	{
		fx_max = 0;
	}
	
	return 0;
}

static int Y[3];
int bMax_Y[3];
int bMin_Y[3];
int yh_flag = 0, yl_flag = 0;
int fy_max = 0;

unsigned int ProcessY( int value )
{
	int n = value;

	Y[0] = Y[1];
	Y[1] = Y[2];
	Y[2] = n;

	if ( n > accel.vMax_Y )
	{
		accel.vMax_Y = n; accel.max_c_y = 0;
	}

	if ( n < accel.vMax_Y )
	{
		accel.max_c_y++; 
		if ( (accel.max_c_y >= 2) && (yh_flag == 0) 
			&& (Y[0] > Y[1]) && (Y[1] > Y[2]) )         // find highest point
		{
			accel.max_c_y = 0;
			bMax_Y[0] = bMax_Y[1];
			bMax_Y[1] = bMax_Y[2];
			bMax_Y[2] = accel.vMax_Y; 
			accel.aMax[1] = (bMax_Y[0]+bMax_Y[1]+bMax_Y[2])/3;
			accel.max_y_tick = skip_mTicks;

			yh_flag = 1; yl_flag = 0;
			accel.vMax_Y = 0;

			accel.hightCnt[1]++;
		}
	}

	if ( n < accel.vMin_Y )
	{
		accel.vMin_Y = n; accel.min_c_y = 0;
	}

	if ( n > accel.vMin_Y )
	{
		accel.min_c_y++;  
		if ( (accel.min_c_y >= 2) && (yl_flag == 0)
			&& (Y[0] < Y[1]) && (Y[1] < Y[2]))		// find lowest point
		{
			accel.min_c_y = 0;
			bMin_Y[0] = bMin_Y[1];
			bMin_Y[1] = bMin_Y[2];
			bMin_Y[2] = accel.vMin_Y; 
			accel.aMin[1] = (bMin_Y[0]+bMin_Y[1]+bMin_Y[2])/3;

			yl_flag = 1; yh_flag = 0;
			accel.vMin_Y = 2047;

			accel.lowCnt[1]++;
		}
	}

	{
		if ( (accel.aMax[1] > accel.aMin[1]) && !(skip_mTicks % 50) )        // update The extreme array
		{
			for ( int i = 0; i < 3; i++ )
			{
				bMax_Y[i] -= 1;
			}

			accel.aMax[1] = (bMax_Y[0]+bMax_Y[1]+bMax_Y[2])/3;
		}

		if ( (accel.aMin[1] < accel.aMax[1]) && !(skip_mTicks % 50) )
		{
			for ( int i = 0; i < 3; i++ )
			{
				bMin_Y[i] += 1;
			}

			accel.aMin[1] = (bMin_Y[0]+bMin_Y[1]+bMin_Y[2])/3;
		}
	}

	{
		int diff =  accel.aMax[1] - accel.aMin[1];
		int bl = (accel.aMax[1]+accel.aMin[1])/2;

		if ( (diff > 35 ) && (n >bl ) && (fy_max == 0) )
		{
			fy_max = 1;

			if ( ( (skip_mTicks -accel.min_y_tick ) > 150) && ((skip_mTicks - accel.min_y_tick) < 2100) )
			{
				accel.c[1]++;
				accel.ic[1]++;

				int max = (accel.ic[0] > accel.ic[2])?(accel.ic[0]):(accel.ic[2]);

				if ( accel.ic[1] < max )
				{
					accel.ic[1] = max;
					accel.aCounter  = max;
				} else {
					accel.aCounter = accel.ic[1];				
				}
			}
					
			accel.min_y_tick = skip_mTicks;
		}
	}

	if ( (n < ((accel.aMin[1] + accel.aMax[1])/2 )) && (fy_max == 1 ) )
	{
		fy_max = 0;
	}
	
	return 0;
}


static int Z[3];
int bMax_Z[3];
int bMin_Z[3];
int zh_flag = 0, zl_flag = 0;
int fz_max = 0;

unsigned int ProcessZ( int value )
{
	int n = value;

	Z[0] = Z[1];
	Z[1] = Z[2];
	Z[2] = n;

	if ( n > accel.vMax_Z )
	{
		accel.vMax_Z = n; accel.max_c_z = 0;
	}

	if ( n < accel.vMax_Z )
	{
		accel.max_c_z++; 
		if ( (accel.max_c_z >= 2) && (zh_flag == 0) 
			&& (Z[0] > Z[1]) && (Z[1] > Z[2]) )         // find highest point
		{
			accel.max_c_z = 0;
			bMax_Z[0] = bMax_Z[1];
			bMax_Z[1] = bMax_Z[2];
			bMax_Z[2] = accel.vMax_Z; 
			accel.aMax[2] = (bMax_Z[0]+bMax_Z[1]+bMax_Z[2])/3;
			accel.max_z_tick = skip_mTicks;

			zh_flag = 1; zl_flag = 0;
			accel.vMax_Z = 0;

			accel.hightCnt[2]++;
		}
	}

	if ( n < accel.vMin_Z )
	{
		accel.vMin_Z = n; accel.min_c_z = 0;
	}

	if ( n > accel.vMin_Z )
	{
		accel.min_c_z++;  
		if ( (accel.min_c_z >= 2) && (zl_flag == 0)
			&& (Z[0] < Z[1]) && (Z[1] < Z[2]))		// find lowest point
		{
			accel.min_c_z = 0;
			bMin_Z[0] = bMin_Z[2];
			bMin_Z[1] = bMin_Z[2];
			bMin_Z[2] = accel.vMin_Z; 
			accel.aMin[2] = (bMin_Z[0]+bMin_Z[1]+bMin_Z[2])/3;

			zl_flag = 1; zh_flag = 0;
			accel.vMin_Z = 2047;

			accel.lowCnt[2]++;
		}
	}

	{
		if ( (accel.aMax[2] > accel.aMin[2]) && !(skip_mTicks % 50) )        // update The extreme array
		{
			for ( int i = 0; i < 3; i++ )
			{
				bMax_Z[i] -= 1;
			}

			accel.aMax[2] = (bMax_Z[0]+bMax_Z[1]+bMax_Z[2])/3;
		}

		if ( (accel.aMin[2] < accel.aMax[2]) && !(skip_mTicks % 50) )
		{
			for ( int i = 0; i < 3; i++ )
			{
				bMin_Z[i] += 1;
			}

			accel.aMin[2] = (bMin_Z[0]+bMin_Z[1]+bMin_Z[2])/3;
		}
	}

	{
		int diff =  accel.aMax[2] - accel.aMin[2];
		int bl = (accel.aMax[2]+accel.aMin[2])/2;

		if ( (diff > 35 ) && (n >bl ) && (fz_max == 0) )
		{
			fz_max = 1;

			if ( ( (skip_mTicks -accel.min_z_tick ) > 150) && ((skip_mTicks - accel.min_z_tick) < 2100) )
			{
				accel.c[2]++;
				accel.ic[2]++;

				int max = (accel.ic[0] > accel.ic[1])?(accel.ic[0]):(accel.ic[1]);

				if ( accel.ic[2] < max )
				{
					accel.ic[2] = max;
					accel.aCounter  = max;
				} else {
					accel.aCounter = accel.ic[2];				
				}
			}
					
			accel.min_z_tick = skip_mTicks;
		}
	}

	if ( (n < ((accel.aMin[2] + accel.aMax[2])/2 )) && (fz_max == 1 ) )
	{
		fz_max = 0;
	}
	
	return 0;
}

#if 0
static int LV[3];
static int LT[3];
static float kl[3];

float get_k(int idx, int v)
{
	float k = (float)(v-LV[idx])/(skip_mTicks-LT[idx]);

	float k2 = (k-kl[idx])/(skip_mTicks-LT[idx]);

	LV[idx] = v;
	LT[idx] = skip_mTicks;

	return k;
}
#endif

void Alogrithm_Cal(int x, int y, int z)
{
    ProcessX(x);
    ProcessY(y);
    ProcessZ(z); 
}

unsigned int stepFlagmTicks_1 = 0;
unsigned int stepFlagmTicks_2 = 0;
unsigned char clear_flag = 0;

void Alogrithm_Do_Process(int x, int y, int z)
{
	if ( accel.step_Machine == STEP_MACHINE_WAIT )
	{
		// 状态机为0：检测步数是否 >= 5
		if ( accel.aCounter - accel.lCounter >= 5 )
		{
			// 状态机切换到1
			accel.step_Machine = STEP_MACHINE_PROC;
			stepFlagmTicks_2 = skip_mTicks;
		}else
		if ( accel.temp_counter != accel.aCounter )
		{
			// 步数小于5,但不等于上次记录的值
			// 更新临时变量,记录T1
			accel.temp_counter = accel.aCounter;
			stepFlagmTicks_1 = skip_mTicks;
		}
	}else{
		// 状态机为1：步数不等于上次的值
		if ( accel.lCounter != accel.aCounter )
		{
			// 更新步数,记录时间T2
			accel.lCounter = accel.aCounter;	
			stepFlagmTicks_2 = skip_mTicks;
		}
	}

	if ( accel.step_Machine == STEP_MACHINE_WAIT )
	{
		if ( (skip_mTicks - stepFlagmTicks_1) > 2200 )
		{
			clear_flag = 0x1;
		}
	}else{
		if ( (skip_mTicks - stepFlagmTicks_2) > 2200 )
		{
			clear_flag = 0x1;
		}
	}

	if (  clear_flag & 0x1 )
	{
		// T1 大于2.2秒,无效，临时累计的步数需要消除
		// T2 大于2.2秒,无效，临时累计的步数需要消除
		int temp_counter =  accel.lCounter;
		accel.aCounter = temp_counter;
		
		for ( int i = 0; i < 3; i++ )
		{
			accel.c[i]  = temp_counter;
			accel.ic[i] = temp_counter;
		}
		// 状态机回0
		accel.step_Machine = STEP_MACHINE_WAIT;
		stepFlagmTicks_1 = stepFlagmTicks_2 = skip_mTicks;
		
		clear_flag = 0x0;
	}
}

void Alogrithm_Process( int x, int y, int z)
{   
	/** 滤波处理 */

	x = accel_filter_(0, x);
	y = accel_filter_(1, y);
	z = accel_filter_(2, z);

	/** 算法处理 */
	Alogrithm_Cal(x, y, z);

	/** 状态处理 */
	Alogrithm_Do_Process(x,y,z);

	/** 更新时基计数器 */
    skip_mTicks += 25;

	/** 计算一阶导数和二阶导数 */
	#if 0
	accel.k[0] = get_k(0,x);
	accel.k[1] = get_k(1,y);
	accel.k[2] = get_k(2,z);
	#endif
}

#include <string.h>

void Alogrithm_Init(void)
{
	/** 算法初始化 */
	memset(&accel, 0, sizeof(accel));

	accel_filter_init();

	accel.vMin_X		= 2047;

	for ( int i = 0; i < 3; i++ )
	{
		bMin_X[i]		= 2047;
		accel.aMin[i]	= 2047;
	}

	accel.step_Machine = STEP_MACHINE_WAIT;
}

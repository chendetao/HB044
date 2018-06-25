#ifndef __SKIPP_ALG__
#define __SKIPP_ALG__

typedef enum
{
	STEP_MACHINE_WAIT = 1,
	STEP_MACHINE_PROC = 2,
}StepMachine;

struct accelDevice
{
	int MaxThreshold[3], MinThreshold[3], MidleThreshold[3];
	int hightCnt[3], lowCnt[3];
	int Counter[3], iCounter[3]/*, toMidleLines[3]*/;
	int aCounter, lCounter, temp_counter;
	StepMachine step_Machine;
	int WaveCounter, WaveAmplitudeSum;
	int d4_MaxMin_x,d4_MaxMin_y,d4_MaxMin_z;

	int vMax_X;
	int vMin_X;
	int aMax[3];
	int aMin[3];
	int max_c_x;
	int min_c_x;
	int max_x_tick,min_x_tick;

	int vMax_Y;
	int vMin_Y;
	int max_c_y;
	int min_c_y;
	int max_y_tick,min_y_tick;

	int vMax_Z;
	int vMin_Z;
	int max_c_z;
	int min_c_z;
	int max_z_tick,min_z_tick;
};

extern struct accelDevice accel;

extern void Alogrithm_Process( int x, int y, int z);
extern void Alogrithm_Init(void);

#endif

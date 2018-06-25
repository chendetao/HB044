
#ifndef __STEP_PROCESS_H__
#define __STEP_PROCESS_H__

struct AccelDevice
{
	int MaxThreshold[3], MinThreshold[3], MidleThreshold[3];
	//int32 hightCnt[3], lowCnt[3];
	int Counter[3], iCounter[3]/*, toMidleLines[3]*/;
	int allCounter, oCounter;
	int WaveCounter, WaveAmplitudeSum;
};

typedef enum
{
	ALGORITHM_PEDOMETER = 0,
	ALGORITHM_SPORT     = 1,
}Algorithm_mode;

#define ALGORITHM_THRESHOLD_MAX     		 50
#define ALGORITHM_THRESHOLD_DEFAULT  		 35

extern struct AccelDevice accelDevice;

extern void AccelHandle(void);

extern int step_algorithm_mode_set( Algorithm_mode mode );

#endif


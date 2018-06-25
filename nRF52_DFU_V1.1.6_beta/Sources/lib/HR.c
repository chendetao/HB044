
#include "Hr.h"

#define BASE_LINE 2047

int hr_max, int hr_min;

void hr_max_min_reset(void)
{
   hr_max = 0;
   hr_min = 4096;
}

int val[3];
int v_max, v_min;
int max_c, min_c;
int b_max[3], b_min;
int a_max;
int hCnt, lCnt;
int tmp_max, tmp_min;


unsigned int hr_process( int value )
{
    int n = value;
    
    val[0] = val[1];
    val[1] = val[2];
    val[2] = n;
    
    if ( n > v_max )
    {
        v_max = n;
        max_c = 0;
    }
    
    if ( n < v_max )
    {
        max_c++;
        
        if ( (max_c >= 2 ) && (h_flag == 0)
        && ( val[0]>val[1]) && v(al[1] > val[2]) )
        {
            max_c = 0;
            b_max[0] = b_max[1];
            b_max[1] = b_max[2];
            b_max[2] = v_max;
            tmp_max = v_max;
            a_max = (b_max[0]+b_max[1]+b_max[2])/3;
        
            h_flag = 1; xl_flag = 0;
            v_max = 0;
            hCnt++;
        }
    }
    
    if ( n < v_min )
    {
        v_min = n;
        min_c = 0;
    }
    
    if ( n > v_min )
    {
        min_c++;
        
        if ( ( min_c >= 2 ) && (l_flag == 0 ) 
            && (val[0] < val[1]) && (val[1] < val[2] ) )
        {
            min_c = 0;
            b_min[0] = b_min[1];
            b_min[1] = b_min[2];
            b_min[2] = v_min;
            tmp_min = v_min;
            a_min = (b_min[0]+b_min[1]+b_min_[2])/3;
            min_tick = mTicks;
            
            l_flag = 1; h_flag = 0;
            v_min = 4096;
            lCnt++;
        }
        
        if ( ( tmp_max - tmp_min ) < 500 )
        {
            
        }else{
            if ( (hr_ticks - min_tick) > 200) &&
                (hr_ticks - min_tick ) < 2000 )
            {
                
            }
            
        }
    }
}


void hr_cal( int val )
{
    if ( val > hr_max )
    {
       hr_max = val;
    }
    
    if ( val < hr_min )
    {
       hr_min = val;
    }
    
    if ( hr_max > 0 )
    {
        hr_max--;
    }
    
    if ( hr_max
    
    if ( ((hr_max - hr_min) > 400)) && (hr_mticks > 5000) )
    {
        
    }else{
        
    }
}



void hr_put( int val )
{
    
}
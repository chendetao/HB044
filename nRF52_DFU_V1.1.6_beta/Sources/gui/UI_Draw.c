#include "UI_Draw.h"
#include "math.h"
#include "ClockTick.h"

#define PI  3.1415926

void draw_bitmap(int fx, int fy, int width, int height, const unsigned char *bitmap )
{
	const unsigned short *p = (unsigned short *)bitmap;
	unsigned short rgb;
	
	for( int y = fy; y < (fy + height); y++ )
	{
		for ( int x = fx; x < ( fx + width); x++, p++ )
		{
			if ( x < LCD_W && y < LCD_H )  {
				rgb = *p; 
				fb[y][x] = rgb;
			}
		}
	}
}

void draw_bitmap_meger(int fx, int fy, int width, int height, const unsigned char *bitmap )
{
	const unsigned short *p = (unsigned short *)bitmap;
	unsigned short rgb;
	
	for( int y = fy; y < (fy + height); y++ )
	{
		for ( int x = fx; x < ( fx + width); x++, p++ )
		{
			if ( x < LCD_W && y < LCD_H )  {
				rgb = *p; 
				if ( !fb[y][x] )
				{
					fb[y][x] = rgb;
				}
			}
		}
	}
}

void draw_fill(int fx, int fy, int width, int height, unsigned short val)
{
	for( int y = fy; y < (fy + height); y++ )
	{
		for (  int x = fx; x < ( fx + width); x++ )
		{
			if ( x < LCD_W && y < LCD_H )  {
				fb[y][x] = val;
			}
		}
	}
}

void UI_Draw_Vline( int fx, int fy, int width, int height, int color)
{
	for( int y = fy; y < (fy + height); y++ )
	{
		for (  int x = fx; x < ( fx + width); x++ )
		{
			if ( x < LCD_W && y < LCD_H )
			 fb[y][x] = color;
		}
	}
}

/*
 * 画一条直线
 */
void draw_line(int x1, int y1, int x2, int y2, unsigned short color)
{
    int dx, dy, e;
    dx = x2 - x1;
    dy = y2 - y1;

    if (dx >= 0)
    {
        if (dy >= 0) // dy>=0
        {
            if (dx >= dy) // 1/8 octant
            {
                e = dy - (dx >> 1);
                while (x1 <= x2)
                {
                    setpixel(x1, y1, color);

                    if (e > 0)
                    {y1 += 1; e -= dx;}
                    x1 += 1;
                    e += dy;
                }
            }
            else        // 2/8 octant
            {
                e = dx - (dy >> 1);
                while (y1 <= y2)
                {
                    setpixel(x1, y1, color);
                    if (e > 0)
                    {x1 += 1; e -= dy;}
                    y1 += 1;
                    e += dx;
                }
            }
        }
        else           // dy<0
        {
            dy = -dy;   // dy=abs(dy)

            if (dx >= dy) // 8/8 octant
            {
                e = dy - (dx >> 1);
                while (x1 <= x2)
                {
                    setpixel(x1, y1, color);
                    
                    if (e > 0)
                    {y1 -= 1; e -= dx;}
                    x1 += 1;
                    e += dy;
                }
            }
            else        // 7/8 octant
            {
                e = dx - (dy >> 1);
                while (y1 >= y2)
                {
                    setpixel(x1, y1, color);
                    if (e > 0)
                    {x1 += 1; e -= dy;}
                    y1 -= 1;
                    e += dx;
                }
            }
        }
    }
    else //dx<0
    {
        dx = -dx;     //dx=abs(dx)
        if (dy >= 0) // dy>=0
        {
            if (dx >= dy) // 4/8 octant
            {
                e = dy - (dx >> 1);
                while (x1 >= x2)
                {
                    setpixel(x1, y1, color);
                    if (e > 0)
                    {y1 += 1; e -= dx;}
                    x1 -= 1;
                    e += dy;
                }
            }
            else        // 3/8 octant
            {
                e = dx - (dy >> 1);
                while (y1 <= y2)
                {
                    setpixel(x1, y1, color);
                    if (e > 0)
                    {x1 -= 1; e -= dy;}
                    y1 += 1;
                    e += dx;
                }
            }
        }
        else           // dy<0
        {
            dy = -dy;   // dy=abs(dy)

            if (dx >= dy) // 5/8 octant
            {
                e = dy - (dx >> 1);
                while (x1 >= x2)
                {
                    setpixel(x1, y1, color); 
                    if (e > 0)
                    {y1 -= 1; e -= dx;}
                    x1 -= 1;
                    e += dy;
                }
            }
            else        // 6/8 octant
            {
                e = dx - (dy >> 1);
                while (y1 >= y2)
                {
                    setpixel(x1, y1, color); 
                    if (e > 0)
                    {x1 -= 1; e -= dy;}
                    y1 -= 1;
                    e += dx;
                }
            }
        }
    }
}


/****************************************************************************
* 名称：GUI_Point()
* 功能：在指定位置上画点。
* 入口参数：x		指定点所在列的位置
*          y		指定点所在行的位置
*          color	显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：返回值为1时表示操作成功，为0时表示操作失败。(操作失败原因是指定地址超出有
*           效范围)
* 说明：
*  
* 
****************************************************************************/
int  GUI_Point(int x, int y, int color)
{
   /* 参数过滤 */
   if(x >= LCD_W) return(0);
   if(y >= LCD_H) return(0);
   
	setpixel( x, y, color );
   return(1);
}



/****************************************************************************
* 名称：GUI_HLine()
* 功能：画水平线。
* 入口参数： x0		水平线起点所在列的位置
*            y0		水平线起点所在行的位置
*            x1     水平线终点所在列的位置
*            color	显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：无
* 说明：
****************************************************************************/
void  GUI_HLine(int x0, int y0, int x1, int color) 
{  
   int  bak;
   if(x0>x1) 						// 对x0、x1大小进行排列，以便画图
   {  
	  bak = x1;
      x1 = x0;
      x0 = bak;
   }   
   do
   { 
      GUI_Point(x0,y0,color);
      x0++;
   }while(x1>=x0);
}


/****************************************************************************
* 名称：GUI_RLine()
* 功能：画垂直线。
* 入口参数： x0		垂直线起点所在列的位置
*           y0		垂直线起点所在行的位置
*           y1      垂直线终点所在行的位置
*           color	显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：无
* 说明：
****************************************************************************/
void  GUI_RLine(int x0, int y0, int y1, int color) 
{
   int  bak;
   if(y0>y1) 						// 对y0、y1大小进行排列，以便画图
   {  
	  bak = y1;
      y1 = y0;
      y0 = bak;
   }
   do
   {  
	  GUI_Point(x0, y0, color);		// 逐点显示，描出垂直线
      y0++;
   }while(y1>=y0);	
}




/****************************************************************************
* 名称：GUI_LineWith()
* 功能：画任意两点之间的直线，并且可设置线的宽度。
* 入口参数： x0		直线起点的x坐标值
*           y0		直线起点的y坐标值
*           x1      直线终点的x坐标值
*           y1      直线终点的y坐标值
*           with    线宽(0-50)
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/

void  GUI_LineWith(int x0, int y0, int x1, int y1, int with, unsigned short color)
{  int   dx;						// 直线x轴差值变量
   int   dy;          			// 直线y轴差值变量
   int    dx_sym;					// x轴增长方向，为-1时减值方向，为1时增值方向
   int    dy_sym;					// y轴增长方向，为-1时减值方向，为1时增值方向
   int   dx_x2;					// dx*2值变量，用于加快运算速度
   int   dy_x2;					// dy*2值变量，用于加快运算速度
   int   di;						// 决策变量
   
   int   wx, wy;					// 线宽变量
   int   draw_a, draw_b;
   
   /* 参数过滤 */
   if(with==0) return;
   if(with>50) with = 50;
   
   dx = x1-x0;						// 求取两点之间的差值
   dy = y1-y0;
   
   wx = with/2;
   wy = with-wx-1;
   
   /* 判断增长方向，或是否为水平线、垂直线、点 */
   if(dx>0)							// 判断x轴方向
   {  dx_sym = 1;					// dx>0，设置dx_sym=1
   }
   else
   {  if(dx<0)
      {  dx_sym = -1;				// dx<0，设置dx_sym=-1
      }
      else
      {  /* dx==0，画垂直线，或一点 */
         wx = x0-wx;
         if(wx<0) wx = 0;
         wy = x0+wy;
         
         while(1)
         {  x0 = wx;
            GUI_RLine(x0, y0, y1, color);
            if(wx>=wy) break;
            wx++;
         }
         
      	 return;
      }
   }
   
   if(dy>0)							// 判断y轴方向
   {  dy_sym = 1;					// dy>0，设置dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0，设置dy_sym=-1
      }
      else
      {  /* dy==0，画水平线，或一点 */
         wx = y0-wx;
         if(wx<0) wx = 0;
         wy = y0+wy;
         
         while(1)
         {  y0 = wx;
            GUI_HLine(x0, y0, x1, color);
            if(wx>=wy) break;
            wx++;
         }
      	 return;
      }
   }
    
   /* 将dx、dy取绝对值 */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* 计算2倍的dx及dy值 */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* 使用Bresenham法进行画直线 */
   if(dx>=dy)						// 对于dx>=dy，则使用x轴为基准
   {  di = dy_x2 - dx;
      while(x0!=x1)
      {  /* x轴向增长，则宽度在y方向，即画垂直线 */
         draw_a = y0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = y0+wy;
         GUI_RLine(x0, draw_a, draw_b, color);
         
         x0 += dx_sym;				
         if(di<0)
         {  di += dy_x2;			// 计算出下一步的决策值
         }
         else
         {  di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      draw_a = y0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = y0+wy;
      GUI_RLine(x0, draw_a, draw_b, color);
   }
   else								// 对于dx<dy，则使用y轴为基准
   {  di = dx_x2 - dy;
      while(y0!=y1)
      {  /* y轴向增长，则宽度在x方向，即画水平线 */
         draw_a = x0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = x0+wy;
         GUI_HLine(draw_a, y0, draw_b, color);
         
         y0 += dy_sym;
         if(di<0)
         {  di += dx_x2;
         }
         else
         {  di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      draw_a = x0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = x0+wy;
      GUI_HLine(draw_a, y0, draw_b, color);
   } 
  
}

/****************************************************************************
* 名称：GUI_CircleFill()
* 功能：指定圆心位置及半径，画圆并填充，填充色与边框色一样。
* 入口参数： x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r       圆的半径
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_CircleFill(int x0, int y0, int r, unsigned short color)
{  int  draw_x0, draw_y0;			// 刽图点坐标变量
   int  draw_x1, draw_y1;	
   int  draw_x2, draw_y2;	
   int  draw_x3, draw_y3;	
   int  draw_x4, draw_y4;	
   int  draw_x5, draw_y5;	
   int  draw_x6, draw_y6;	
   int  draw_x7, draw_y7;	
   int  fill_x0, fill_y0;			// 填充所需的变量，使用垂直线填充
   int  fill_x1;
   int  xx, yy;					// 画圆控制变量
 
   int  di;						// 决策变量
   
   /* 参数过滤 */
   if(0==r) return;
   
   /* 计算出4个特殊点(0、90、180、270度)，进行显示 */
   draw_x0 = draw_x1 = x0;
   draw_y0 = draw_y1 = y0 + r;
   if(draw_y0<LCD_H)
   {  GUI_Point(draw_x0, draw_y0, color);	// 90度
   }
    	
   draw_x2 = draw_x3 = x0;
   draw_y2 = draw_y3 = y0 - r;
   if(draw_y2>=0)
   {  GUI_Point(draw_x2, draw_y2, color);	// 270度
   }
  	
   draw_x4 = draw_x6 = x0 + r;
   draw_y4 = draw_y6 = y0;
   if(draw_x4<LCD_W) 
   {  GUI_Point(draw_x4, draw_y4, color);	// 0度
      fill_x1 = draw_x4;
   }
   else
   {  fill_x1 = LCD_W;
   }
   fill_y0 = y0;							// 设置填充线条起始点fill_x0
   fill_x0 = x0 - r;						// 设置填充线条结束点fill_y1
   if(fill_x0<0) fill_x0 = 0;
   GUI_HLine(fill_x0, fill_y0, fill_x1, color);
   
   draw_x5 = draw_x7 = x0 - r;
   draw_y5 = draw_y7 = y0;
   if(draw_x5>=0) 
   {  GUI_Point(draw_x5, draw_y5, color);	// 180度
   }
   if(1==r) return;
   
   
   /* 使用Bresenham法进行画圆 */
   di = 3 - 2*r;							// 初始化决策变量
   
   xx = 0;
   yy = r;
   while(xx<yy)
   {  if(di<0)
	  {  di += 4*xx + 6;
	  }
	  else
	  {  di += 4*(xx - yy) + 10;
	  
	     yy--;	  
		 draw_y0--;
		 draw_y1--;
		 draw_y2++;
		 draw_y3++;
		 draw_x4--;
		 draw_x5++;
		 draw_x6--;
		 draw_x7++;		 
	  }
	  
	  xx++;   
	  draw_x0++;
	  draw_x1--;
	  draw_x2++;
	  draw_x3--;
	  draw_y4++;
	  draw_y5++;
	  draw_y6--;
	  draw_y7--;
		
	
	  /* 要判断当前点是否在有效范围内 */
	  if( (draw_x0<=LCD_W)&&(draw_y0>=0) )	
	  {  GUI_Point(draw_x0, draw_y0, color);
	  }	    
	  if( (draw_x1>=0)&&(draw_y1>=0) )	
	  {  GUI_Point(draw_x1, draw_y1, color);
	  }
	  
	  /* 第二点水直线填充(下半圆的点) */
	  if(draw_x1>=0)
	  {  /* 设置填充线条起始点fill_x0 */
	     fill_x0 = draw_x1;
	     /* 设置填充线条起始点fill_y0 */
	     fill_y0 = draw_y1;
         if(fill_y0>LCD_H) fill_y0 = LCD_H;
         if(fill_y0<0) fill_y0 = 0; 
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x1;				
         if(fill_x1>LCD_W) fill_x1 = LCD_W;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }
	  
	  
	  if( (draw_x2<=LCD_W)&&(draw_y2<=LCD_H) )	
	  {  GUI_Point(draw_x2, draw_y2, color);   
	  }
	    	  
	  if( (draw_x3>=0)&&(draw_y3<=LCD_H) )	
	  {  GUI_Point(draw_x3, draw_y3, color);
	  }
	  
	  /* 第四点垂直线填充(上半圆的点) */
	  if(draw_x3>=0)
	  {  /* 设置填充线条起始点fill_x0 */
	     fill_x0 = draw_x3;
	     /* 设置填充线条起始点fill_y0 */
	     fill_y0 = draw_y3;
         if(fill_y0>LCD_H) fill_y0 = LCD_H;
         if(fill_y0<0) fill_y0 = 0;
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x3;				
         if(fill_x1>LCD_W) fill_x1 = LCD_W;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }
	  
	  	  
	  if( (draw_x4<=LCD_W)&&(draw_y4>=0) )	
	  {  GUI_Point(draw_x4, draw_y4, color);
	  }
	  if( (draw_x5>=0)&&(draw_y5>=0) )	
	  {  GUI_Point(draw_x5, draw_y5, color);
	  }
	  
	  /* 第六点垂直线填充(上半圆的点) */
	  if(draw_x5>=0)
	  {  /* 设置填充线条起始点fill_x0 */
	     fill_x0 = draw_x5;
	     /* 设置填充线条起始点fill_y0 */
	     fill_y0 = draw_y5;
         if(fill_y0>LCD_H) fill_y0 = LCD_H;
         if(fill_y0<0) fill_y0 = 0;
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x5;				
         if(fill_x1>LCD_W) fill_x1 = LCD_W;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }
	  
	  
	  if( (draw_x6<=LCD_W)&&(draw_y6<=LCD_H) )	
	  {  GUI_Point(draw_x6, draw_y6, color);
	  }
	  
	  if( (draw_x7>=0)&&(draw_y7<=LCD_H) )	
	  {  GUI_Point(draw_x7, draw_y7, color);
	  }
	  
	  /* 第八点垂直线填充(上半圆的点) */
	  if(draw_x7>=0)
	  {  /* 设置填充线条起始点fill_x0 */
	     fill_x0 = draw_x7;
	     /* 设置填充线条起始点fill_y0 */
	     fill_y0 = draw_y7;
         if(fill_y0>LCD_H) fill_y0 = LCD_H;
         if(fill_y0<0) fill_y0 = 0;
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x7;				
         if(fill_x1>LCD_W) fill_x1 = LCD_W;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }
	  
   }
}

/*
function: calculate the termination point of the hand 计算指针的终止坐标
param 	:x0  y0  the start point 起始坐标 
		 *x1 *y1 termination point 终止坐标的指针
		 position   指针走到了哪个位置，按照分钟计算 
		 length 针的长度
*/
void Calc_Destination( int x0, int y0, int *x1, int *y1, int position, float length)
{
	if ( position < 0 || position > 60 )
		return ;
	
	float hand_position = (float)position / (float)60;
	
	if( hand_position > (-0.001f) && hand_position < (0.001f) )  //12点
	{
		*x1 = x0;
		*y1 = y0 - (int)length;
	}
	else
	{
		*x1 = x0 + (int)(length * sin((2 * PI) * hand_position) + 0.5f);
		*y1 = y0 - (int)(length * cos((2 * PI) * hand_position) + 0.5f);
	}
	
	if(*x1<0)*x1=0;
	if(*y1<0)*y1=0;
}

void UI_style(int x0, int y0, int hour_len, int min_len, int sec_len)
{
	//表盘 时针
	{
		int hour_x1 = 0,hour_y1 = 0;
		
		unsigned char hour_position = 0;
//		unsigned char hour_position1 = 0;

		unsigned char hour = TimerHH();
		
		hour -= (hour >= 12)? (12) : (0);

		hour_position = hour * 5 + (TimerMI() / 12);
//		hour_position1 = hour_position + 30;
		
//		hour_position1 -= (hour_position1 >= 60)? (60) : (0);

		Calc_Destination( x0, y0, &hour_x1, &hour_y1, hour_position, hour_len );
		GUI_LineWith(x0,y0,hour_x1,hour_y1,5,0xFFFF);
	}
	
	//分针
	{
		int min_x1 = 0,min_y1 = 0;
//		int min_x2 = 0,min_y2 = 0;
		
		unsigned char minute = TimerMI();
//		unsigned char minute1 = minute +30;
		
//		if(minute1 >=60)
//		{
//			minute1 -= 60;
//		}
		
		Calc_Destination( x0, y0, &min_x1, &min_y1, minute, min_len );
		GUI_LineWith(x0,y0,min_x1,min_y1,3,0xFFFF);
	}
	
	//秒针
	{
		int sec_x1 = 0,sec_y1 = 0;
		
		unsigned char seconds = TimerSE();
//		unsigned char seconds1 = seconds +30;
		
//		if(seconds1 >60)
//		{
//			seconds1 -= 60;
//		}

		Calc_Destination( x0, y0, &sec_x1, &sec_y1, seconds, sec_len );
		GUI_LineWith(x0,y0,sec_x1,sec_y1,1,0xFFFF);
	}
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  void DrawUI_Bitmap( int x, int y, int w, int h, \                         //
//	const unsigned char *bitmap,unsigned long F, unsigned long B)             //
//  x,y start coordinate                                                      //
//  w,h Bitmap width and height                                               //
//  bitmap Bitmap data pointer                                                //
//  该函数用于绘制单色位图, xy为起始坐标,wh为宽度和高度                       //
//  bitmap为图片数据指针,FB为图片数据中01对应的颜色.                          //
//  需要注意的是, 图片的高度必须设置为8的整数倍                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void DrawUI_Bitmap( int x, int y, int w, int h, \
	const unsigned char *bitmap,unsigned long F, unsigned long B)
{   
	unsigned long temp;
	
	if ( h % 8 ){ // 错误的宽度
		return;
	}
	
	for ( int k = 0; k < w; k++ )
	for ( int i = 0; i < h/8; i++ )
	{
		temp = bitmap[(h/8)*k+i];
	
		for ( int j = 0; j < 8; j++ )
		{
			if ( (temp>>j) & 0x1)
			{
				setpixel(x+k, i*8+y+j, F);
			}
			else
			{
				setpixel(x+k, i*8+y+j, B);
			}
		}	
	}
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  void DrawUI_Bitmap( int x, int y, int w, int h, \                         //
//	const unsigned char *bitmap,unsigned long F, unsigned long B)             //
//  x,y start coordinate                                                      //
//  w,h Bitmap width and height                                               //
//  bitmap Bitmap data pointer                                                //
//  该函数用于绘制单色位图, xy为起始坐标,wh为宽度和高度                       //
//  bitmap为图片数据指针,FB为图片数据中01对应的颜色.                          //
//  需要注意的是, 图片的高度必须设置为8的整数倍                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void DrawUI_Bitmap_Ex( int x, int y, int w, int h, \
	const unsigned char *bitmap,unsigned long F)
{   
	unsigned long temp;
	
	if ( h % 8 ){ // 错误的宽度
		return;
	}
	
	for ( int k = 0; k < w; k++ )
	for ( int i = 0; i < h/8; i++ )
	{
		temp = bitmap[(h/8)*k+i];
	
		for ( int j = 0; j < 8; j++ )
		{
			if ( (temp>>j) & 0x1)
			{
				setpixel(x+k, i*8+y+j, F);
			}
		}	
	}
}

void DrawUI_Bitmap_Rever( int x, int y, int w, int h, \
	const unsigned char *bitmap,unsigned long F)
{   
	unsigned long temp;
	
	if ( h % 8 ){ // 错误的宽度
		return;
	}
	
	for ( int k = 0; k < w; k++ )
	for ( int i = 0; i < h/8; i++ )
	{
		temp = bitmap[(h/8)*k+i];
	
		for ( int j = 0; j < 8; j++ )
		{
			if ( !((temp>>j) & 0x1) )
			{
				setpixel(x+k, i*8+y+j, F);
			}
		}	
	}
}

void DrawUI_Bitmap_Exx( int x, int y, int w, int h,\
	const unsigned char *bitmap, unsigned short F )
{
	unsigned  char temp = 0;
	int i = 0;
	for ( int k = 0; k < w; k++ ) //宽
	{
		for ( i = 0; i < h / 8; i++ ) //高
		{
			temp = *bitmap;
			for( unsigned char j=0; j < 8; j++ )
			{
				if( (temp >> j)	& 0x1 )
					setpixel(x+k, y+i*8+j, F);
			}
			bitmap++;
		}
		
		if( h % 8 != 0 )
		{
			temp = *bitmap;
			for( unsigned char m = 0; m < (h % 8); m++ )
			{
				if ( (temp >> m) & 0x1 )
				{
					setpixel(x+k, y+i*8+m, F);
				}
			}
			bitmap++;
		}
	}
}

void set_pixel( int x, int y, int color )
{
    setpixel(x,y,color);
}


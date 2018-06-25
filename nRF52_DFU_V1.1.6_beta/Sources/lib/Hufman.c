#include "Hufman.h"

extern unsigned char *get_position(int x, int y);

/**
 * void HufmanDecoding(HufTree *HT, const char *c_code )
 * @HT 霍夫曼树
 * @p_code 存放解码字符串的缓冲区
 * @c_code 待解码字符串
 */
void Hufman_Decoding(HufTree HT, int n, const unsigned char *c_code, int code_len, int x,int y,int w, int h )
{
	int d_cnt = 0;
	unsigned char temp_c, d_c;

	HufTree t = HT+2*n-1;                       	/* 从根节点开始 */

	int dec_w = 0;
	unsigned char *p_code;
	p_code = get_position(x,y);
	
	while( d_cnt < code_len )
	{
		temp_c = *c_code++;

		for ( int i = 0; i < 8; i++ )
		{
			if ( !(temp_c & 0x80) && t->lchild )		/* 左子树 */
			{
				t = HT+t->lchild;
			}else if ( (temp_c & 0x80) && t->rchild ){	/*右子树 */
				t = HT+t->rchild;
			}

			if ( !t->lchild && !t->rchild )				/* 到达叶子节点 */
			{
				/**
				 * 子树下标-1就是该霍夫曼编码对应的原始编码(0-255)
				 */
				if ( !(temp_c & 0x80) )
				{
					d_c = (HT+t->parent)->lchild - 1;
				}else{
					d_c = (HT+t->parent)->rchild - 1;
				}

				/**
				 * 解码字节存储到p_code后，从根节点继续下一个解码
				 */
				*p_code = d_c;
				p_code++; t = HT+2*n-1;
				d_cnt++; dec_w ++;
				if ( dec_w >= w*2 )
				{
					p_code = get_position(x,++y);
					dec_w = 0;
				}
			}

			temp_c <<= 1;
		}
	}
}

HufNode tree[512];

int Hufman_Test_Decoding(const unsigned char *p_s, int x, int y, int w, int h)
{
	// step 1 打开压缩文件 读取霍夫曼树和文件大小
	
	HufTree HT;
	int n = 256;
	int m = 2*n-1;

	HT = tree;

	HT[0].parent = 0; HT[m].parent = 0;

	// make hufman tree from file

	for ( int i = 0; i <= n; i++ )
	{
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}

	const unsigned char *p = p_s;
	unsigned short temp;
	
	for ( int i = n+1; i <= m; i++ )
	{
		temp = *(p+1)<<8 | (*p);
		HT[i].lchild = temp;
		HT[temp].parent = i;
		p += 2;
		temp = *(p+1)<<8 | *p;
		HT[i].rchild = temp;
		HT[temp].parent = i;
		p += 2;
	}

	int orgin_size = 0;
	
	orgin_size = (*p<<0) | (*(p+1)<<8) | (*(p+2)<<16) | (*(p+3)<<24);

	p += 4;

	Hufman_Decoding( HT, n, p, orgin_size, x,y, w, h);

	return 0;
}


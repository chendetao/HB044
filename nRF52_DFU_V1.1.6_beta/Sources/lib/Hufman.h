/*
 * Hufman.h
 *
 *  Created on: 2018年1月19日
 *      Author: Think
 */

#ifndef HUFMAN_H_
#define HUFMAN_H_

typedef struct{
	unsigned short parent, lchild, rchild;
}HufNode, *HufTree;

typedef char **HufmanCode;

extern void PrintHufmanCode( HufmanCode C, int *s, int n );
extern void Hufman_make_tree(HufTree *HT, HufmanCode *HC, int *w, int n);
extern void StrCopy( char *str, const char *c );
extern void Select(HufTree T, int n, int *l, int *r );
extern int getHufmanSize( HufmanCode C, int *s, int n );
extern int Hufman_Encoding(HufTree HT, HufmanCode hc,
		const unsigned char *s, int length, unsigned char *buf);
extern void Hufman_Decoding(HufTree HT, int n,
		const unsigned char *c_code, int code_len,int x,int y, int w, int h);

extern int Hufman_Test_Decoding(const unsigned char *p_s, int x,int y,int w, int h);

#if defined DEBUG_ENABLE
#define DEBUG_CODE(x){x}
#else
#define DEBUG_CODE(x)
#endif

#endif /* HUFMAN_H_ */

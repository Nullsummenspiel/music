#ifndef __MUSIC_H
#define __MUSIC_H	 
#include "sys.h"

extern unsigned char musicflag;
extern unsigned char flag;
extern unsigned char lasttune;
extern unsigned char m,n;

void Music_Task(unsigned char x);
void music_run(unsigned char flag);
void Music_Init(void);
		 				    
#endif

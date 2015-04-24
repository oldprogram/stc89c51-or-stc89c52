//´Ó0ÏÔÊ¾µ½9999
#include"display_4X8.h"

extern unsigned char code DuanMa[];
extern unsigned char TempData[];
extern void Display(unsigned char FirstBit,unsigned char Num);

void delay_n40us(unsigned int n)
{
	unsigned int i; 
	unsigned char j; 
  	for(i=n;i>0;i--) 
       for(j=0;j<2;j++);
}

void main()
{
	unsigned int i=0;
	while(1<2)
	{
		i++;
		if(i>9999)i=0;
		TempData[0]=DuanMa[i/1000];
		TempData[1]=DuanMa[i%1000/100];
		TempData[2]=DuanMa[i%100/10];
		TempData[3]=DuanMa[i%10];
		Display(0,4);
		delay_n40us(200);
	}
}

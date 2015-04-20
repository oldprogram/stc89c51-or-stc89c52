#include"led8.h"


unsigned char code DuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};// 显示段码值0~F
unsigned char code WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//分别对应相应的数码管点亮,即位码
unsigned char TempData[8]; //存储显示值的全局变量


/*------------------------------------------------
功能:显示函数，用于动态扫描数码管
参数:1) FirstBit表示8x8段数码管需要显示的第一位，如赋值2表示从第三个数码管开始显示
	 2) Num表示需要显示的位数，如需要显示99两位数值则该值输入2
------------------------------------------------*/
void Display(unsigned char FirstBit,unsigned char Num)
{
	static unsigned char i=0;

	DataPort=0;   //清空数据，防止有交替重影
	LATCH1=1;     //段锁存
	LATCH1=0;

	DataPort=WeiMa[i+FirstBit]; //取位码 
	LATCH2=1;     //位锁存
	LATCH2=0;

	DataPort=TempData[i]; //取显示数据，段码
	LATCH1=1;     //段锁存
	LATCH1=0;

	i++;
	if(i==Num)
		i=0;
}
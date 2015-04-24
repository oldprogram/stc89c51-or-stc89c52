#include"display_4X8.h"

unsigned char code DuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};// 显示段码值0~F
unsigned char code WeiMa[]={0xbf,0xdf,0xef,0xf7};//分别对应相应的数码管点亮,即位码
unsigned char TempData[4]; //存储显示值的全局变量

//------------------------------------------------
//4位8段共阴数码管显示函数
//第一个参数为0表示从第一个数码管开始显示num个数
//提前要显示的数要存在TempData中（TempData[0]表示要显示的第一个数）
//------------------------------------------------
void Display(unsigned char FirstBit,unsigned char Num)
{
	static unsigned char i=0;

	DataPort=0x00;   //清空数据，防止有交替重影
	DataControl=0x00;

	DataPort=TempData[i]; //取显示数据，段码
	DataControl=WeiMa[i+FirstBit];

	i++;
	if(i==Num)
		i=0;
}
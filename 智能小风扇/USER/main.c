/*-----------------------------------------------
名称：独立按键控制直流电机调速
内容：对应的电机接口需用杜邦线连接到uln2003电机控制端
使用5V-12V 小功率电机皆可 2个按键分别加速和减速
------------------------------------------------*/
#include "../FUNC/led8.h"
#include "../FUNC/uart.h"
#include "../FUNC/key8.h"
#include "../INTE/inte.h"

sbit DCOUT = P1^1;//定义电机信号输出端口
/*------------------------------------------------
全局变量
------------------------------------------------*/
unsigned char PWM_ON;   //定义速度等级
#define CYCLE 10        //周期

extern unsigned char code DuanMa[];// 显示段码值
extern unsigned char TempData[8]; //存储显示值的全局变量
/*------------------------------------------------
函数声明
------------------------------------------------*/
extern void Display(unsigned char FirstBit,unsigned char Num);//数码管显示函数
extern unsigned char KeyScan(void);//键盘扫描
extern void Init_Timer0(void);//定时器初始化
/*------------------------------------------------
主函数
------------------------------------------------*/
void main (void)
{
	unsigned char num;                  
	PWM_ON=0;
	Init_Timer0();    //初始化定时器0，主要用于数码管动态扫描
	
	while (1)         //主循环
	{
		num=KeyScan();    //循环调用按键扫描
		if(num==1)//第一个按键,速度等级增加
		{
			if(PWM_ON<CYCLE)
				PWM_ON++;
		}	
		else if(num==2)//第二个按键，速度等级减小
		{
			if(PWM_ON>0)
				PWM_ON--;
		}	
		TempData[0]=DuanMa[PWM_ON/10]; //显示速度等级
		TempData[1]=DuanMa[PWM_ON%10]; 	 
	}
}
/*------------------------------------------------
定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
	static unsigned char count;
	TH0=(65536-2000)/256;		  //重新赋值 2ms
	TL0=(65536-2000)%256;
	
	Display(6,2);                // 调用数码管扫描
	
	if (count==PWM_ON) 
    {
		DCOUT = 0;               //如果定时等于on的时间，
		//说明作用时间结束，输出低电平
    }
	count++;
	if(count == CYCLE)       //反之低电平时间结束后返回高电平
    {
		count=0;
		if(PWM_ON!=0)    //如果开启时间是0 保持原来状态
			DCOUT = 1;      	
    }
}


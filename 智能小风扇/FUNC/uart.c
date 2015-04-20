#include"uart.h"              


unsigned char getByte[8];          //定义临时变量
unsigned char flag; 			//接收标记
unsigned char point;			//指针

/*------------------------------------------------
串口初始化
------------------------------------------------*/
void InitUART  (void)
{
	flag=0;
	point=0;
	SCON  = 0x50;		        // SCON: 模式 1, 8-bit UART, 使能接收  
	TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重装
	TH1   = 0xFD;               // TH1:  重装值 9600 波特率 晶振 11.0592MHz  
	TR1   = 1;                  // TR1:  timer 1 打开                         
	EA    = 1;                  //打开总中断
	ES    = 1;                  //打开串口中断
}                            

/*------------------------------------------------
发送一个字节
------------------------------------------------*/
void SendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);
	TI = 0;
}
/*------------------------------------------------
发送一个字符串
------------------------------------------------*/
void SendStr(unsigned char *s)
{
	while(*s!='\0')// \0 表示字符串结束标志，通过检测是否字符串末尾
	{
		SendByte(*s);
		s++;
	}
}
/*------------------------------------------------
串口中断程序
------------------------------------------------*/
void UART_SER (void) interrupt 4 //串行中断服务程序
{
	if(RI)                        //判断是接收中断产生
	{
		RI=0;                      //标志位清零
		getByte[point]=SBUF;                 //读入缓冲区的值
		point++;
		if(point==8)
		{
			point=0;
			flag=1;
		}
	}
} 


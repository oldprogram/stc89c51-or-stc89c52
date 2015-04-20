#include"key8.h"
#include"delay.h"

extern void DelayUs2x(unsigned char t);//us级延时函数声明 
extern void DelayMs(unsigned char t); //ms级延时

/*------------------------------------------------
按键扫描函数，返回扫描键值
------------------------------------------------*/
unsigned char KeyScan(void)
{
	unsigned char keyvalue;
	if(KeyPort!=0xff)
	{
		DelayMs(10);
		if(KeyPort!=0xff)
		{
			keyvalue=KeyPort;
			while(KeyPort!=0xff);
			switch(keyvalue)
			{
			case 0xfe:return 1;break;
			case 0xfd:return 2;break;
			case 0xfb:return 3;break;
			case 0xf7:return 4;break;
			case 0xef:return 5;break;
			case 0xdf:return 6;break;
			case 0xbf:return 7;break;
			case 0x7f:return 8;break;
			default:return 0;break;
			}
		}
	}
	return 0;
}


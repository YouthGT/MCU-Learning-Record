#include <reg52.h>
#include <intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

sbit flag = P3^7;//外部中断信号产生脚
sbit key_s2 = P3^0;//独立按键s2
sbit beep = P2^3;

void int1Inint();
void delay(uint z);

void main ()//main函数自身会循环
{
	int1Inint();//外部中断1初始化
	while(1)
	{
		if(key_s2 == 0)//判断按键是否按下
		{
			delay(20);//按键消抖
			if(key_s2 == 0);
			{
				
				flag = 1;
				flag = 0;//产生下降沿
				while(!key_s2);//判断是否松手
			}
			
		}
	}
	
}
//外部中断1初始化
void int1Inint()
{
	EA = 1;//中断的总开关
	EX1 = 1;//外部中断的总开关
	IT1 = 1;//选择外部中断为下降沿触发
}

//外部中断1中断服务程序  写在主函数之后不需要声明
void int1()interrupt 2
{
	beep =~beep;
}
//毫秒级延时函数
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}
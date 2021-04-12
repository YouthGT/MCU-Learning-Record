#include <reg52.h>
#include <intrins.h>
//宏定义
#define uint unsigned int
#define uchar unsigned char
	
sbit beep=P2^3;//蜂鸣器位定义
	
uchar temp;//LED灯相关变量

void	delay (uint z);//毫秒级相关延时函数声明

void main()
{
	temp=0xf0;//1111 0000 
	P1=temp;
	delay(100);
	while(1)
	{
		temp=_crol_(temp,1);//循环左移，四位一起流动
		P1=temp;
		beep=~beep;//取反（本来是1关闭取反后为零打开while循环达到滴滴声）
		delay(100);
	}
}
//延时函数
void delay (uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
	
}
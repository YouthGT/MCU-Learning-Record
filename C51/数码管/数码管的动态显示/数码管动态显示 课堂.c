#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit WE = P2^7;
sbit DU = P2^6;

void delay(uint z);//声明延时函数
void display(uchar i);//声明显示函数

void main()
{
	while(1)
	{
		P0 = 0xff;//清除段码
		WE = 1;//打开段选锁存器
		P0 = 0xfe;//1111 1110
		WE = 0;//锁存位选数�?
		
		DU = 1;//打开段锁存器
		P0 = 0x06;//0000 0110
		DU = 0;//锁存段选数�?
		delay(5);//延时5ms
		
		P0 = 0xff;//清除段码
		WE = 1;
		P0 = 0xfd;//1111 1101
		WE = 0;
		
		DU = 1;
		P0 = 0x5b;//0101 1011
		DU = 0;
	    delay(5);//延时5ms
		
		P0 = 0xff;//清除段码
		WE = 1;
		P0 = 0xfb;//1111 1011
		WE = 0;
		
		DU = 1;
		P0 = 0x4f;//0101 1011
		DU = 0;
		delay(5);//延时5ms
		
	}
	
}
//毫秒级延时函�?
void delay(uint z)
{
	uint x,y;
	for (x = z; x > 0;x--)
		for(y = 114; y>0; y--);
	
}
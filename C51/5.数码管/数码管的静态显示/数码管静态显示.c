#include <REG52.H>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit DU = P2^6;//数码管段选  U9
sbit WE = P2^7;//数码管位选  U8

void main()//
{
	WE = 1;//打开位选锁存器
	P0 = 0xfe;//控制位选锁存器1111 1110
	WE = 0;//关闭位选锁存器
	
	DU = 1;//打开段选锁存器
	P0 = 0xff;//控制段选锁存器 1111 1111显示为8. 
	DU = 0;//关闭锁存寄存器
	
	while(1)
	{
			P0 = 0x06;//段选锁存器已经关闭，无影响
	}
} 
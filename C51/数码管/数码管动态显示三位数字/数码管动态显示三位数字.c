#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit WE = P2^7;
sbit DU = P2^6;

//共阴极数码管段选数组0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//将数组储存在ROM区

void delay(uint z);//声明延时函数
void display(uint i);//声明显示函数


void main()
{
		display(111UL);//输入需要显示的值
}


//毫秒级延时函数
void delay(uint z)
{
	uint x,y;
	for (x = z; x > 0;x--)
		for(y = 114; y>0; y--);
	
}
//数码管显示函数
void display(uint i)
{
	uint bai, shi, ge;
	bai = i / 100;         //212 / 100 = 2
	shi = i % 100 / 10;    //212 % 100 / 10 = 1
	ge  = i % 10;          //212 % 10 = 2
	
	while(1)
	{
	//第一位数码管(bai)
	    P0 = 0xff;//清除段码
		WE = 1;//打开段选锁存器
		P0 = 0xfe;//1111 1110
		WE = 0;//锁存位选数据
		
		DU = 1;//打开段锁存器
		P0 = table[bai];
		DU = 0;//锁存段选数据
		delay(5);//延时5ms
	 
	//第二位数码管(shi)
	    P0 = 0xff;//清除段码
		WE = 1;//打开段选锁存器
		P0 = 0xfd;//1111 1101
		WE = 0;//锁存位选数据
		
		DU = 1;//打开段锁存器
		P0 = table[shi];
		DU = 0;//锁存段选数据
		delay(5);//延时5ms
	
	//第三位数码管(ge)
		P0 = 0xff;//清除段码
		WE = 1;//打开段选锁存器
		P0 = 0xfb;//1111 1011
		WE = 0;//锁存位选数据

		DU = 1;//打开段锁存器
		P0 = table[ge];
		DU = 0;//锁存段选数据
		delay(5);//延时5ms
	}
}
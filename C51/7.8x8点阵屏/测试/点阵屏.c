#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit DIO  = P3^4;//串行数据口
sbit S_CLK = P3^5;//移位寄存器时钟
sbit R_CLK = P3^6;//输出寄存器时钟
 
void main()
{
  	//ROW 0x80，COL 0xfe
	uchar i, dat;
	dat = 0xfe;//行
	for(i = 0; i < 8; i++)
	{
		
		S_CLK = 0;
		R_CLK = 0;
		if(dat & 0x01)//按位与
			DIO = 1;
		else 
			DIO = 0;
		S_CLK = 1;
		//dat = dat>>1;
		dat >>= 1;
	}
	dat = 0x80;//列
	for(i = 0; i < 8; i++)
	{
		
		S_CLK = 0;
		R_CLK = 0;
		if(dat & 0x01)//按位与
			DIO = 1;
		else 
			DIO = 0;
		S_CLK = 1;
		//dat = dat>>1;
		dat >>= 1;
	}
	R_CLK = 1;
	while(1);
}





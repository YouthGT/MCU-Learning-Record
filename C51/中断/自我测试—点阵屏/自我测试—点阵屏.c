#include <reg52.h>
#include <intrins.h>

#define uint unsigned int 
typedef unsigned char uchar;

sbit DIO = P3^4;//串行数据口
sbit S_CLK = P3^5;//移位寄存器时钟
sbit R_CLK = P3^6;//输出寄存器时钟

uchar code table[5][8] = {
0xE0, 0xEE, 0x01, 0x6D, 0x01, 0x6D, 0x01, 0xEF, 
0xEF, 0xC7, 0x97, 0xF7, 0x00, 0xE7, 0xF9, 0x81,
0x81, 0x81, 0xE7, 0xE7, 0xE7, 0xC7, 0xC7, 0xE7,
0x81, 0x81, 0xC7, 0xF3, 0xF9, 0x99, 0x81, 0xC3,
0xC3, 0x81, 0x99, 0xF9, 0xE3, 0x99, 0x81, 0xC3		
};//输出字符的取模多维数组

void Send_Byte(uint dat);//声明自定义函数

void main()//main函数会循环！！！！
{
    uint j,k,z,ROW;
	ROW = 0x80;//行值初始化
	while(1)	   //使其循环显示
	{
		for(k=0;k<5;k++)//分别输出五个字符
		{
			for(z=0;z<100;z++)//延时作用，让一个字符显示一段时间
			{
				for (j = 0;j<8; j++)//分别显示八行
					{
					   Send_Byte(table[k][j]);//将列信号输入
					   Send_Byte(ROW);//将行信号输入，给一行高电平
					   R_CLK = 1;//产生上升沿，将其并行输出
					   R_CLK = 0;//为下一次上升沿准备
					   ROW = _cror_(ROW,1);//将点亮的行线下移
					}
		     }
		}
    }
}

void Send_Byte(uint dat)//发送字节函数
{
	uint i;
	for (i=0;i<8;i++)//进行串行输入
	{
		S_CLK = 0;//为上升沿做准备
		R_CLK = 0;//为上升沿做准备
		if(dat & 0x01)//按位与操作，都真为真
			DIO = 1;
		else
			DIO = 0;
		dat >>= 1;//右移运算符
		S_CLK = 1;//产生上升沿输入字节
	}
}

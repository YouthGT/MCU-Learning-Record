#include <reg52.h>
#include <intrins.h>
#include <IIC.h>

#define uchar unsigned char
#define uint unsigned int
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3


sbit DU = P2^6;//数码管段选
sbit WE = P2^7;//数码管段选
sbit key_s2 = P3^0;//独立按键S2
sbit key_s3 = P3^1;//独立按键S3
extern bit AckFlag;//应答标志位
uint num;//数码管显示的值


//共阴数码管段选表0-9
uchar code SMGduan[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//数码管位选码
uchar code SMGwei[] = {0xfe, 0xfd, 0xfb};

void delay(uint z);
void timer0Init();
void display(uint i);

void main()
{
	timer0Init();//定时器0初始化
	while (1)
	{
		EA = 0;//屏蔽中断
		num = PCF8591Read(CH0);
		EA = 1;//开中断
		delay(5);	
	}
	
}


void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 
//定时器0初始化函数
void timer0Init()
{
	EA = 1;//打开总中断
	ET0 = 1;//打开定时器0中断
	TR0 = 1;//启动定时器0
	TMOD = 0x01;//定时器工作模式16位定时模式
	TH0 = 0xed;
	TL0 = 0xff;//定时5ms
}
//定时器0中断函数
void timer0() interrupt 1
{
    TH0 = 0xed;
	TL0 = 0xff;//定时5ms
	display(num);//数码管显示
}
//数码管显示函数
void display(uint i)
{
	static uchar wei;//静态局部变量
	P0 = 0xff;
	WE = 1;
	P0 = SMGwei[wei];
	WE = 0;
	switch(wei)
	{
		case 0:
			DU = 1;
			P0 = SMGduan[i / 100];
			DU = 0;
			break;
		case 1:
			DU = 1;
			P0 = SMGduan[i % 100 / 10];
			DU = 0;
			break;
		case 2:
			DU = 1;
			P0 = SMGduan[i % 10];
			DU = 0;
			break;
	}
	wei++;
	if(wei == 3)
		wei = 0;
}

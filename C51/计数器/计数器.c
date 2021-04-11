/*
将P3^4和P1口任意一角相连接，将脉冲计数并以数码管显示出来
方波的周期为一秒
*/
#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;
sbit DU = P2^6;

//提前声明自定义函数
void timer0Init();
void timer1Init();
void display(uint i);
void delay (uint z);

//共阴极数码管段选数组0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//将数组储存在ROM区

//主函数
void main()
{
	uchar mSec;
	timer0Init();//初始化计数器0，用来计数
	timer1Init();//初始化定时器1，用来延时
	while(1)
	{
		if(TF1 == 1)//判断定时器1是否溢出
		{
			TF1 = 0;//软件清零溢出标志位
			TH1 = 0x4b;//定时寄存器高八位
			TL1 = 0xfd;//定时寄存器低八位
			mSec++;//50ms到
			if(mSec == 10)//500ms到
			{
				mSec = 0;//为下一次延时50ms准备
				P1 = ~P1;//产生方波，以八个LED的亮灭表示出来
				
			}
		}
//		delay(500);//会影响数码管动态扫描实时显示，所以用定时器延时	
		
		display(TL0);//数码管显示
	 }	
}
//计数器0初始化
void timer0Init()
{
	TR0 = 1;//启动计数器0
	TMOD |= 0x05;//计数器模式,16位计数模式
	TH0 = 0;
	TL0 = 0;
	
}
//定时器1初始化
void timer1Init()
{
	TR1 = 1;//启动定时器1
	TMOD |= 0x10;//定时器1工作模式,16位定时模式
	TH1 = 0x4b;
	TL1 = 0xfd;//定时50ms
	
}
//延时函数
void delay (uint z)
{
	uint x,y;
	for (x = z; x > 0; x--)
		for(y = 114; y > 0; y--);
}
//数码管动态显示函数
void display(uint i)
{
	uint bai,shi,ge;
	bai = i / 100;
	shi = i %100 / 10;
	ge = i % 10;

	//百位显示
	P0 = 0xff;//清除断码
	WE = 1;
	P0 = 0xfe;//1111 1110打开第一位数码管
	WE = 0;
	
	DU = 1;
	P0 = table[bai];
	DU = 0;
	delay(5);
	
	//十位显示
	P0 = 0xff;//清除断码
	WE = 1;
	P0 = 0xfd;//1111 1101打开第二位数码管
	WE = 0;
	
	DU = 1;
	P0 = table[shi];
	DU = 0;
	delay(5);
	
	//个位显示
	P0 = 0xff;//清除断码
	WE = 1;
	P0 = 0xfb;//1111 1011打开第三位数码管
	WE = 0;
	
	DU = 1;
	P0 = table[ge];
	DU = 0;
	delay(5);	

}

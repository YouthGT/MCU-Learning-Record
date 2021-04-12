#include <reg52.h>
#include <intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

sbit DU = P2^6;//数码管段选
sbit WE = P2^7;//数码管段选
uint num;//数码管显示的值

//共阴数码管段选表0-9
uchar code SMGduan[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//数码管位选码
uchar code SMGwei[] = {0xfe, 0xfd, 0xfb};

void timer0Init();
void display(uint i);
void UARTInit();

void main()
{
	timer0Init();//定时器0初始化
	UARTInit();//串口初始化
	while(1);
}
//定时器0初始化函数
void timer0Init()
{
	EA = 1;//打开总中断
	ET0 = 1;//打开定时器0中断
	TR0 = 1;//启动定时器0
	TMOD |= 0x01;//定时器工作模式16位定时模式
	TH0 = 0xed;
	TL0 = 0xff;//定时5ms
}
//串口初始化
void UARTInit()
{
	EA = 1;//打开总中断
	ES = 1;//打开串口中断
	SM0 =0; SM1 = 1;//串口工作方式1,8位
	REN = 1;//串口允许接收
	TR1 = 1;//启动定时器1 
	TMOD |= 0x20;//定时器1，工作模式2 8位自动重装
	TH1 = 0xfd;
	TL1 = 0xfd;//设置波特率9600
}
//定时器0中断函数
void timer0() interrupt 1
{
    TH0 = 0xed;
	TL0 = 0xff;//定时5ms
	display(num);//数码管显示
}
//串口中断函数
void UART() interrupt 4
{
	uchar temp;
	if(RI)//判断接收是否完成
	{
		num = SBUF;//读SBUF
		RI = 0;//软件清零接收标志位
		temp = num;
		SBUF = ++temp;//写SBUF，把要发送的数据发送给缓存器
	}
	if(TI)//判断是否发送完成
		TI = 0;//清零发送完成标志
}
//数码管显示函数
void display(uint i)
{
	static uchar wei;//静态局部变量
	P0 = 0xff;//清除断码
	WE = 1;//打开位选锁存器
	P0 = SMGwei[wei];
	WE = 0;//锁存位选数据
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
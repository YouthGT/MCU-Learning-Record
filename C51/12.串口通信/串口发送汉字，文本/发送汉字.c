#include <reg52.h>
#include <stdio.h>

#define uint unsigned int
#define uchar unsigned char
	
void UARTInit();
void delay(uint z);
	
void main()
{
	UARTInit();//串口初始化
	while(1)
	{
		TI = 1;
		puts("测试使用，测试使用2021.01.23");
		while (!TI);
		TI = 0;
		delay(1000);
	}
}
//串口初始化
void UARTInit()
{
	SM0 = 0; SM1 = 1; //串口工作方式1，8位UART比特率可变
	TR1 = 1;//启动定时器1
	TMOD |=0x20;//定时器1，工作模式2 8位自动重装
	TH1 = 0xfd;
	TL1 = 0xfd;//设置波特率9600
	
}
//延时函数
void delay(uint z)
{
	uint x,y;
	for(x = z;x > 0;x--)
		for(y = 114; y > 0; y--);
}
/*************************************
备注：
使用printf()puts()前都应软件置位TI = 1；
printf()puts()  使用putchar函数发送 字节（一个汉字两个字节）

void putchar(uchar sbyte )
{
    while(！TI);   //等待发送完

    SBUF=sbyte;

}

所以第一次调用putchar前没TI=1 永远等待
*************************************/

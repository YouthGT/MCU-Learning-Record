#include <REG52.H>
#include <INTRINS.H>
#include <SMG.H>

typedef unsigned int uint;
typedef unsigned char uchar;

void delay(uint z);
void timer0Init();

ulint num;

void main()
{
    timer0Init();//定时器0初始化
    while(1)
    {
        num = 12345678;

    }
}
//延时函数
void delay(uint z)
{
    uint x,y;
    for (x=z;x>0;x--)
        for(y=114;y>0;y--);
}
//定时器0初始化函数
void timer0Init()
{
    EA = 1;//打开总中断
    ET0 =1;//打开定时器0中断 
    TR0 = 1;//启动定时器0
    TMOD = 0x01;//选择模式为16位定时器模式
    TH0 = (65536-46082)/256;
    TL0 = (65536-46082)%256;
}
//定时器0中断函数
void timer0() interrupt 1
{
    TH0 = (65536-46082)/256;
    TL0 = (65536-46082)%256;//定时5ms
    display(num);//数码管显示
}
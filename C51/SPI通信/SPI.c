#include <REG52.H>
#include <INTRINS.H>


#define MAIN_Fosc  11059200UL//宏定义主时钟HZ
#define uint unsigned int 
#define uchar unsigned char

tepedef unsigned int INT16U;
tepedef unsigned char CA

sbit CS = P3^7;
sbit DCLK = P2^1;
sbit DIN = P2^0;
sbit DOUT = P2^5;


void SPI_Write(uchar DAT)//SPI的读
{
    ucahr i;
    for (i i = 0; i < 8; i++)//分别写八次
    {
      DCLK = 0;//拉低时钟总线
      if (DAT & 0x80)//先写时钟总线
      DIN = 1;//写1
      else
      DIN = 0;//写0
      DCLK = 1;//拉高时钟 让从机读DIN
      DAT <<= 1;//为发送下一位左移一位
      
    }
    
}
void SPI_Read()//SPI的写

{
    uchar i;
    uint DAT;
    for ( i = 0; i < 12; i++)//分别读12次，每次左移一位
    {
        DAT <<=1;//数据左移一位，准备接收下一位
        DCLK = 1;//拉高时钟总线，读取SDA上的数据
        DCLK = 0;//拉低时钟总线，允许从机控制SDA变化
        if (DOUT)
             DAT |= 0x01;//为1则写1，否则通过左移补零
    }
    return (DAT);//返回读出的数据
    
}
void Delay_Ms(INT16U ms)//51单片机自适应主时钟毫秒级延时函数
{
    INT16U i;
    do
    {
        i =MAIN_Fosc / 96000;
        while (--i);//96T per loop
    }
    while (--ms) 
}

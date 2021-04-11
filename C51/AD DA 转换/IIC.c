#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define PCF8591ADDR 0X90   //PCF8591硬件地址
#define	IICRead 1		   //IIC读方向位
#define	IICWrite 0		   //IIC写方向位

sbit SCL = P2^1;//I2C时钟总线
sbit SDA = P2^0;//I2C数据总线
bit AckFlag;//应答标志位

//延时函数
void delay5us()
{
	_nop_();
}
/*====================================
函数	：IICStart()
参数	：无
返回值	：无
描述	：IIC总线起始信号
====================================*/
void IICStart()
{
	SCL = 1;
	SDA = 1;
	delay5us();
	SDA = 0;
	delay5us();
} 
/*====================================
函数	：IICStop()
参数	：无
返回值	：无
描述	：IIC总线停止信号
====================================*/
void IICStop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	delay5us();//状态保持5us
	SDA = 1;
	delay5us();//状态保持5us	
}
/*====================================
函数	：ReadACK()
参数	：无
返回值	：1非应答，0应答
描述	：IIC总线读从机应答信号
====================================*/
bit ReadACK()
{
	SCL = 0;//拉低时钟总线，允许从机控制SDA
	SCL = 1;//拉高读SDA
	delay5us();
	if(SDA)//SDA为高电平
	{
		SCL = 0;
		return(1);
	}
	else
	{
		SCL = 0;
		return(0);
	}
}
/*====================================
函数	：SendACK(bit i)
参数	：1主机发送非应答，0发送应答
返回值	：无
描述	：主机发送应答信号
====================================*/
void SendACK(bit i)
{
	SCL = 0;
	if(i)
		SDA = 1;
	else
		SDA = 0;
	SCL = 1;
	delay5us();
	SCL = 0;
	SDA = 1;//释放数据总线
}
/*====================================
函数	：IICSendByte(uchar DAT)
参数	：DAT需要发送的数据
返回值	：无
描述	：IIC发送一个字节数据
====================================*/
void IICSendByte(uchar DAT)
{
	uchar i;
	for (i =0;i<8;i++)//利用左移运算符发送数据
	{
		SCL = 0;
		if(DAT & 0x80)
			SDA = 1;
		else
			SDA = 0;
		SCL = 1;
		DAT <<= 1; 
	}
	SCL= 0;
	SDA = 1;//释放总线
}
/*====================================
函数	：PCF8591Write(uchar ADDR, DAT)
参数	：ADDR 单元地址0-255，DAT 需要输入的数据0-255
返回值	：无
描述	：PCF8591指定单元写入一个字节数据
====================================*/
//void PCF8591Write(uchar ADDR,DAT)
//{
//	IICStart();//IIC起始信号
//	IICSendByte(PCF8591ADDR + IICWrite);
//	if (ReadACK())//读从机应答
//		AckFlag = 1;//NoAck
//	else
//		AckFlag = 0;//Ack
//	IICSendByte(ADDR);//发送储存单元地址字节
//	if(ReadACK())//读从机应答
//		AckFlag = 1;//NoAck
//	else
//		AckFlag = 0;//ACk
//	IICSendByte(DAT);
//	if(ReadACK())
//		AckFlag = 1;
//	else 
//		AckFlag = 0;
//	IICStop();//IIC停止信号	
//}
/*====================================
函数	：IICReadByte()
参数	：无
返回值	：返回读出的一字节数据
描述	：IIC总线读一字节数据
====================================*/
uchar IICReadByte()
{
	uchar i,DAT;
	for(i = 0;i < 8;i++)//分别读八次，每次读一位
	{
		DAT <<= 1;//数据左移准备接受下一位
		SCL = 0;//拉低时钟总线，允许从机控制SDA变化
		SCL = 1;//拉高时钟总线，读取SDA上的数据
		if(SDA)
			DAT |=0x01;
	}
	return (DAT);//读出返回的数据
}
/*====================================
函数	：PCF8591Read(uchar ADDR)
参数	：ADDR 单元地址	0-255
返回值	：返回指定单元的数据
描述	：读PCF8591指定单元内数据
====================================*/
uchar PCF8591Read(uchar Ctrl)
{
	uchar DAT;
	IICStart();//IIC起始信号
	IICSendByte(PCF8591ADDR + IICWrite);//发送器件地址加读写方向位
	if(ReadACK())//读从机应答
		AckFlag = 1;	//NOACK
	else
		AckFlag = 0;	//ACK
	IICSendByte(Ctrl);//IIC发送一个字节
	ReadACK();//读从机应答
	IICStart();//再次产生IIC起始信号
	IICSendByte(PCF8591ADDR + IICRead);//发送器件地址加读写方向位 读
	if(ReadACK())//读从机应答
		AckFlag = 1;	//NOACK
	else
		AckFlag = 0;	//ACK
	DAT = IICReadByte();//读一字节
	SendACK(1);//主机发送非应答
	IICStop(); //IIC停止信号
	return(DAT);//返回读出数据
}


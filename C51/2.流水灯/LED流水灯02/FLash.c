#include <reg52.h>
#include <intrins.h>

#define uint  unsigned int //宏定义用uxxx替换unsigned xxx
#define uchar unsigned char//typedef 已有数据类型 新的数据类型；语句要加分号	

uchar temp;//LED灯相关变量

int delay(uint z);//声明延时函数

int main()//主函数自身会循环
{
	temp=0xfe;
	P1=temp;//1111 1110
	delay(10);
	while (1)
	{
			temp=_crol_(temp,1);//循环左移一位
			P1=temp;
			delay(100);	
	}
	return 0;
}
//延时函数
int delay(uint z)//毫秒级延时函数
{
	uint x,y;
	for (x=z;x>0;x--)//一条语句省略花括号
		for (y=114;y>0;y--);
	return 0;
}
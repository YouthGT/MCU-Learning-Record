#include <reg52.h>//引用头文件
	//位定义
unsigned int i ;//0~65535


int mian()//main函数自身会循环
	
{
	while (1)
	{
		P1 = 0xaa;//P1口整组操作
		i = 65535;
		while(i--);//亮的时间长一点
		P1 = 0xff;//1111 1111 八个高电平 熄灭八个LED灯
		i = 65535;
		while(i--);//灭的时间长一点
	}

	
	return 0;
}
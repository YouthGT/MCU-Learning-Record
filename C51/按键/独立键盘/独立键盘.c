#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;
sbit DU = P2^6;
sbit key_s2 = P3^0;
sbit key_s3 = P3^1;

uchar num = 0;

void delay(uint z);

//共阴极数码管段选数组0-9
uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//将数组储存在ROM区

void main()
{
	WE = 1;//打开位选锁存器
	P0 = 0xfe;//1111 1110
	WE = 0;//关闭位选锁存器
	
	
	while(1)
	{
		if(key_s2 == 0)
		{
			delay(20);//去除按键抖动
			if(key_s2 == 0)
			{
				if(num != 9)
					num++;
				    DU = 1;
					P0 = table[num];//按下就变化
					DU = 0;
					while(!key_s2);//松手检测
			}
		}

		
		if(key_s3 == 0)
		{	
			delay(20);//去除按键抖动
			if(key_s3 == 0)
			{
				if(num > 0)
					num--;
					DU = 1;
					P0 = table[num];//按下就变化
					DU = 0;
					while(!key_s3);//松手检测
			}
		}

			
			//刷新显示			
			DU = 1;
			P0 = table[num];
			DU = 0;
			

	}
}

//毫秒级延时函数定义
void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 
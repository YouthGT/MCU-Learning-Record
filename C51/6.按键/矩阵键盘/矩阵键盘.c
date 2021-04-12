#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit WE = P2^7;//位选
sbit DU = P2^6;//段选
sbit beep = P2^3;//蜂鸣器

uchar num = 0;//数码管显示的值
uchar KeyValue;//按键值

void delay(uint z);
void KeyScan( );

//共阴极数码管段选表
uchar code table[] = {
//0   1     2    3    4    5   6    7     8
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
//9    A   B     C    D    E     F   H    L
0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x38,
//N    U   -    熄灭
0x37,0x3e,0x40,0x00};

void main()
{
	WE = 1;//打开位选锁存器
	P0 = 0xfe;//1111 1110
	WE = 0;//关闭位选锁存器
	
	
	while(1)
	{
//			beep = ~beep;//蜂鸣器

	        KeyScan();
			
			DU = 1;
			P0 = table[KeyValue];
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
//键盘扫描函数
void KeyScan( )
{
	P3 = 0xf0;//列扫描
	if(P3 != 0xf0)//判断按键是否被按下
	{
		delay(10);//延时10ms
		if(P3 != 0xf0)//判断按键是否被按下
			{
				switch(P3)
				{
					case 0xe0:KeyValue = 0;
					break;
					case 0xd0:KeyValue = 1;
					break;
					case 0xb0:KeyValue = 2;
					break;
					case 0x70:KeyValue = 3;
					break;
				
				}
				P3 = 0x0f;//行扫描
				switch(P3)
				{
					case 0x0e:KeyValue = KeyValue;
					break;
					case 0x0d:KeyValue = KeyValue + 4;
					break;
					case 0x0b:KeyValue = KeyValue + 8;
					break;
					case 0x07:KeyValue = KeyValue + 12;
					break;
				}
				while(P3 != 0x0f);//松手检测
			}
	}
	P3 = 0xff;//独立按键扫描
	if(P3 = 0xff) 
	{
		delay(10);
		if(P3 != 0xff)//判断独立键盘是否按下
			switch(P3)
			{
				case 0xfe: KeyValue = 16;  break;
				case 0xfd: KeyValue = 17;  break;
				case 0xfb: KeyValue = 18;  break;
				case 0xf7: KeyValue = 19;  break;

			}
			while(P3 != 0xff);//松手检测
		
	}
}
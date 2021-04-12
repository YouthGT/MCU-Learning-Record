#include <REG52.H>
#include <INTRINS.H>


#define ulint unsigned long int
#define uchar unsigned char 

sbit WE = P2^7;
sbit DU = P2^6;

//八位数码管位选表
uchar code SMGwei[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
//共阴数码管段选表0-9
uchar code SMGduan[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

//数码管显示函数
void display(ulint i)
{
    static uchar wei;//静态局部变量
    P0 = 0xff;//清除断码
    WE = 1;//打开数码管位选
    P0 = SMGwei[wei];
    WE = 0;//关闭数码管位选
    switch (wei)
    {
        case 0:
            DU = 1;
            P0 = SMGduan[i/10000000];
			DU = 0;
            break;
		case 1:
			DU = 1;
			P0 = SMGduan[i % 10000000 / 1000000];
			DU = 0;
			break;
		case 2:
			DU = 1;
			P0 = SMGduan[i % 1000000 / 100000];
			DU = 0;
			break;
        case 3:
			DU = 1;
			P0 = SMGduan[i % 100000 / 10000];
			DU = 0;
			break;
        case 4:
			DU = 1;
			P0 = SMGduan[i % 10000 / 1000];
			DU = 0;
			break;
        case 5:
			DU = 1;
			P0 = SMGduan[i % 1000 / 100];
			DU = 0;
			break;
        case 6:
			DU = 1;
			P0 = SMGduan[i % 100 / 10];
			DU = 0;
			break;
        case 7:
			DU = 1;
			P0 = SMGduan[i % 10];
			DU = 0;
			break;   
    }
    wei++;
    if(wei == 8)
        wei = 0;
}
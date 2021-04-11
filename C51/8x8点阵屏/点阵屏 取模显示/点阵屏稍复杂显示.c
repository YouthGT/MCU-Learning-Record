#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit DIO  = P3 ^ 4; //串行数据口
sbit S_CLK = P3 ^ 5; //移位寄存器时钟
sbit R_CLK = P3 ^ 6; //输出寄存器时钟

uchar code dianzi[5][8] = {
	0xE0, 0xEE, 0x01, 0x6D, 0x01, 0x6D, 0x01, 0xEF, 
	0xEF, 0xC7, 0x97, 0xF7, 0x00, 0xE7, 0xF9, 0x81,
	0x00, 0x00, 0xE7, 0xE7, 0xE7, 0xE7, 0xC7, 0xE7,
	0x81, 0x81, 0xC7, 0xF3, 0xF9, 0x99, 0x81, 0xC3,
	0xC3, 0x81, 0x99, 0xF9, 0xE3, 0x99, 0x81, 0xC3
};

void Send_Byte(uchar dat);
void main() {
	uint j, k, z, ROW = 0x80;
	while (1) {
		for (k = 0; k < 5; k++) {
			for (z = 0; z < 1000; z++) {
				for (j = 0; j < 8; j++) {
					Send_Byte(dianzi[k][j]);//列
					Send_Byte(ROW);//行
					R_CLK = 1;
					R_CLK = 0;
					ROW = _cror_(ROW, 1);
				}
			}
		}
	}

}


void Send_Byte(uchar dat) {
	uchar i;
	S_CLK = 0;
	R_CLK = 0;
	for (i = 0; i < 8; i++) {

		if (dat & 0x01) //按位与
			DIO = 1;
		else
			DIO = 0;
		S_CLK = 1;
		//dat = dat>>1;
		dat >>= 1;
		S_CLK = 0;
	}
}




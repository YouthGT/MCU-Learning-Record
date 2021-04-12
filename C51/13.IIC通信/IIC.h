#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char 

void At24c02Write(uchar ADDR,DAT);
uchar At24c02Read(uchar ADDR);
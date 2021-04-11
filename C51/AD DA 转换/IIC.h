#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char 

void PCF8591(uchar ADDR,DAT);
uchar PCF8591Read(uchar Ctrl);
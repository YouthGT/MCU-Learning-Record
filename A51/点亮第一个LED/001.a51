ORG 0000H ;伪指令，程序起始位置，可以给堆栈留位置
MOV A,#11111110B ;低电平点亮LED
MOV P2,A ;送给P0口
JMP $ ;跳转到当前的地址
END
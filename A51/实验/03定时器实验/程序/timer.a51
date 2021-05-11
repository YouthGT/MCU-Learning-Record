     ORG 0000H    ;将下面的绝对跳转语句放到地址0100H
	 AJMP MAIN    ;绝对跳转到主程序
	 ORG 0100H    ;将下面程序块放到地址0100H
MAIN:SETB TR0     ;打开定时器0
     MOV R7,#42   ;设置循环次数，保证延时时间
LOOP:MOV P1,A     ;将A中的数放入P1口
     MOV TMOD,#01H;设置定时器工作方式为方式1
	 MOV TH0,#00H ;设置高八位
	 MOV TL0,#00H ;设置低八位
	 JNB TF0,$    ;若没有溢出则等待
     CLR TF0	  ;清空溢出标志位
     DJNZ R7,LOOP ;若R7为零则转回LOOP
     CPL A        ;将A取反
	 SJMP MAIN    ;无条件转回MAIN
	 END          ;程序结束
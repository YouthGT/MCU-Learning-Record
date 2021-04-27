	   ORG  0000H     ;将下面的绝对跳转语句放到地址0100H
	   AJMP MAIN      ;绝对跳转到主程序
	   ORG  0003H     ;将下面的绝对跳转语句放到地址0003H
	   AJMP INT	      ;绝对跳转到INT
	   ORG  0100H     ;将下面程序块放到地址0100H
MAIN:  SETB EX0       ;设置外部中断0下降沿触发
       SETB EA        ;打开总中断
	   SJMP $         ;等待中断
	   ORG  0200H	  ;将下面程序块放到地址0200H	   
INT:   MOV  R0,#08H   ;循环八次
       MOV  A,#01H    ;将01H放入Ａ中 0000 0001最低位的灯亮
LIGHT: MOV  P1,A      ;将A中的数放入P1口
       MOV  R2,#199   ;内外循环延时
LOOPS: MOV  B,#250    ;T=1us
LOOPR: DJNZ B,LOOPR   ;2T=2us
       DJNZ R2,LOOPS  ;2T=2us
	   RL   A         ;循环左移
       DJNZ R0,LIGHT  ;无条件转移到LIGHT
	   RETI           ;中断返回
	   END            ;程序结束

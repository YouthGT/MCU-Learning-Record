/***********主函数***********/
	   ORG  0000H    ;程序入口
       MOV  A,#0FFH  ;全部置一
      ;SETB  C      ;将CY置一
	   CLR   C       ;将CY清零
LIGHT: RLC  A        ;A中的数带进位循环左移
	   MOV  P2,A     ;将A中的数放入Px口
       CALL DELAY    ;调用延时函数
       AJMP LIGHT    ;无条件转移到LIGHT
/**********延时函数**********/
DELAY: MOV  R2,#199  ;
LOOPS: MOV  B,#250   ;T=1us
LOOPR: DJNZ B,LOOPR  ;2T=2us
       DJNZ R2,LOOPS ;2T=2us
	   RET
	   END




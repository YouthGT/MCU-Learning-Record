
/**********延时函数**********/
       OGR 1000H
DELAY: MOV R2,#CTS
LOOPS: MOV B,#CTR ;T=1us
LOOPR: DJNZ B,LOOPR ;2T=2us
       DJNZ R2,LOOPS ;2T=2us
	   END
/***********主函数***********/

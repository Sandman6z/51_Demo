#include<reg51.h> 
void Delay1(int del)
{
	int i,j;
	for(i=0; i<del; i++)
	for(j=0; j<1827; j++)   
	;
}
void Delay(unsigned int t)
{
 while(--t);
}
 //函数声明
unsigned int z,y;
void main (void)//主函数
{
	unsigned int CYCLE=400,PWM_LOW=0;//定义周期并赋值
	while (1)         //主循环
	{

/*--------整排LED灯呼吸---------*/
		
		Delay1(100); 								//加延时，可以看到熄灭的过程（下面程序同理）
		for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)   	//PWM_LOW表示低
			{ 
				P1=0x00;        				
				Delay(PWM_LOW);
				P1=0xff; 
				Delay(CYCLE-PWM_LOW);
			}
		P1=0xff;										
		for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--) 	//与逐渐变亮相反的过程
			{
			   	P1=0x00;							//点亮LED 
			   	Delay(PWM_LOW);
			   	P1=0xff;							//熄灭LED
			  	Delay(CYCLE-PWM_LOW);				//主循环中添加其他需要一直工作的程序，延时长度，600次循环中从599减至1
			}

}
}

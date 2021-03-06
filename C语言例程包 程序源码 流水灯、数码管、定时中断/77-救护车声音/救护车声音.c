 /*-----------------------------------------------
  名称：喇叭
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：模救护车发声
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

sbit SPK=P1^2;    //定义喇叭端口
unsigned char frq; 

void DelayUs2x(unsigned char t);//函数声明 
void DelayMs(unsigned char t);
/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		     
 //TH0=0x00;	      //给定初值
 //TL0=0x00;
 EA=1;            //总中断打开
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
}
/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{
 unsigned char i;
 Init_Timer0(); //初始化定时器
 while(1)
      {
   frq=0;
   for(i=0;i<60;i++)//播放1s左右一种频率
      {
      DelayMs(10); 
	  }
   frq=100;
   for(i=0;i<60;i++)//播放1s左右另外一种频率
      {  
      DelayMs(10); 
	  }
          
	 }
}
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
 TH0=0xfe;		  //重新赋值 
 TL0=frq;         //低8位值在主程序中不断累加
 
 SPK=!SPK;        //端口电平取反

}
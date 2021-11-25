/*-----------------------------------------------
  名称：遥控器红外解码数码管显示
  公司：上海浩豚电子科技有限公司
  编写：师访
  日期：2009.5
  修改：无
  内容：按配套遥控器上1-9会在数码管上对应显示
------------------------------------------------*/
#include<reg52.h>    //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<stdio.h>
#include<intrins.h>


#define TURE 1
#define FALSE 0


sbit IR=P3^2;  //红外接口标志

unsigned char const dofly[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/******************************************************************/
/*                    变量声明                                    */
/******************************************************************/

unsigned char  irtime;//红外用全局变量

bit irpro_ok,irok;
unsigned char IRcord[4];
unsigned char   irdata[33];

/******************************************************************/
/*                    函数声明                                    */
/******************************************************************/

void Delay(unsigned char mS);
void Ir_work(void);
void Ircordpro(void);

/******************************************************************/
/*                    定时器0中断服务函数                         */
/******************************************************************/

void tim0_isr (void) interrupt 1 using 1//定时器0中断服务函数
{
  irtime++;                             //用于计数2个下降沿之间的时间
}

/******************************************************************/
/*                    外部中断0函数                               */
/******************************************************************/
void ex0_isr (void) interrupt 0 using 0//外部中断0服务函数
{
  static unsigned char  i;             //接收红外信号处理
  static bit startflag;                //是否开始处理标志位

 if(startflag)                         
 {
   
    if(irtime<63&&irtime>=33)//引导码 TC9012的头码，9ms+4.5ms
            i=0;
     
    		irdata[i]=irtime;//存储每个电平的持续时间，用于以后判断是0还是1
    		irtime=0;
    		i++;
   			 if(i==33)
      			{
	  			 irok=1;
				 i=0;
	  			}
          }
	 
  	 else
		{irtime=0;startflag=1;}

}

/******************************************************************/
/*                   定时器0初始化                                */
/******************************************************************/
void TIM0init(void)//定时器0初始化
{

  TMOD=0x02;//定时器0工作方式2，TH0是重装值，TL0是初值
  TH0=0x00; //重载值
  TL0=0x00; //初始化值
  ET0=1;    //开中断
  TR0=1;    
}
/******************************************************************/
/*                   外部中断初始化                               */
/******************************************************************/
void EX0init(void)
{
 IT0 = 1;   //指定外部中断0下降沿触发，INT0 (P3.2)
 EX0 = 1;   //使能外部中断
 EA = 1;    //开总中断
}
/******************************************************************/
/*                    红外键值处理                                */
/******************************************************************/

  void Ir_work(void)//红外键值散转程序
  {
       switch(IRcord[2])//判断第三个数码值
	         {
			 case 0:P0=dofly[1];break;//1 显示相应的按键值
			 case 1:P0=dofly[2];break;//2
			 case 2:P0=dofly[3];break;//3
			 case 3:P0=dofly[4];break;//4
			 case 4:P0=dofly[5];break;//5
			 case 5:P0=dofly[6];break;//6
			 case 6:P0=dofly[7];break;//7
			 case 7:P0=dofly[8];break;//8
			 case 8:P0=dofly[9];break;//9

			 }

		  irpro_ok=0;//处理完成标志

  }
/******************************************************************/
/*                    红外解码函数处理                            */
/******************************************************************/
void Ircordpro(void)//红外码值处理函数
{ 
  unsigned char i, j, k;
  unsigned char cord,value;

  k=1;
  for(i=0;i<4;i++)      //处理4个字节
     {
      for(j=1;j<=8;j++) //处理1个字节8位
         {
          cord=irdata[k];
          if(cord>7)//大于某值为1，这个和晶振有绝对关系，这里使用12M计算，此值可以有一定误差
		    {
             value=value|0x80;
			}
          else 
		    {
             value=value;
			}
          if(j<8)
		    {
			 value=value>>1;
			}
           k++;
         }
     IRcord[i]=value;
     value=0;     
     } irpro_ok=1;//处理完毕标志位置1
    
}




/////////////////////////////////////////////////////////////////

void main(void)
{
 EX0init(); //初始化外部中断
 TIM0init();//初始化定时器

 P2=0x00;//1位数码管全部显示

 while(1)//主循环
   {
    if(irok)                        //如果接收好了进行红外处理
	  {   
	   Ircordpro();
 	   irok=0;
	  }

    if(irpro_ok)                   //如果处理好后进行工作处理，如按对应的按键后显示对应的数字等
	  {
	   Ir_work();
  	  }
   }
}
  
  
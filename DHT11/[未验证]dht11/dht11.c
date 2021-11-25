#include <REGX52.H>
#include <stdio.h>
#include "intrins.h"
#include "codetab.h"
#include "LQ12864.h"

sbit dht11=P2^0;
sbit key1=P0^5;//切换 
sbit key2=P0^6;//+
sbit key3=P0^7;//-
sbit led=P1^7;
sbit beep=P1^6;

unsigned int dht11_data[5],flag_1=0,flag_dec=0,flag_add=0;
unsigned char Tem=0,Hum=0,y,DATA0,HN=0,TemH=25,TemL=17,HumH=28,HumL=22;
unsigned char TemData_shi,TemData_ge,TemData_dec1,TemData_dec2,TemData_dec3;
unsigned char HumData_shi,HumData_ge,HumData_dec1,HumData_dec2,HumData_dec3;
unsigned char read();
void start();
void UartInit(void);
void Delay10ms();
void Delay10us();
void show();
void key();
void Data();
void baojing();
void main()
{
	led=0;
	OLED_Init();
	
	//UartInit();
  while(1)
  {	 
		start();
		dht11_data[0]=read();
		dht11_data[1]=read();
		dht11_data[2]=read();
		dht11_data[3]=read();
		dht11_data[4]=read(); 
		key();
		Data();
		show();
		baojing();
		for(y=0;y<86;y++)
		{
			Delay10ms();
		}
		if(flag_1>=4)
		{
					flag_1=0;
		}
  }
}
void Delay10us()		//@12.000MHz
{
	unsigned char i;
	
		_nop_();
		i = 2;
		while (--i);
}
void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 20;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}

void UartInit(void)		//9600bps@12.000MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void start()
{
	 dht11=1;
	 _nop_();
	 dht11=0;
	 Delay10ms();
	 Delay10ms();
	 dht11=1;
	 Delay10us();
	 Delay10us();
	 Delay10us();
	 while(dht11==0);
	 while(dht11==1);
	 
}
unsigned char read()
{
	unsigned char i,bat=0;
	for(i=0;i<8;i++)
	{
		bat=bat<<1;
		while(dht11==0);
		Delay10us();
		Delay10us();
		Delay10us();
		if(dht11==1)
		{
			while(dht11==1);
			bat|=0x01;
		}
	}
	 return bat;
}
void show()
{		
		OLED_P16x16Ch(0,0,0);//温
		OLED_P16x16Ch(16,0,1);//度
		OLED_P8x16Ch(32,0,26); //:
		OLED_P8x16Strone(40,0,TemData_shi+'0');
		OLED_P8x16Strone(48,0,TemData_ge+'0');
		OLED_P8x16Ch(56,0,14); //.
		OLED_P8x16Strone(64,0,TemData_dec3+'0');
		//OLED_P8x16Strone(72,0,TemData_dec2+'0');
		//OLED_P8x16Strone(80,0,TemData_dec3+'0');
		OLED_P8x16Ch(72,0,95);//摄氏度符
		OLED_P8x16Ch(80,0,35);//C
		if(flag_1==0)
		{
		 	OLED_P16x16Ch(0,2,6);//上阳码
			OLED_P16x16Ch(64,2,3);//下
			OLED_P16x16Ch(0,6,2);//上
			OLED_P16x16Ch(64,6,3);//下
		}
		else if(flag_1==1)
		{	
			OLED_P16x16Ch(0,2,2);//上
			OLED_P16x16Ch(64,2,7);//下阳码
			OLED_P16x16Ch(0,6,2);//上
			OLED_P16x16Ch(64,6,3);//下	
		}
			if(flag_1==2)
		{
			OLED_P16x16Ch(0,2,2);//上
			OLED_P16x16Ch(64,2,3);//下
		 	OLED_P16x16Ch(0,6,6);//上阳码
			OLED_P16x16Ch(64,6,3);//下
		}
		else if(flag_1==3)
		{	
			OLED_P16x16Ch(0,2,2);//上
			OLED_P16x16Ch(64,2,3);//下
			OLED_P16x16Ch(0,6,2);//上
			OLED_P16x16Ch(64,6,7);//下阳码
			
		}
		OLED_P8x16Ch(16,2,26); //：
		OLED_P8x16Strone(24,2,(TemH/10)+'0');
		OLED_P8x16Strone(32,2,(TemH%10)+'0');
		OLED_P8x16Ch(40,2,95);//摄氏度符
		OLED_P8x16Ch(48,2,35);//C
		OLED_P8x16Ch(80,2,26); //：
		OLED_P8x16Strone(88,2,(TemL/10)+'0');
		OLED_P8x16Strone(96,2,(TemL%10)+'0');
		OLED_P8x16Ch(104,2,95);//摄氏度符
		OLED_P8x16Ch(112,2,35);//C

		OLED_P16x16Ch(0,4,5);//湿
		OLED_P16x16Ch(16,4,1);//度
		OLED_P8x16Ch(32,4,26); //：
		OLED_P8x16Strone(40,4,HumData_shi+'0');
		OLED_P8x16Strone(48,4,HumData_ge+'0');
		OLED_P8x16Ch(56,4,14); //.	
		OLED_P8x16Strone(64,4,HumData_dec1+'0');
		OLED_P8x16Strone(72,4,HumData_dec2+'0');
		OLED_P8x16Strone(80,4,HumData_dec3+'0');
		OLED_P8x16Ch(88,4,5);//%
		OLED_P8x16Strone(96,4,flag_1+'0');
	
		OLED_P8x16Ch(16,6,26); //：
		OLED_P8x16Strone(24,6,(HumH/10)+'0');
		OLED_P8x16Strone(32,6,(HumH%10)+'0');
		OLED_P8x16Ch(40,6,5);//%	
		OLED_P8x16Ch(80,6,26); //：
		OLED_P8x16Strone(88,6,(HumL/10)+'0');
		OLED_P8x16Strone(96,6,(HumL%10)+'0');
		OLED_P8x16Ch(104,6,5);//%

			
		if(DATA0==dht11_data[4])
			OLED_P8x16Strone(112,0,'Y'); 
		else 
			OLED_P8x16Strone(112,0,'N');
}
void key()
{
	if(key1==0)	
	{		
		 
		Delay10ms();   //消除抖动
		if(key1==0)	 //再次判断按键是否按下
		{	
			led=1;
			flag_1++;
			
		} 	  
		while(!key1);//检测按键是否松开
		if(flag_1==4)
		{
			flag_1=0;
		}	 
	}
	if(key2==0)	
	{
		Delay10ms();   //消除抖动
		if(key2==0)	 //再次判断按键是否按下
		{	
			led=1;
			flag_add=1;		  
		}
		while(!key2);//检测按键是否松开
	}
	if(key3==0)	
	{
		Delay10ms();   //消除抖动
		if(key3==0)	 //再次判断按键是否按下
		{
			led=1;
			flag_dec=1;		
		}
		while(!key3);	 //检测按键是否松开
	}
}
void Data()
{
	if(flag_dec==1)
	{
		if(flag_1==0)
		{
			TemH=TemH-1;
			flag_dec=0;
		}
		else if(flag_1==1)
		{
			TemL=TemL-1;
			flag_dec=0;
		}
		else if(flag_1==2)
		{
			HumH=HumH-1;
			flag_dec=0;
		}
		else if(flag_1==3)
		{
			HumL=HumL-1;
			flag_dec=0;
		}			
	}
	if(flag_add==1)
	{
		if(flag_1==0)
		{
			TemH=TemH+1;
			flag_add=0;
		}
		else if(flag_1==1)
		{
			TemL=TemL+1;
			flag_add=0;
		}
		else if(flag_1==2)
		{
			HumH=HumH+1;
			flag_add=0;
		}
		else if(flag_1==3)
		{
			HumL=HumL+1;
			flag_add=0;
		}	
	}
	 TemData_shi=dht11_data[2]/10;
	 TemData_ge=dht11_data[2]%10;
	 TemData_dec1=dht11_data[3]/100;
	 TemData_dec2=dht11_data[3]%100/10;
	 TemData_dec3=dht11_data[3]%10;
	 Tem=dht11_data[2];

	 HumData_shi=dht11_data[0]/10;
	 HumData_ge=dht11_data[0]%10;
	 HumData_dec1=dht11_data[1]/100;
	 HumData_dec2=dht11_data[1]%100/10;
	 HumData_dec3=dht11_data[1]%10;
	 Hum=dht11_data[0];

	 DATA0=dht11_data[0]+dht11_data[1]+dht11_data[2]+dht11_data[3];
}
void baojing()
{
	if((Tem<=TemL)||(Tem>=TemH)||(Hum<=HumL)||(Hum>=HumH))
	{
		beep=0;
		led=1;
	}
	else
	{
		beep=1;
		led=0;
	}

}
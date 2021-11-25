/************************************说明***************************************
程序运行时 会对模块进行预热 保证读取第一个数值的精确
预热时间大概为4秒左右
程序初始化时将会提示你设置最大温湿度 
H1  最高温度   L1   最低温度
H2  最高湿度   L2   最低湿度
按钮K1温度加    按钮K2温度减
设置完成后  按K3   即确定按钮 开始监控报警   
																									（适用于吉农51单片机开发板）
                                    2016-12-29----------------------------SWorld
********************************************************************************/
#include <reg52.h>  

#define OK 1 
#define ERROR 0  
#define NUMBER  20  
#define SIZE  5 


/*-----------------------------显示部分接线方法-------------------------------*/
#define GPIO_DIG P0
sbit WEC=P2^3;              //段选
sbit DUC=P2^2;  						//位选

/*----------------------------模块引脚连接-------------------------------------*/
sbit dht11 = P2^0;  				//dht 接口    只要接一个就行   接dht11   data0接口  NC不用管

/*-----------------------------按键引脚方法------------------------------------*/
sbit add=P2^5;								//增加    连接K2
sbit sub=P2^4;								//减少    连接K1
sbit ok=P2^6;									//确定    连接K3

/*----------------------------报警引脚连接-------------------------------------*/
sbit bell=P2^7;								//蜂鸣器接口  连接蜂鸣器

/*------------------------------全局变量---------------------------------------*/
unsigned char flag;   
/*---------------分别代表数码管上的0~9共10位数以及字母L、H----------------------*/
unsigned char code array[12]= { 
         0x3f,0x06,0x5b,0x4f,0x66, 
         0x6d,0x7d,0x07,0x7f,0x6f,0x38,0x76												//L  H
         }; 

unsigned char DisplayData[8];																 //用来存放要显示的8位数的值
unsigned int HTemp,LTemp,HHumi,LHumi,setok;			         		 //用来存放最大温湿度  以及是否设置好温湿度		 
int temp_value, humi_value;                               	 //温湿度数值存放
unsigned char status; 
unsigned char value_array[5]; 
				 
				 
/*------------------------------函数声明---------------------------------------*/
void Delay_1ms(unsigned int ms); 
unsigned char ReadTempAndHumi(void);  
void InitTime(void); 
void Delay_1ms(unsigned int ms); 
void SMG_Display(unsigned int value,unsigned int way ) ;       //显示部分
unsigned char ReadValue(void); 
				 



/*------------------------------延时函数
				  延时1ms
				 ---------------------------------------*/
void Delay_1ms(unsigned int ms) 
{ 
	 unsigned int x, y; 
	 for(x = ms; x > 0; x--) 
	 { 
		for(y = 124; y > 0; y--); 
	 } 
} 


/*------------------------------延时函数
			  延时10ns
				---------------------------------------*/
void  Delay_10us(void) 
{ 
	 unsigned char  i; 
			i--; 
			i--; 
			i--; 
			i--; 
			i--; 
			i--; 
}  


/*------------------------------读取模块数值
				
					---------------------------------------*/
unsigned char ReadValue(void) 
{ 
	 unsigned char count, value = 0, i; 
	 status = OK;   
	 for(i = 8; i > 0; i--) 
	 { 
			value <<= 1; 
			count = 0; 
			while(dht11 == 0 && count++ < NUMBER); 
			if(count >= NUMBER) 
			{ 
			 status = ERROR;
			 return 0;    
			} 
			Delay_10us(); 
			Delay_10us(); 
			Delay_10us(); 
		if(dht11 != 0) 
		{ 
			 value++; 
			 while(dht11 != 0 && count++ < NUMBER) 
			 { 
					dht11 = 1; 
			 } 
			 if(count >= NUMBER) 
			 { 
					status = ERROR;  
					return 0; 
			 }  
		} 
	 }  
	 return (value); 
} 

unsigned char ReadTempAndHumi(void) 
{  
	 unsigned char i = 0, check_value = 0,count = 0; 
	 EA = 0; 
	 dht11 = 0;     
	 Delay_1ms(20);   
	 dht11 = 1;     
	 Delay_10us(); 
	 Delay_10us(); 
	 Delay_10us(); 
	 Delay_10us();  
	 if(dht11 != 0)    
	 { 
		EA = 1; 
		return ERROR; 
	 } 
	 else 
	 { 
		while(dht11 == 0 && count++ < NUMBER);   
		if(count >= NUMBER)  
		{ 
		 dht11 = 1; 
		 EA = 1; 
		 return ERROR;   
		} 
		count = 0; 
		dht11 = 1;
		while(dht11 != 0 && count++ < NUMBER); 
		if(count >= NUMBER) 
		{ 
		 dht11 = 1; 
		 EA = 1; 
		 return ERROR;  
		}  
			 for(i = 0; i < SIZE; i++) 
		{ 
		 value_array[i] = ReadValue(); 
		 if(status == ERROR)
		 { 
			dht11 = 1; 
			EA = 1;    
			return ERROR;  
		 } 
		 if(i != SIZE - 1)  
		 { 
			check_value += value_array[i];  
		 } 
		}
		if(check_value == value_array[SIZE - 1]) 
		{ 
		 humi_value = value_array[0] * 10; 
		 temp_value = value_array[2] * 10; 
		 dht11 = 1; 
		 EA = 1; 
		 return OK;   
		} 
		else 
		{ 
		 EA = 1; 
		 return ERROR; 
		} 
	 }         
} 

/**************************************************************
键盘扫描子程序
**************************************************************/
unsigned char Key_Scan()
{
	unsigned char keyValue = 0 , i; //保存键值

	//--检测按键1--//
	if (ok != 1)		//检测按键K3是否按下
	{
		Delay_1ms(10);	//消除抖动

		if (ok != 1)	//再次检测按键是否按下
		{
			keyValue = 3;
			i = 0;
			while ((i<50) && (ok != 1))	 //检测按键是否松开
			{
				Delay_1ms(10);
				i++;
			}
		}
	}
		//--检测按键1--//
	if (add != 1)		//检测按键K1是否按下
	{
		Delay_1ms(10);	//消除抖动

		if (add!= 1)	//再次检测按键是否按下
		{
			keyValue = 2;
			i = 0;
			while ((i<50) && (add != 1))	 //检测按键是否松开
			{
				Delay_1ms(10);
				i++;
			}
		}
	}
		//--检测按键1--//
	if (sub != 1)		//检测按键K2是否按下
	{
		Delay_1ms(10);//消除抖动

		if (sub!= 1)	//再次检测按键是否按下
		{
			keyValue = 1;
			i = 0;
			while ((i<50) && (sub != 1))	 //检测按键是否松开
			{
				Delay_1ms(10);
				i++;
			}
		}
	
	}

	return keyValue;   //将读取到键值的值返回
}


/*******************************************************************************
* 函 数 名         : DigDisplay
* 函数功能		     : 使用数码管显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		WEC=1;DUC=0;
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				GPIO_DIG=0x7F; break;//显示第0位
			case(1):
				GPIO_DIG=0xBF; break;//显示第1位
			case(2):
				GPIO_DIG=0xDF; break;//显示第2位
			case(3):
				GPIO_DIG=0xEF; break;//显示第3位
			case(4):
				GPIO_DIG=0xF7; break;//显示第4位
			case(5):
				GPIO_DIG=0xFB; break;//显示第5位
			case(6):
				GPIO_DIG=0xFD; break;//显示第6位
			case(7):
				GPIO_DIG=0xFE; break;//显示第7位	
		}
		WEC=0;DUC=1;
		GPIO_DIG=DisplayData[i];//发送段码
		j=50;						 //扫描间隔时间设定
		while(j--);	
		GPIO_DIG=0x00;//消隐
	}
}
	

/*------------------------------主函数
		主函数共分为5部分，有switch语句执行相关操作
		case 1：设置最高温度，完成设置后跳到下一循环
		case 2：设置最低温度，完成设置后跳到下一循环
		case 3：设置最高湿度，完成设置后跳到下一循环
		case 4：设置最低湿度，完成设置后跳到下一循环
		case 5：温湿度监控主循环，当低于后者超过预设值，
						触发警报。所读取的数值同时显示于数码管
				---------------------------------------*/				 
void main(void) 
{ 
	unsigned char mark = 0; 
	Delay_1ms(1000); 
	ReadTempAndHumi(); 
	Delay_1ms(3000); 
	InitTime(); 
	WEC=0;DUC=0;
	HTemp=30,LTemp=20;
	HHumi=100,LHumi=20;
	bell=1,setok=1;
	while(1) 
	{ 
		switch(setok)
		{
			case 1:
				DisplayData[7]=array[11];	
        DisplayData[6]=array[1];
			  DisplayData[4]=array[HTemp/10];
			  DisplayData[3]=array[HTemp%10];
				switch(Key_Scan())
				{
					case 1:
						HTemp-=2;
						break;
					case 2:
						HTemp+=2;
						break;
					case 3:
						setok=2;
						break;
				}
				break;
			case 2:
				DisplayData[7]=array[10];	
        DisplayData[6]=array[1];
		   	DisplayData[4]=array[LTemp/10];
			  DisplayData[3]=array[LTemp%10];
				switch(Key_Scan())
				{
					case 1:
						LTemp-=2;
						break;
					case 2:
						LTemp+=2;
						break;
					case 3:
						setok=3;
						break;
				}
				break;
			case 3:
				DisplayData[7]=array[11];	
        DisplayData[6]=array[2];
			  DisplayData[4]=array[HHumi/100];
			  DisplayData[3]=array[HHumi%100/10];
			  DisplayData[2]=array[HHumi%10];
				switch(Key_Scan())
				{
					case 1:
						HHumi-=2;
						break;
					case 2:
						HHumi+=2;
						break;
					case 3:
						setok=4;
						break;
				}
				break;
			case 4:
				DisplayData[7]=array[10];	
        DisplayData[6]=array[2];
			  DisplayData[4]=array[LHumi/100];
		   	DisplayData[3]=array[LHumi%100/10];
			  DisplayData[2]=array[LHumi%10];
				switch(Key_Scan())
				{
					case 1:
						LHumi-=2;
						break;
					case 2:
						LHumi+=2;
						break;
					case 3:
						setok=5;
						break;
				}
				break;
			case 5:
		  DisplayData[4]=0x00;
			if(flag == 30) 
			{ 
				flag = 0; 
				mark++; 
				ReadTempAndHumi(); 
				if(temp_value<LTemp*10||temp_value>HTemp*10||humi_value<LHumi*10||humi_value>HHumi*10)
				{
					bell=0;
				}
				else
				{
					bell=1;
				}
			} 
			SMG_Display(temp_value,0); 
			SMG_Display(humi_value,1); 
			break;
	 }
		DigDisplay();
 } 
} 

/*------------------------------定时器初始化
						---------------------------------------*/
void InitTime(void) 
{ 
	TH0 = (unsigned char)((65535U - 50000) >> 8); 
	TL0 = (unsigned char)(65535U - 50000) ; 
	TMOD = 0X01; 
	TR0 = 1; 
	ET0 = 1; 
	EA = 1; 
}  


/*------------------------------数值转换
			将读取到的数值转换为数码管可显示的数值
									---------------------------------------*/
void SMG_Display(unsigned int value,unsigned int way ) 
{ 
	 unsigned char ge, bai, shi; 
	 ge = value % 10; 
	 shi = value % 100 / 10; 
	 bai = value % 1000 / 100; 
   if(way==0)
	 {		 
	   DisplayData[7]=array[bai];	
     DisplayData[6]=array[shi]|0x80;			
     DisplayData[5]=array[ge];	
	 }
	 else
	 {
		 DisplayData[3]=array[bai];	
     DisplayData[2]=array[shi]|0x80;			
     DisplayData[1]=array[ge];	
	 }
}  

/*------------------------------定时器0
										---------------------------------------*/
void timer(void) interrupt 1 
{ 
	 TH0 = (unsigned char)((65535 - 50000) >> 8);  
	 TL0 = (unsigned char)(65535 - 50000); 
	 flag++; 
} 
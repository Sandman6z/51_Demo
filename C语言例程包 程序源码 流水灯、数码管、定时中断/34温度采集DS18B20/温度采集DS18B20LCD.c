/********************************************************************
* 文件名  ： 温度采集DS18B20.c
* 描述    :  该文件实现了用温度传感器件DS18B20对温度的采集，并在数码管上显示出来。
* 创建人  ： 东流，2009年4月10日
* 版本号  ： 2.0
***********************************************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int

#define jump_ROM 0xCC
#define start 0x44
#define read_EEROM 0xBE

sbit DQ = P2^3;            //DS18B20数据口

unsigned char TMPH,TMPL; 

uchar code table[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
/********************************************************************
* 名称 : delay()
* 功能 : 延时,延时时间大概为140US。
* 输入 : 无
* 输出 : 无
***********************************************************************/

void delay_1()
{
	int i,j;
	for(i=0; i<=10; i++)
	for(j=0; j<=2; j++)
;
}

/********************************************************************
* 名称 : delay()
* 功能 : 延时函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void delay(uint N)
{
	int i;
	for(i=0; i<N; i++)
	;
}

/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay_1ms(uint i)//1ms延时
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}
/********************************************************************
* 名称 : Reset()
* 功能 : 复位DS18B20
* 输入 : 无
* 输出 : 无
***********************************************************************/
uchar Reset(void)
{
	uchar deceive_ready;
	DQ = 0;
	delay(29);
	DQ = 1;
	delay(3);
	deceive_ready = DQ;
	delay(25);
	return(deceive_ready);
}

/********************************************************************
* 名称 : read_bit()
* 功能 : 从DS18B20读一个位值
* 输入 : 无
* 输出 : 从DS18B20读出的一个位值
***********************************************************************/
uchar read_bit(void)
{
	uchar i;
	DQ = 0;
	DQ = 1;
	for(i=0; i<3; i++);
	return(DQ);
}

/********************************************************************
* 名称 : write_bit()
* 功能 : 向DS18B20写一位
* 输入 : bitval（要对DS18B20写入的位值）
* 输出 : 无
***********************************************************************/
void write_bit(uchar bitval)
{
DQ=0;if(bitval==1)
DQ=1;
delay(5);
DQ=1;
}

/********************************************************************
* 名称 : read_byte()
* 功能 : 从DS18B20读一个字节
* 输入 : 无
* 输出 : 从DS18B20读到的值
***********************************************************************/
uchar read_byte(void)
{
	uchar i,m,receive_data;
	m = 1;
	receive_data = 0;
	for(i=0; i<8; i++)
	{
		if(read_bit())
		{
			receive_data = receive_data + (m << i);
		}
		delay(6);
	}
	return(receive_data);
}

/********************************************************************
* 名称 : write_byte()
* 功能 : 向DS18B20写一个字节
* 输入 : val（要对DS18B20写入的命令值）
* 输出 : 无
***********************************************************************/
void write_byte(uchar val)
{
	uchar i,temp;
	for(i=0; i<8; i++)
	{
		temp = val >> i;
		temp = temp & 0x01;
		write_bit(temp);
		delay(5);
	}
}


/********************************************************************
* 名称 : Main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void main()
{
	float tt;
	uint temp;
	P2 = 0x00;
	while(1)
	{
		Reset();
		write_byte(jump_ROM);
		write_byte(start);
		Reset();
		write_byte(jump_ROM);
		write_byte(read_EEROM);
		TMPL = read_byte();
		TMPH = read_byte();
		temp = TMPL / 16 + TMPH * 16;
		P0 = table[temp/10%10]&0xef;
		P2 = 6;
		Delay_1ms(5);
		P0 = table[temp%10];
		P2 = 7;
		Delay_1ms(5);
		P1=B11111111;
	}
}
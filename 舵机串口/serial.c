#include <STC15F2K60S2.H>

sbit SEV_PWM = P0^0;
sbit SEH_PWM = P2^6;
//sbit VCC = P0^1;
//sbit GND = P0^2;

unsigned char count = 0;
unsigned char SEV_count = 15;
unsigned char SEH_count = 15;

void Com_Init()
{
	IP =  0x08;
	PCON &= 0x7F;
	TMOD &= 0x00;
	TMOD |= 0x21;
	SCON = 0x50;
	TH1 = 0xfd;
	TL1 = 0xfd;
	ES = 1;
	ET1 = 0;
	TR1 = 1;
	
	TH0 = 0xff;
	TL0 = 0xa4;
	
	ET0 = 1;
	TR0 = 1;	
}
void Time0_Init() interrupt 1
{
	TR0 = 0;
	TH0 = 0xff;
	TL0 = 0xa4;
	
	if(count <= SEH_count)
	{
		SEH_PWM = 1;
	}
	else
	{
		SEH_PWM = 0;
	}
	if(count <= SEV_count)
	{
		SEV_PWM = 1;
	}
	else
	{
		SEV_PWM = 0;
	}
	count++;
	if(count >= 200)
	{
		count = 0;
	}
	TR0 = 1;
}

void main()
{
//	GND = 0;
//	VCC = 1;
	Com_Init();
	while(1)
	{
		;
	}
}

void uart_ser() interrupt 4
{
	unsigned char command;
	if(RI == 0)
		return;
	ES = 0;
	RI = 0;
	command = SBUF;
	
	switch(command)
	{
		case 'f':
		{
			SEV_count++;
			if(SEV_count >= 25)
				SEV_count = 25;
			count = 0;
			break;
		}
		case 'g':
		{
			SEV_count--;
			if(SEV_count <= 5)
				SEV_count = 5;
			count = 0;
			break;
		}
		case 'h':
		{
			SEV_count++;
			if(SEH_count >= 25)
				SEH_count = 25;
			count = 0;
			break;
		}
//		case 'g':
//		{
//			SEH_count--;
//			if(SEH_count <= 5)
//				SEH_count = 5;
//			count = 0;
//			break;
//		}
//		case 'k':
//		{
//			SEH_count = 15;
//			SEV_count = 15;
//			count = 0;
//			break:
//		}
//		default:
//		{
//			break:
//		}
	}
	ES = 1;
}
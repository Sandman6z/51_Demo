#include <reg51.h>
#include <intrins.h>                        //����_nop_( )�պ���ָ���ͷ�ļ�

#define uchar unsigned char
#define uint unsigned int
#define out P0

sbit RS=P2^0;                                    //λ����
sbit RW=P2^1;                                    //λ����
sbit E=P2^2; 

void lcd_initial(void);                          //λ����void lcd _initial(void);                                        //LCD��ʼ������
void check_busy(void);                           //���æ��־����
void write_command(uchar com);                   //д�����
void write_data(uchar dat);                      //д���ݺ���
void string(uchar ad ,uchar *s);
void delay(uint);                                //��ʱ����

unsigned char key_scan()
{
        unsigned char key_temp0,key_temp1;
        unsigned char key_num=0;
        P1=0x0f;
        key_temp0=P1;
        if(key_temp0!=0x0f)
        {
                delay(5);
                key_temp0=P1;
                if(key_temp0!=0x0f)
                {
                        P1=0xf0;
                        key_temp1=P1;
                        if(key_temp0==0x0e)
                        {
                                switch(key_temp1)
                                {
                                        case 0xe0: key_num=4;break;
                                        case 0xd0: key_num=3;break;
                                        case 0xb0: key_num=2;break;
                                        case 0x70: key_num=1;break;
                                        default:key_num=0;break;
                                }
                        }
                        else if(key_temp0==0x0d)
                        {
                                switch(key_temp1)
                                {
                                        case 0xe0: key_num=8;break;
                                        case 0xd0: key_num=7;break;
                                        case 0xb0: key_num=6;break;
                                        case 0x70: key_num=5;break;
                                        default:key_num=0;break;
                                }
                        }
                        else if(key_temp0==0x0b)
                        {
                                switch(key_temp1)
                                {
                                        case 0xe0: key_num=12;break;
                                        case 0xd0: key_num=11;break;
                                        case 0xb0: key_num=10;break;
                                        case 0x70: key_num=9;break;
                                        default:key_num=0;break;
                                }
                        }
                        else if(key_temp0==0x07)
                        {
                                switch(key_temp1)
                                {
                                        case 0xe0: key_num=16;break;
                                        case 0xd0: key_num=15;break;
                                        case 0xb0: key_num=14;break;
                                        case 0x70: key_num=13;break;
                                        default:key_num=0;break;
                                }
                        }
                }
        }
return key_num;
}


void main(void)                         //������
{
        unsigned char key_num;
        lcd_initial( );                        //���ö�LCD��ʼ������
   do
   {
                        key_num=key_scan();
                        string(0x82,"Yu Wang wang");                //��ʾ�ĵ�1���ַ���
                  switch(key_num)
                        {
                                case 1 :string(0xC8,"1");  break;
                                case 2 :string(0xC8,"2");  break;
                                case 3 :string(0xC8,"3");  break;
                                case 4 :string(0xC8,"4");  break;
                                case 5 :string(0xC8,"5");  break;
                                case 6 :string(0xC8,"6");  break;
                                case 7 :string(0xC8,"7");  break;
                                case 8 :string(0xC8,"8");  break;
                                case 9 :string(0xC8,"9");  break;
                                case 10:string(0xC8,"10"); break;
                                case 11:string(0xC8,"11"); break;
                                case 12:string(0xC8,"12"); break;
                                case 13:string(0xC8,"13"); break;
                                case 14:string(0xC8,"14"); break;
                                case 15:string(0xC8,"15"); break;
                                case 16:string(0xC8,"16"); break;
                        }        
                        delay(100);                         //��ʱ
                        write_command(0x01);                //д����������
                        delay(1);                        //��ʱ
         }while(1);
}
void delay(uint j)                        //1ms��ʱ�ӳ���
{
        uchar i=250;
        for(;j>0;j--)
{
                while(--i);
                i=249;
                while(--i);
                i=250;
        }
}
void check_busy(void)                        //���æ��־����
{
        uchar dt;
        do
        {
                dt=0xff;
                E=0;
                RS=0;        
                RW=1;
E=1;
dt=out;
}while(dt&0x80);
E=0;
}
void write_command(uchar com)                 //д�����
{
check_busy();
E=0;
RS=0;
RW=0;
out=com;
E=1;
_nop_( );
E=0;
delay(1);
}
void write_data(uchar dat)                                 //д���ݺ���
{
        check_busy();
        E=0;
        RS=1;
        RW=0;
        out=dat;
        E=1;
        _nop_();
        E=0;
        delay(1);        
}
void LCD_initial(void)                         //Һ����ʾ����ʼ������
{
write_command(0x38);        //д������0x38��8λ������ʾ��5��7�����ַ�
write_command(0x0C);        //д������0x0C����������ʾ�����أ��޺ڿ�
write_command(0x06);        //д������0x06���������

write_command(0x01);                         //д������0x01������
delay(1);
}
void string(uchar ad,uchar *s)        //�����ʾ�ַ����ĺ���
{
write_command(ad);
while(*s>0)
{
write_data(*s++);                        //����ַ�������ָ����1
delay(50);
}
}
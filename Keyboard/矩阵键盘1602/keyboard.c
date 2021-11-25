#include <reg51.h>
#include <intrins.h>                        //包含_nop_( )空函数指令的头文件

#define uchar unsigned char
#define uint unsigned int
#define out P0

sbit RS=P2^0;                                    //位变量
sbit RW=P2^1;                                    //位变量
sbit E=P2^2; 

void lcd_initial(void);                          //位变量void lcd _initial(void);                                        //LCD初始化函数
void check_busy(void);                           //检查忙标志函数
void write_command(uchar com);                   //写命令函数
void write_data(uchar dat);                      //写数据函数
void string(uchar ad ,uchar *s);
void delay(uint);                                //延时函数

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


void main(void)                         //主函数
{
        unsigned char key_num;
        lcd_initial( );                        //调用对LCD初始化函数
   do
   {
                        key_num=key_scan();
                        string(0x82,"Yu Wang wang");                //显示的第1行字符串
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
                        delay(100);                         //延时
                        write_command(0x01);                //写入清屏命令
                        delay(1);                        //延时
         }while(1);
}
void delay(uint j)                        //1ms延时子程序
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
void check_busy(void)                        //检查忙标志函数
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
void write_command(uchar com)                 //写命令函数
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
void write_data(uchar dat)                                 //写数据函数
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
void LCD_initial(void)                         //液晶显示器初始化函数
{
write_command(0x38);        //写入命令0x38：8位两行显示，5×7点阵字符
write_command(0x0C);        //写入命令0x0C：开整体显示，光标关，无黑块
write_command(0x06);        //写入命令0x06：光标右移

write_command(0x01);                         //写入命令0x01：清屏
delay(1);
}
void string(uchar ad,uchar *s)        //输出显示字符串的函数
{
write_command(ad);
while(*s>0)
{
write_data(*s++);                        //输出字符串，且指针增1
delay(50);
}
}
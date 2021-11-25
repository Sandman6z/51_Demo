/*-----------------------------------------------
  名称：单个共阳数码管指示逻辑电平
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过循环检测P3.2口电平输入值，然后用数码管输出"H" or "L"，
        表示该端口现在连接的是高电平还是低电平
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，
                  //头文件包含特殊功能寄存器的定义

sbit IO_IN=P3^2;  //定义IO 信号输入端

/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
                  

while (1)         //主循环
  {
  if(IO_IN==1)//如果端口检测到1表示高电平
    P1=0x89;  //"H"
  else
    P1=0xc7;  //"L"
	          //否则表示低电平，这里使用 条件语句 if 。。。else 。。。 
              //主循环中添加其他需要一直工作的程序
  }
}

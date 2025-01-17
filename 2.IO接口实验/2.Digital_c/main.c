#include <REGX52.H>
#include <INTRINS.H>
unsigned char code ShowNum[]={0xa4,0xc0,0xa4,0x99,0xf9,0xc0,0xa4,0x99};//将日期20241024转为8个十六进制数字进行编码
/*
数码表编码对应关系：
  0: 0xC0
  1: 0xF9
  2: 0xA4
  3: 0xB0
  4: 0x99
  5: 0x92
  6: 0x82
  7: 0xF8
  8: 0x80
  9: 0x90
*/
void delay_ms(unsigned int time);

void main()
{
	unsigned int j;
	P2 = 0x01;  // 初始化P2口
	while(1)
	{
		for(j = 0; j < 8; j++)
		{
			P2 = 0x01;  // 重新初始化P2，开始选通第一个数码管
			P2 = _crol_(P2, j);  // 循环左移，选通相应的数码管
			P3_7 = 1;  // 产生锁存信号，高电平
			P3_7 = 0;  // 锁存信号恢复为低电平

			P2 = ShowNum[j];  // 显示编码，输出到P2口
			P3_6 = 1;  // 产生显示信号，高电平
			P3_6 = 0;  // 显示信号恢复为低电平
			delay_ms(1);  // 短延时实现视觉暂留效果
		}
	}
}

void delay_ms(unsigned int time)
{
	unsigned int i, j;
	for (i = 0; i < time; i++) 
	{
		for (j = 0; j < 123; j++) 
		{
			// 空循环，用于产生延时
		}
	}
}

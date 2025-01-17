#include <REGX52.H>
#include <INTRINS.H>
unsigned char code ShowNum[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90, // 9
    0x88, // A
    0x83, // B
    0xC6, // C
    0xA1, // D
    0x86, // E
    0x8E  // F
};
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
unsigned int button_cnt = 0;

void delay_ms(unsigned int time);
sbit key = P3^2;

void int0() interrupt 0 {
    if (!key) {
        button_cnt += 1;
        button_cnt = button_cnt & 0x0F;  // 保证计数在0-15之间循环
        delay_ms(100);
    }
}
void main()
{
	unsigned int j;
	P2 = 0x01;  // 初始化P2口
	
	EA = 1; 
    IT0 = 1;  
    EX0 = 1;  
	
	while(1)
	{
		for(j = 0; j < 8; j++)
		{
			P2 = 0x01;  // 重新初始化P2，开始选通第一个数码管
			P2 = _crol_(P2, j);  // 循环左移，选通相应的数码管
			P3_7 = 1;  // 产生锁存信号，高电平
			P3_7 = 0;  // 锁存信号恢复为低电平

			P2 = ShowNum[button_cnt];  // 显示编码，输出到P2口
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

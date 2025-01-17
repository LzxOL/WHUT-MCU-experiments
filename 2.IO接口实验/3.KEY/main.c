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
unsigned char code KeyNum[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//将日期20241024转为8个十六进制数字进行编码
//0到9、及A到F对应的数码管编码
//矩阵键盘对应行：

sbit KeyRow1=P1^7;
sbit KeyRow2=P1^6;
sbit KeyRow3=P1^5;
sbit KeyRow4=P1^4;

void delay_ms(unsigned int time);
void key_scan(void);
void main()
{
	while(1){
			key_scan();
			delay_ms(1);
		}
}

void delay_ms(unsigned int time){
		unsigned int i, j;
		for (i = 0; i < time; i++) {
        for (j = 0; j < 123; j++) {
					//12MHZ执行一个语句123次大约为1ms
            // 空循环，用于产生延时
        }
    }
}
void key_scan(void){
	//数码管显示不需要进行按键消抖，检测到对应电平对最终结果无影响
	unsigned char i;
	P1=0xf0;
	//0xf0对应1111 0000
	if((P1&0xf0)!=0xf0){
		P3_7=0;
		P3_6=0;
		P1=0xfe;
		P2=0xff;
		P3_7 = 1;
		
	}
	if((P1&0xf0)!=0xf0)//若p1端口的高四位不全为1，即有按键按下
	{
		P3_7=0;
		P3_6=0;//两个置零，用来关闭控制信号
		P1=0xfe;//设置 P1 为 1111 1110，准备进行键盘扫描
		P2=0xff;//设置 P2 为 1111 1111，控制显示位置，ff代表8个数码管均进行相关内容显示
		P3_7=1;
		P3_7=0;
		for(i=0;i<4;i++)
		{
			P1=_cror_(0xf7,i);//循环右移，扫描下一列 1111 0111
			if(KeyRow1==0)
			{
				P2=KeyNum[i];
				P3_6=1;
				P3_6=0;
			}
			if(KeyRow2==0)
			{
				P2=KeyNum[i+4];
				P3_6=1;
				P3_6=0;
			}
			if(KeyRow3==0)
			{
				P2=KeyNum[i+8];
				P3_6=1;
				P3_6=0;
			}
			if(KeyRow4==0)
			{
				P2=KeyNum[i+12];
				P3_6=1;
				P3_6=0;
			}
		}
	}
	
}


#include <REGX52.H>
#include <INTRINS.H>

unsigned int i=0;
void delay_ms(unsigned int time);
void main()
{
	TMOD=0x01;
	TH0=0x4c;
	TL0=0x00;
	EA=1;
	ET0=1;
	TR0=1;
		while(1)
	{

	}
}

void timer() interrupt 1{
	TH0=0x4c;
	TL0=0x00;
	P0=_crol_(0xfe,i);
	i++;
	TR0=1;
}
void delay_ms(unsigned int time){
		unsigned int i, j;
		for (i = 0; i < time; i++) {
        for (j = 0; j < 123; j++) {
					
            // 空循环，用于产生延时
        }
    }
}

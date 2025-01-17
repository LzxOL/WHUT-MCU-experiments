#include <REGX52.H>
#include <INTRINS.H>
unsigned char code KeyNum[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
// 0到9、及A到F对应的数码管编码
// 矩阵键盘对应行：
unsigned char position[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

sbit KeyRow1 = P1 ^ 7;
sbit KeyRow2 = P1 ^ 6;
sbit KeyRow3 = P1 ^ 5;
sbit KeyRow4 = P1 ^ 4;

void delay_ms(unsigned int time);
void test001(void);
void test002(void);
void display_digit(int position, int digit);
int queue_record=0;
int key_num;
int num_record[8]=0;
int i;
int show;

void key_scan(void);
void main()
{
		key_num=0;
    while (1)
    {
        key_scan();
			display_digit(1,key_num);
		for(show=0;show<queue_record;show++){
			
					display_digit(show,num_record[show]);
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
            // 12MHZ执行一个语句123次大约为1ms
            // 空循环，用于产生延时
        }
    }
}

void key_scan(void){
	//key_num=0;
	//数码管显示不需要进行按键消抖，检测到对应电平对最终结果无影响
	P1=0xf0;
	if(queue_record>8)
			queue_record=0;
	if((P1&0xf0)!=0xf0)//若p1端口的高四位不全为1，即有按键按下
	{
		P1=0xfe;//设置 P1 为 1111 1110，准备进行键盘扫描
		for(i=0;i<4;i++)
		{
			P1=_cror_(0xf7,i);//循环右移，扫描下一列
			if(KeyRow1==0)
			{	
				delay_ms(100);
				if(KeyRow1==0){
					key_num=i;
					num_record[queue_record++]=i;
				}
			}
			if(KeyRow2==0)
			{
				delay_ms(100);
				if(KeyRow2==0){
					key_num=i+4;
					num_record[queue_record++]=i+4;
				}
			}
			if(KeyRow3==0)
			{
				delay_ms(100);
					if(KeyRow3==0){
					key_num=i+8;
					num_record[queue_record++]=i+8;
					}
			}
			if(KeyRow4==0)
			{
				delay_ms(100);
				if(KeyRow4==0){
					key_num=i+8;
				num_record[queue_record++]=i+12;
				}
			}
		}
	}
	
}
// {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
//{0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
void test001(void){
	//显示位置1
				P2 = 0x01;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字1
				P2 =0xc0;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
	//显示位置2
				P2 = 0x02;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字2
				P2 =0xf9;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
	//显示位置3
				P2 = 0x04;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字3
				P2 =0xa4;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
		//显示位置4
				P2 = 0x08;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字4
				P2 =0xb0;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
			//显示位置5
				P2 = 0x10;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字5
				P2 =0x99;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
			//显示位置6
				P2 = 0x20;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字6
				P2 =0x92;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
			//显示位置7
				P2 = 0x40;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字7
				P2 =0x82;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
			//显示位置8
				P2 = 0x80;
	      P3_7 = 1;
        P3_7 = 0;
	//显示数字8
				P2 =0xf8;
				P3_6 = 1;
				P3_6 = 0;
	delay_ms(2);
}
void display_digit(int position, int digit) {
    // 定义数码管位置对应的端口值
    unsigned char position_codes[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    // 定义数字对应的段码值
    unsigned char digit_codes[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

    // 检查输入的有效性
    if (position < 1 || position > 8 || digit < 0 || digit > 15) {
        return; // 如果输入无效，则直接返回
    }

    // 设置数码管的位置
    P2 = position_codes[position - 1];
    P3_7 = 1;
    P3_7 = 0;

    // 设置要显示的数字
    P2 = digit_codes[digit];
    P3_6 = 1;
    P3_6 = 0;

    // 延时以保持显示稳定
    delay_ms(2);
}

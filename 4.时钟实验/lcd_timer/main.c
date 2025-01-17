#include <reg52.h>
#include <lcd1602.h>


uint8 arr[3];  // 用于存储显示的字符


unsigned char time = 0;    // 分
unsigned char time_point = 0;  // 秒
unsigned int i, j;

void timer() interrupt 1
{
    i++;
    if (i == 2)  // 每计数到2时更新一次时间
    {
        i = 0;
        time_point++;
        if (time_point == 10)  // 秒达到10后归零
        {
            time_point = 0;
            time++;
        }
        if (time == 10)  // 分达到10后归零
        {
            time = 0;
        }
    }

    // 将分钟和秒数转换为ASCII字符，更新显示内容
    arr[0] = time + 0x30;   // 将分钟转为字符
    arr[1] = 0x2E;          // 用"."分隔
    arr[2] = time_point + 0x30;  // 将秒数转为字符
}
void main()
{
    EA = 1; 
	
    TMOD = 0x01; 
    TH0 = 0x0B;  
    TL0 = 0xDC;   
	
    ET0 = 1; 
    TR0 = 1; 

    init();  // 初始化LCD显示

    while(1)
    {
        display(arr);  // 更新LCD显示
    }
}


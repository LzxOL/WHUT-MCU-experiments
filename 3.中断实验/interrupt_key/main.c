#include <reg51.h>
#include <INTRINS.H>

sbit key = P3^2;
unsigned int flag = 0;
void delay(unsigned int time);
// 外部中断0服务程序

void int0() interrupt 0 {
    while (!key) {  // 检查按键是否按下
        P0 = 0x00;  // 使所有LED全亮
        delay(500);  // 延时
    }
	if(key) flag = 1;
}

int main() {
    EA = 1; 
    IT0 = 1;  
    EX0 = 1;  
    
	P0 = 0xFE;    
    while (1) {
		//逻辑标志位
		if(flag == 1){
			P0 = 0xFE;
			flag = 0;
		}
        P0 = _crol_(P0, 1);  // 循环左移一位
        delay(300); 
    }
}

void delay(unsigned int time){
		unsigned int i, j;
		for (i = 0; i < time; i++) {
        for (j = 0; j < 123; j++) {
					
        }
    }
}

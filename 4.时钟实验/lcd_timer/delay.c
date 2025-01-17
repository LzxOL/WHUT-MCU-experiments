#include <reg52.h>
// 延时函数，确保LCD稳定
void delay_ms(unsigned int times)
{
    unsigned int i, j;
    for (i = 0; i < times; i++) {
        for (j = 0; j < 120; j++) {  // 调整循环次数以提高延时精度
            // 空循环，用于产生延时
        }
    }
}


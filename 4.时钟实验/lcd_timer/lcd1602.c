#include <reg52.h>
#include <lcd1602.h>
sbit rs = P1^0;  // RS (Register Select)
sbit rw = P1^1;  // RW (Read/Write)
sbit e = P1^2;   // E (Enable)

void delay_ms(unsigned int times)
{
    unsigned int i, j;
    for (i = 0; i < times; i++) {
        for (j = 0; j < 120; j++) {  // 调整循环次数以提高延时精度
            // 空循环，用于产生延时
        }
    }
}


// 写命令到LCD
void wrc(uint8 c)
{
    rs = 0;      // 选择指令寄存器
    rw = 0;      // 选择写操作
    e = 0;       // 使能低电平
    P0 = c;      // 将命令写到P0端口
    e = 1;       // 使能高电平，表示命令有效
    delay_ms(2);  // 延时
    e = 0;       // 使能低电平
    delay_ms(2);  // 延时，确保命令被处理
}

// 写数据到LCD
void wrd(uint8 dat)
{
    rs = 1;      // 选择数据寄存器
    rw = 0;      // 选择写操作
    e = 0;       // 使能低电平
    P0 = dat;    // 将数据写到P0端口
    e = 1;       // 使能高电平
    delay_ms(2);  // 延时
    e = 0;       // 使能低电平
    delay_ms(2);  // 延时
}

// 初始化LCD
void init()
{
    delay_ms(20);  // 等待LCD稳定启动
    wrc(0x38);  // 设置为8位模式，2行显示
    wrc(0x06);  // 输入数据时，光标向右移动
    wrc(0x0C);  // 开启显示，关闭光标
    wrc(0x01);  // 清屏命令
    delay_ms(20); // 清屏需要较长时间
}

// 更新LCD显示内容
void display(uint8 arr[3])
{
    uint8 i;
    wrc(0x80);  // 将光标定位到第一行开始位置
    for (i = 0; i < 3; i++) {
        wrd(arr[i]);  // 写数据到LCD
    }
}

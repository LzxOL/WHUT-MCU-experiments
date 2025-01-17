// 写命令到LCD
typedef unsigned char uint8;
typedef unsigned int uint16;
void delay_ms(unsigned int times);
void wrc(uint8 c);
void wrd(uint8 dat);
void init();
void display(uint8 arr[3]);
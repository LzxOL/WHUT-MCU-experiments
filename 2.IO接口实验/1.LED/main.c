#include <reg51.h>
#include <INTRINS.H>

void delay(unsigned int time);
int main(){
    P0 = 0xfd;
    while(1){
//        P0 = _crol_(P0,1);
        delay(500);
    }
}
void delay(unsigned int time){
		unsigned int i, j;
		for (i = 0; i < time; i++) {
        for (j = 0; j < 123; j++) {
					
        }
    }
}

#include "mbed.h"
 
Ticker flipper1;
Ticker flipper2;
Ticker flipper3;
Ticker flipper4;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

void flip1() {
    led1 = !led1;
}

void flip2() {
    led2 = !led2;
}

void flip3() {
    led3 = !led3;
}

void flip4() {
    led4 = !led4;
}
 
int main() {
    led1 = 1;
    led2 = 1;
    led3 = 1;
    led4 = 1;
    flipper1.attach(&flip1, 1.0);
    flipper2.attach(&flip2, 2.0);
    flipper3.attach(&flip3, 4.0);
    flipper4.attach(&flip4, 8.0);
    
    while(1) {}
}
#include "mbed.h"
 
DigitalOut myled(LED1);
DigitalOut Ctrl(p8);
 
int main() {
    while(1) {
        Ctrl = 1;
        myled = 1;
        wait(2);
        Ctrl = 0;
        myled = 0;
        wait(2);
    }
}
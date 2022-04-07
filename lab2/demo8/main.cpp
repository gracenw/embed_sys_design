#include "mbed.h"
 
DigitalOut myled(LED1);
DigitalOut Ctrl(p8); //Solenoid output control bit
 
int main() {
    while(1) {
        Ctrl = 1; //ON
        myled = 1;
        wait(0.5); 
        Ctrl = 0; //OFF
        myled = 0;
        wait(2);
    }
}
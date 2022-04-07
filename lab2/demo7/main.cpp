#include "mbed.h"
 
DigitalOut myled(LED1);
PwmOut ctrl(p21);
 
int main() {
    for(float i = 0.0; i <= 1.0; i += 0.1) {
        ctrl = i;
        wait(1);
        ctrl = 0.0;
        wait(1);
    }
}
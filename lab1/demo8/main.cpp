#include "mbed.h"
 
PwmOut led(p23);
AnalogIn pot(p19);

int main() {
    while(1) {
        led = pot;
        wait(0.01);
    }
}

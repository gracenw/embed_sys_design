#include "mbed.h"
 
DigitalOut led(p24);
DigitalIn pb(p23);

int main() {
    while(1) {
        led = pb;
    }
}

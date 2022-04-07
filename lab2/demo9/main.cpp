#include "mbed.h"
#include "Servo.h"

AnalogIn pot(p20);
Servo servo(p21);
Serial pc(USBTX, USBRX);

int main() {
    while(1) {
        servo = pot;
        wait(0.2);
    }
}

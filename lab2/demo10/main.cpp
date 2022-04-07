// Sweep the motor speed from full-speed reverse (-1.0) to full speed forwards (1.0)

#include "mbed.h"
#include "Motor.h"

Motor m(p21, p6, p5); // pwm, fwd, rev
AnalogIn pot(p20);
Serial pc(USBTX,USBRX);

int main() {
    while(1) {
        m.speed((pot * 2) - 1);
        wait(0.2);
    }
}

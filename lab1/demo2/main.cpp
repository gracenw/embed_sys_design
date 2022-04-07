#include "mbed.h"
#include "PinDetect.h"

PwmOut led(LED1);
PwmOut monitor(p23);
PinDetect pb_up(p22);
PinDetect pb_down(p21);

void pb_up_callback (void) {
    if(led < 1.0f) led = led + 0.1f;
    wait(.1);
}

void pb_down_callback (void) {
    if(led > 0.0f) led = led - 0.1f;
    wait(.1);
}

int main() {
    pb_up.mode(PullUp);
    pb_down.mode(PullUp);
    
    wait(.001);
    
    pb_up.attach_deasserted(&pb_up_callback);
    pb_down.attach_deasserted(&pb_down_callback);
    
    pb_up.setSampleFrequency();
    pb_down.setSampleFrequency();
 
    while (1) {
        wait(.5);
        monitor = led;
    }
}
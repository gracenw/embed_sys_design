#include "mbed.h"
#include "PinDetect.h"

PwmOut red(p23);
PwmOut green(p24);
PwmOut blue(p25);
PwmOut led(LED1);
PinDetect pb_up(p22);
PinDetect pb_down(p21);
DigitalIn dip_red(p8);
DigitalIn dip_green(p7);
DigitalIn dip_blue(p6);

void pb_up_callback (void) {
    if(!dip_red && red < 1.0f) red = red + 0.1f;
    if(!dip_green && green < 1.0f) green = green + 0.1f;
    if(!dip_blue && blue < 1.0f) blue = blue + 0.1f;
    wait(.1);
}

void pb_down_callback (void) {
    if(!dip_red && red > 0.0f) red = red - 0.1f;
    if(!dip_green && green > 0.0f) green = green - 0.1f;
    if(!dip_blue && blue > 0.0f) blue = blue - 0.1f;
    wait(.1);
}

int main() {
    pb_up.mode(PullUp);
    pb_down.mode(PullUp);
    dip_red.mode(PullUp);
    dip_green.mode(PullUp);
    dip_blue.mode(PullUp);
    
    wait(.001);
    
    pb_up.attach_deasserted(&pb_up_callback);
    pb_down.attach_deasserted(&pb_down_callback);
    
    pb_up.setSampleFrequency();
    pb_down.setSampleFrequency();
    
    red.period(0.0005f);
    green.period(0.0005f);
    blue.period(0.0005f);
    
    int prev_red = 0;
    int prev_green = 0;
    int prev_blue = 0;
 
    while (1) {
        if(dip_red == 0 && prev_red > 0) red = 1;
        if(dip_red == 1 && prev_red == 0) red = 0;
        if(dip_green == 0 && prev_green > 0) green = 1;
        if(dip_green == 1 && prev_green == 0) green = 0;
        if(dip_blue == 0 && prev_blue > 0) blue = 1;
        if(dip_blue == 1 && prev_blue == 0) blue = 0;
        
        prev_red = dip_red;
        prev_green = dip_green;
        prev_blue = dip_blue;
        wait(0.1);
    }
}
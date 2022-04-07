#include "mbed.h"

AnalogOut aout(p18);
 
int main()
{
    float sample;
    
    while(1) {
        for (float i = 0.0f; i < 20.0f; i+=1.0f) {
            sample = (float)(0.5f * sin((3.14 * i) / 10.0f) + 0.5f);
            aout.write(sample);
        }
    }
}
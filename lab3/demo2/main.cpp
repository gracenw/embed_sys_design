#include "mbed.h"
#include "ultrasonic.h"

Serial pc(USBTX, USBRX);

void dist(int distance)
{
    pc.printf("Distance %d mm\r\n", distance);
}

ultrasonic mu(p6, p7, .1, 1, &dist);

int main()
{
    mu.startUpdates();
    while(1)
    {
        mu.checkDistance();
    }
}

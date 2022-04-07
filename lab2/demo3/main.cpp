#include "mbed.h"
#include "uLCD_4DGL.h"
#include "LSM9DS1.h"

Serial pc(USBTX, USBRX);
uLCD_4DGL uLCD(p28, p27, p29);
LSM9DS1 IMU(p9, p10, 0xD6, 0x3C);

int main()
{
    IMU.begin();
    if (!IMU.begin()) pc.printf("failed to communicate with imu\n");
    IMU.calibrate(1);
    
    uLCD.display_control(PORTRAIT);
    uLCD.cls();
    uLCD.baudrate(BAUD_3000000);
    wait(1.0);
    
    float vx = 0.0, vy = 0.0;
    int x = 63, y = 64, radius = 4;
    
    uLCD.background_color(BLUE);
    uLCD.cls();
    
    uLCD.line(0, 0, 127, 0, WHITE);
    uLCD.line(127, 0, 127, 127, WHITE);
    uLCD.line(127, 127, 0, 127, WHITE);
    uLCD.line(0, 127, 0, 0, WHITE);
    
    while(1) {
        uLCD.circle(x, y, radius, LGREY);
        wait(0.025);
        
        while(!IMU.accelAvailable());
        IMU.readAccel();
        
        vx = IMU.calcAccel(IMU.ay);
        vy = IMU.calcAccel(IMU.ax);
        
        uLCD.filled_circle(x, y, radius, BLUE);
        
        if(vx < -0.2 && (x < 126 - radius)) x++;
        if(vx > 0.2 && (x > radius + 1)) x--;
        if(vy > 0.2 && (y < 126 - radius)) y++;
        if(vy < -0.2 && (y > radius + 1)) y--;
    }
}
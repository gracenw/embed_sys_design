#include "mbed.h"
#include "rtos.h"
#include "SDFileSystem.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"

SDFileSystem sd(p5, p6, p7, p8, "sd");
RawSerial pc(USBTX, USBRX);
uLCD_4DGL uLCD(p28, p27, p29);
AnalogOut speaker(p18);
RawSerial bluefruit(p13, p14);
PwmOut red(p23);
PwmOut green(p24);
PwmOut blue(p25);
wave_player waver(&speaker);

Mutex ulcd_mutex;

int temp = 600;
int vol = 15;

void sound() {
    FILE *wave_file;
    wave_file=fopen("/sd/sounds/fireplace.wav","r");
    if(wave_file == NULL) pc.printf("could not open file for read\n");
    waver.play(wave_file, vol);
    fclose(wave_file);
    Thread::wait(1000);
}

void light()
{
    switch (temp) {
        case 600:
            red = 0.98f;
            green = 0.65f;
            blue = 0.57f;
            break;
        case 700:
            red = 0.99f;
            green = 0.45f;
            blue = 0.32f;
            break;
        case 800:
            red = 0.90f;
            green = 0.44f;
            blue = 0.38f;
            break;
        case 900:
            red = 0.90f;
            green = 0.21f;
            blue = 0.12f;
            break;
        case 1000:
            red = 1.0f;
            green = 0.02f;
            blue = 0.02f;
            break;
        case 1100:
            red = 0.90f;
            green = 0.38f;
            blue = 0.0f;
            break;
        case 1200:
            red = 1.0f;
            green = 0.62f;
            blue = 0.0f;
            break;
        case 1300:
            red = 0.73f;
            green = 0.94f;
            blue = 0.98f;
            break;
        case 1400:
            red = 0.81f;
            green = 0.96f;
            blue = 0.98f;
            break;
        case 1500:
            red = 0.95f;
            green = 0.98f;
            blue = 0.99f;
            break;
        default:
            break;
    }
    Thread::wait(1000);
}

void temperature() {
    ulcd_mutex.lock();
    uLCD.locate(5, 5);
    uLCD.printf("Temperature");
    uLCD.locate(20,20);
    uLCD.printf("%i degrees Celsius", temp);
    ulcd_mutex.unlock();
    Thread::wait(500);
}

void volume() {
    ulcd_mutex.lock();
    uLCD.locate(30, 70);
    uLCD.printf("Volume");
    uLCD.filled_rectangle(10, 80, 120, 120, DGREY);
    uLCD.rectangle(10, 80, 120, 115, WHITE);
    for(int i = 1; i <= vol; i++) {
        uLCD.filled_rectangle((10 + 7 * i), 80, (17 + 7 * i), 120, WHITE);
    }
    ulcd_mutex.unlock();
    Thread::wait(100);
}

int main() {
    uLCD.display_control(PORTRAIT);
    uLCD.cls();
    uLCD.baudrate(BAUD_3000000);
    uLCD.background_color(DGREY);
    uLCD.line(63, 0, 63, 127, WHITE);
    uLCD.color(WHITE);
    
    red.period(0.0005f);
    green.period(0.0005f);
    blue.period(0.0005f);
    
    red = 0.0f;
    blue = 0.0f;
    green = 0.0f;
    
    pc.baud(9600);
    bluefruit.baud(9600);
    
    Thread sound_t;
    Thread light_t;
    Thread temperature_t;
    Thread volume_t;
    
    sound_t.start(sound);
    light_t.start(light);
    temperature_t.start(temperature);
    volume_t.start(volume); 
    
    char bnum=0;
    char bhit=0;
    
    while(1) {
        if (bluefruit.getc()=='!') {
            if (bluefruit.getc()=='B') {
                bnum = bluefruit.getc();
                bhit = bluefruit.getc();
                if (bluefruit.getc()==char(~('!' + 'B' + bnum + bhit)) && bhit=='1') {
                    switch (bnum) {
                        case '5': //up arrow
                            if (temp < 1500) temp += 100;
                            break;
                        case '6': //down arrow
                            if (temp > 600) temp -= 100;
                            break;
                        case '7': //left arrow
                            if (vol > 0) vol --;
                            break;
                        case '8': //right arrow
                            if (vol < 15) vol ++;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

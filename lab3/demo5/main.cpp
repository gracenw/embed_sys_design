#include "mbed.h"
#include "rtos.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
#include "SDFileSystem.h"
#include "Speaker.h"

RawSerial pc(USBTX, USBRX);
uLCD_4DGL uLCD(p28, p27, p29);
AnalogOut DACOut(p18);
RawSerial bluefruit(p13, p14);
PwmOut red(p23);
PwmOut green(p24);
PwmOut blue(p25);
SDFileSystem sd(p5, p6, p7, p8, "sd");
wave_player waver(&DACOut);
Speaker speaker(p18);


Mutex ulcd_mutex;

float new_red = 0;
float new_green = 0;
float new_blue = 0;

int curr = 0;

int vol = 15;
bool rgb_change = 1;

void sound() {
    float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
    float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };
    while(1) {
        for(int i = 0; i < 18; i++) {
            speaker.PlayNote(note[i], duration[i], 0.05);
        }
        Thread::wait(2000);
    }
}

void light()
{
    while(1) {
        green = new_green;
        red = new_red;
        blue = new_blue;
        Thread::wait(500);
        red = 0.1;
        green = new_green;
        blue = new_blue;
        Thread::wait(500);
        red = new_red;
        green = 0.1;
        blue = new_blue;
        Thread::wait(500);
        red = new_red;
        green = new_green;
        blue = 0.1;
        Thread::wait(500);
    }
}

void temperature() {
    while(1) {
        if (curr == 0) {
            ulcd_mutex.lock();
            uLCD.filled_rectangle(0, 0, 20, 20, RED);
            uLCD.filled_rectangle(20, 0, 40, 20, BLUE);
            uLCD.filled_rectangle(40, 0, 60, 20, GREEN);
            uLCD.filled_rectangle(60, 0, 80, 20, RED);
            uLCD.filled_rectangle(80, 0, 100, 20, BLUE);
            uLCD.filled_rectangle(100, 0, 120, 20, GREEN);
            uLCD.filled_rectangle(120, 0, 127, 20, RED);
            uLCD.filled_rectangle(0, 20, 20, 40, BLUE);
            uLCD.filled_rectangle(20, 20, 40, 40, GREEN);
            uLCD.filled_rectangle(40, 20, 60, 40, RED);
            uLCD.filled_rectangle(60, 20, 80, 40, BLUE);
            uLCD.filled_rectangle(80, 20, 100, 40, GREEN);
            uLCD.filled_rectangle(100, 20, 120, 40, RED);
            uLCD.filled_rectangle(120, 20, 127, 40, BLUE);
            uLCD.filled_rectangle(0, 40, 20, 60, RED);
            uLCD.filled_rectangle(20, 40, 40, 60, BLUE);
            uLCD.filled_rectangle(40, 40, 60, 60, GREEN);
            uLCD.filled_rectangle(60, 40, 80, 60, RED);
            uLCD.filled_rectangle(80, 40, 100, 60, BLUE);
            uLCD.filled_rectangle(100, 40, 120, 60, GREEN);
            uLCD.filled_rectangle(120, 40, 127, 60, RED);
            ulcd_mutex.unlock();
            curr = 1;
        }
        else {
            ulcd_mutex.lock();
            uLCD.filled_rectangle(0, 0, 20, 20, BLUE);
            uLCD.filled_rectangle(20, 0, 40, 20, GREEN);
            uLCD.filled_rectangle(40, 0, 60, 20, RED);
            uLCD.filled_rectangle(60, 0, 80, 20, BLUE);
            uLCD.filled_rectangle(80, 0, 100, 20, GREEN);
            uLCD.filled_rectangle(100, 0, 120, 20, RED);
            uLCD.filled_rectangle(120, 0, 127, 20, BLUE);
            uLCD.filled_rectangle(0, 20, 20, 40, GREEN);
            uLCD.filled_rectangle(20, 20, 40, 40, RED);
            uLCD.filled_rectangle(40, 20, 60, 40, BLUE);
            uLCD.filled_rectangle(60, 20, 80, 40, GREEN);
            uLCD.filled_rectangle(80, 20, 100, 40, RED);
            uLCD.filled_rectangle(100, 20, 120, 40, BLUE);
            uLCD.filled_rectangle(120, 20, 127, 40, GREEN);
            uLCD.filled_rectangle(0, 40, 20, 60, BLUE);
            uLCD.filled_rectangle(20, 40, 40, 60, GREEN);
            uLCD.filled_rectangle(40, 40, 60, 60, RED);
            uLCD.filled_rectangle(60, 40, 80, 60, BLUE);
            uLCD.filled_rectangle(80, 40, 100, 60, GREEN);
            uLCD.filled_rectangle(100, 40, 120, 60, RED);
            uLCD.filled_rectangle(120, 40, 127, 60, BLUE);
            ulcd_mutex.unlock();
            curr = 0;
        }
        Thread::wait(2000);
    }
}

void volume() {
    while(1) {
        if (rgb_change) {
            ulcd_mutex.lock();
            uLCD.locate(1, 9);
            uLCD.printf("RGB:");
            uLCD.locate(2, 12);
            uLCD.printf("               ");
            uLCD.locate(2, 12);
            uLCD.printf("(%i, %i, %i)", ((int)(new_red*255)), ((int)(new_green*255)), ((int)(new_blue*255)));
            ulcd_mutex.unlock();
            rgb_change = 0;
        }
        Thread::wait(500);
    }
}

int main() {
    uLCD.display_control(LANDSCAPE);
    uLCD.cls();
    uLCD.baudrate(BAUD_3000000);
    uLCD.line(0, 61, 128, 61, WHITE);
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
    
    //sound_t.start(sound);
    light_t.start(light);
    temperature_t.start(temperature);
    volume_t.start(volume); 
    
    char bnum=0;
    char bhit=0;
    char bred=0;
    char bgreen=0;
    char bblue=0;
    red = green = blue = 0;
    
    while(1) {
        if (bluefruit.readable() && bluefruit.getc()=='!') {
            char type = bluefruit.getc();
            if (type=='C') {
                bred = bluefruit.getc();
                bgreen = bluefruit.getc();
                bblue = bluefruit.getc();
                if (bluefruit.getc()==char(~('!' + 'C' + bred + bgreen + bblue))) {
                    new_red = bred/255.0;
                    new_green = bgreen/255.0;
                    new_blue = bblue/255.0;
                    rgb_change = 1;
                }
            }
            if (type=='B') {
                bnum = bluefruit.getc();
                bhit = bluefruit.getc();
                if (bluefruit.getc()==char(~('!' + 'B' + bnum + bhit)) && bhit=='1') {
                    switch (bnum) {
                        case '6': //up arrow
                            if (vol > 0) {
                                vol --;
                            }
                            break;
                        case '5': //down arrow
                            if (vol < 15) { 
                                vol ++;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

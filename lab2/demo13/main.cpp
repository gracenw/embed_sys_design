#include "mbed.h"
#include "SDFileSystem.h"
 
SDFileSystem sd(p5, p6, p7, p8, "sd");
Serial pc(USBTX, USBRX);
 
int main() {
    mkdir("/sd/mydir", 0777);
    
    FILE *fp = fopen("/sd/mydir/sdtest.txt", "w");
    if(fp == NULL) error("could not open file for write\n");
    fprintf(fp, "hello SD file world\n");
    fclose(fp); 
    
    unsigned char c;
    
    fp = fopen("/sd/mydir/sdtest.txt", "r");
    while (!feof(fp)){
        c=fgetc(fp); 
        pc.printf("%c", c);
    }
    fclose(fp);
}

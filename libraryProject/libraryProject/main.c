#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

typedef unsigned short color_t;

void clear_screen();
void exit_graphics();
void init_graphics();
char getkey();
void sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x, int y, int width, int height, color_t c);
color_t getColor(color_t red, color_t green, color_t blue);

char *startOfFile = 0;
long int screensize = 0;
int fd = 0;
struct fb_var_screeninfo varInfo;
struct fb_fix_screeninfo fixedInfo;


int main(int argc, char** argv)
{
    int i;
    int j;

    init_graphics();

    draw_rect(80, 35, 350, 200, getColor(25, 10, 15));

    sleep_ms(1000);

    draw_rect(800, 35, 350, 200, getColor(5, 15, 28));


    exit_graphics();

    /*char key;
    int x = (640-20)/2;
    int y = (480-20)/2;

    do
    {
        //draw a black rectangle to erase the old one
        draw_rect(x, y, 20, 20, 0);
        key = getkey();
        if(key == 'w') y-=10;
        else if(key == 's') y+=10;
        else if(key == 'a') x-=10;
        else if(key == 'd') x+=10;
        //draw a blue rectangle
        draw_rect(x, y, 20, 20, 15);
        sleep_ms(20);
    } while(key != 'q');

    */

    return 0;

}


color_t getColor(color_t red, color_t green, color_t blue)
{
//- upper 5 bits to storing red intensity (0-31).
//- middle 6 bits to store green intensity (0-63).
//- low order 5 bits to store blue intensity (0-31).

    // Prevent overflow by restricting colors to there maximum values.
    if(red > 31) red = 31;
    if(green > 63) green = 63;
    if(blue > 31) blue = 31;

    color_t newColor;
    newColor = newColor | red;
    newColor = newColor << 11; // Shift the bits over 11 so that they occupy the uppermost five bits in newColor.

    green = green << 5; // Shift the green value over so that the middle 6 bits will contain the green intensity
    newColor = newColor | green;

    newColor = newColor | blue; // bitwise the blue color into the lower 5 bits

    return newColor;
}

void clear_screen()
{

}

void exit_graphics()
{
    munmap(startOfFile, screensize);
    close(fd);
}

void init_graphics()
{


    // Open the file for reading and writing
    fd = open("/dev/fb0", O_RDWR); //Open the /dev/fb0 file using read/write
    if (!fd) printf("Error opening file.\n");



    printf("The framebuffer device was opened successfully.\n");



    //********** Get fixed screen information **********
    //ARG1: The first argument is the file descriptor
    //ARG2: The second argument is a device-dependent request code.
    //ARG3: The third argument is an untyped pointer to memory



    if (ioctl(fd, FBIOGET_FSCREENINFO, &fixedInfo)) printf("Error reading fixed information.\n");
    if (ioctl(fd, FBIOGET_VSCREENINFO, &varInfo)) printf("Error reading variable information.\n");


    screensize = varInfo.yres_virtual * fixedInfo.line_length;


    startOfFile = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    return 0;

}

char getkey()
{

    return 0;
}

void sleep_ms(long ms)
{
    nanosleep(ms * 1000000, NULL);
}

void draw_pixel(int x, int y, color_t color)
{
    // draw...
    // just fill upper half of the screen with something

    int index = (y * fixedInfo.line_length) + x;

    *(startOfFile + index) = color;

}

void draw_rect(int x, int y, int width, int height, color_t c)
{

    int i;
    int j;

    for(i = x; i < x+ width; i++)
    {
        for(j = y; j < y + height; j++)
        {
            draw_pixel(i, j, c);
        }
    }


}

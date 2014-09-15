#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

typedef unsigned short color_t;


color_t getColor(unsigned short red, unsigned short green, unsigned short blue);


int main(int argc, char* argv[])
{
    int fileDescriptor = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;

    // Open the file for reading and writing
    fileDescriptor = open("/dev/fb0", O_RDWR); //Open the /dev/fb0 file using read/write
    if (!fileDescriptor) {
        printf("Error: cannot open framebuffer device.\n");
        return(1);
    }

    printf("The framebuffer device was opened successfully.\n");


    /*
    ***** Get fixed screen information *****

    ARG1: The first argument is the file descriptor
    ARG2: The second argument is a device-dependent request code.
    ARG3: The third argument is an untyped pointer to memory
     */

    if (ioctl(fileDescriptor, FBIOGET_FSCREENINFO, &finfo))
    {
        printf("Error reading fixed information.\n");
    }

    if (ioctl(fileDescriptor, FBIOGET_VSCREENINFO, &vinfo))
    {
        printf("Error reading variable information.\n");
    }
    printf("%dx%d, %d bpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );


    // map framebuffer to user memory
    screensize = finfo.smem_len;

    fbp = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

    if ((int)fbp == -1)
    {
        printf("Failed to mmap.\n");
    }
    else
    {
        // draw...
        // just fill upper half of the screen with something
        memset(fbp, 0xff, screensize/2);
        // and lower half with something else
        memset(fbp + screensize/2, 0x18, screensize/2);
    }

    // cleanup
    munmap(fbp, screensize);
    close(fileDescriptor);
    return 0;
}


color_t getColor(unsigned short red, unsigned short green, unsigned short blue)
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
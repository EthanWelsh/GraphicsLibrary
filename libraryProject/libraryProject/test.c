#include "library.c"

int main(int argc, char** argv)
{

    init_graphics();

    int pittx = 0;
    int pitty = 30;

    /*                          P                                */

    clear_screen();

    int xp = 30 + pittx;
    int yp = 30 + pitty;

    draw_rect(xp, yp, 40, 300, getColor(0, 10, 15));   // STEM
    draw_rect(xp + 25, yp, 125, 135, getColor(0, 10, 15));  // BOX
    draw_rect(xp + 35, yp + 27, 70, 70, getColor(0, 0, 0));      // HOLE

    /*                          I                                */
    int xi = 210 + pittx;
    int yi = 30 + pitty;

    draw_rect(xi, yi, 40, 300, getColor(0, 10, 15));

    /*                          T                                */

    int xt = 325 + pittx;
    int yt = 30 + pitty;

    draw_rect(xt, yt, 40, 300, getColor(0, 10, 15));
    draw_rect(xt-50, yt, 135, 40, getColor(0, 10, 15));

    /*                          T                                */
    int xt2 = 475 + pittx;
    int yt2 = 30 + pitty;

    draw_rect(xt2, yt2, 40, 300, getColor(0, 10, 15));
    draw_rect(xt2-50, yt2, 135, 40, getColor(0, 10, 15));
    exit_graphics();

    return 0;
}
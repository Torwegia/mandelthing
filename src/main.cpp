#include "mandel.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    Mandelbrot *mandel;
    if(argc > 3)
    {
        std::cout << "invalid arguements!" << std::endl;
        std::cout << "try: " << argv[0] << std::endl;
        std::cout << "or:  " << argv[0] << "<width> <height>" << std::endl;
        return 1;
    }

    if(argc < 2)
        mandel = new Mandelbrot;
    else
    {
        int wid = atoi(argv[1]);
        int hei = atoi(argv[2]);
        mandel = new Mandelbrot(wid, hei);
    }

    mandel->write("set.png");

    return 0;
}

#ifndef MANDEL_INCLUDED
#define MANDEL_INCLUDED

#include <png++/png.hpp>
#include <complex>
#include <vector>
#include <deque>

#include "timer.h"

class Mandelbrot
{
    public:
        Mandelbrot();
        Mandelbrot(int width, int height);
        ~Mandelbrot();

        void write(const char* filename);
    private:
        //useful vars
        int m_width, m_height;
        double xmin, xmax, ycent;

        //timer... snore fest.
        Timer timer;

        //image things
        std::vector<std::vector<std::complex<double>>> plane;
        std::vector<png::rgb_pixel> colors;
        png::image<png::rgb_pixel> image;
        
        //Can't touch these methods
        void generate();
        void buildColors();
        png::rgb_pixel rainbow(double scale);
};

#endif

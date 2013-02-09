#include "mandel.h"
#include <cmath>
#include <algorithm>


Mandelbrot::Mandelbrot()
:m_width(2000), m_height(2000)
{
    buildColors();

    double range, xincr, yincr;
    xmin=-1.5;
    xmax=0.5;

    range = xmax - xmin;
    xincr = range / double(m_width);
    yincr = range / double(m_height);

    plane.resize(m_height);

    for(std::vector<std::complex<double>> &i: plane)
    {
        i.resize(m_width);
    }

    double real = xmin, imag = range / 2;

    for(unsigned int y = 0; y < m_height; ++y)
    {
        real = xmin;
        for(unsigned int x = 0; x < m_width; ++x)
        {
            plane[y][x] = std::complex<double>(real, imag);
            real += xincr;
        }
        imag -= yincr;
    }

    image.resize(m_width, m_height);

    generate();
}

Mandelbrot::Mandelbrot(int width, int height)
:m_width(width), m_height(height)
{
    buildColors();

    double xrange, yrange;
    double xincr, yincr;
    
    //xmin=-1.26, xmax=-1.24;
    //xmin=-1.24, xmax=-1.26;
    //xmin=0.001585, xmax=0.001612;
    xmin=-1.5, xmax=0.5;

    //ycent=0.822467633298876;
    ycent=0.0;

    double ratio = double(m_height)/double(m_width);

    xrange = xmax - xmin;
    yrange = xrange * ratio;

    xincr = xrange / double(m_width);
    yincr = yrange / double(m_height);

    plane.resize(m_height);

    for(std::vector<std::complex<double>> &i: plane)
    {
        i.resize(m_width);
    }

    double real = xmin, imag = yrange / 2 + ycent;

    for(unsigned int y = 0; y < m_height; ++y)
    {
        real = xmin;
        for(unsigned int x = 0; x < m_width; ++x)
        {
            plane[y][x] = std::complex<double>(real, imag);
            real += xincr;
        }
        imag -= yincr;
    }

    image.resize(m_width, m_height);

    generate();
}

Mandelbrot::~Mandelbrot()
{
    for(std::vector<std::complex<double>> &i: plane)
    {
        i.clear();
    }
    plane.clear();
}

void Mandelbrot::write(const char *filename)
{
    image.write(filename);
}

void Mandelbrot::generate()
{
    std::complex<double> t1, t2, c;
    
    timer.start();

    for(unsigned int y = 0; y < m_height; ++y)
    {
        for(unsigned int x = 0; x < m_width; ++x)
        {
            //t1 = std::complex<double>(0.0,0.0);
            t1 = std::complex<double>(-0.835,-0.2321);
            c = plane[y][x];

            for(unsigned int i = 0; i < 1024; ++i)
            {
                t1 = t1 * t1 - c;  //Julia
                //t1 = t1 * t1 + c;  //Mandel
                
                //ship

                //t2 = std::complex<double>(fabs(t1.real()),fabs(t1.imag()));
                //t1 = t2*t2 - c;
                if(abs(t1) > 2.0)
                {
                    double scale = (i +1-log(log(abs(t1)))/log(2))/36;
                    image[y][x] = rainbow(scale);
                    break;
                }
            }

            if(abs(t1) <= 2.0)
            {
                image[y][x] = png::rgb_pixel(0.0,0.0,0.0);
            }
        }
    }
    
    timer.stop();

    std::cout << timer.elapsed << std::endl;
}

png::rgb_pixel Mandelbrot::rainbow(double scale)
{
    if (scale>1.0)
    {
        if (scale-(int)scale==0.0)
            scale=1.0; 
        else 
            scale=scale-(int)scale;
    }

    int numColor = 6;
    double m = numColor * scale;
    int n = int(m);
    double fract = m-n;
    int t = int(fract*255);

    png::rgb_pixel pix;

    switch(n)
    {
        case 0: {
                    pix.red = 255;
                    pix.green = t;
                    pix.blue = 0;
                    break;
                };
        case 1: {
                    pix.red = 255 - t;
                    pix.green = 255;
                    pix.blue = 0;
                    break;
                };
        case 2: {
                    pix.red = 0;
                    pix.green = 255;
                    pix.blue = t;
                    break;
                };
        case 3: {
                    pix.red = 0;
                    pix.green = 255 - t;
                    pix.blue = 255;
                    break;
                };
        case 4: {
                    pix.red = t;
                    pix.green = 0;
                    pix.blue = 255;
                    break;
                };
        case 5: {
                    pix.red = 255;
                    pix.green = 0;
                    pix.blue = 255 - t;
                    break;
                };
        default: {
                     pix.red = 255;
                     pix.green = 0;
                     pix.blue = 0;
                     break;
                 };
    }

    return pix;

}

void Mandelbrot::buildColors()
{
    /*
       colors.push_back(png::rgb_pixel(0, 255, 255)); 
       colors.push_back(png::rgb_pixel(0, 127, 127)); 
       colors.push_back(png::rgb_pixel(0, 64, 64)); 
       colors.push_back(png::rgb_pixel(0, 64, 0)); 
       colors.push_back(png::rgb_pixel(0, 127, 0));
       colors.push_back(png::rgb_pixel(0, 255, 0));
       colors.push_back(png::rgb_pixel(127, 255, 0));
       colors.push_back(png::rgb_pixel(64, 255, 0));
       colors.push_back(png::rgb_pixel(127, 127, 0));
       colors.push_back(png::rgb_pixel(64, 64, 0));
       colors.push_back(png::rgb_pixel(255, 127, 0));
       colors.push_back(png::rgb_pixel(255, 64, 0));
       colors.push_back(png::rgb_pixel(255, 0, 0));
       colors.push_back(png::rgb_pixel(127, 0, 0));
       colors.push_back(png::rgb_pixel(64, 0, 0));
       colors.push_back(png::rgb_pixel(255, 0, 127));
       colors.push_back(png::rgb_pixel(255, 0, 64));
       colors.push_back(png::rgb_pixel(255, 0, 255));
       colors.push_back(png::rgb_pixel(127, 0, 255));
       colors.push_back(png::rgb_pixel(64, 0, 255));
       colors.push_back(png::rgb_pixel(127, 127, 127));
       colors.push_back(png::rgb_pixel(64, 64, 64));
       colors.push_back(png::rgb_pixel(255, 255, 255)); 
       colors.push_back(png::rgb_pixel(0, 0, 255));
       colors.push_back(png::rgb_pixel(0, 0, 127));
       colors.push_back(png::rgb_pixel(0, 0, 64));
     */
    colors.push_back(png::rgb_pixel(255,0,0));
    colors.push_back(png::rgb_pixel(255,127,0));
    colors.push_back(png::rgb_pixel(255,255,0));
    colors.push_back(png::rgb_pixel(0,255,0));
    colors.push_back(png::rgb_pixel(0,0,255));
    colors.push_back(png::rgb_pixel(111,0,255));
    colors.push_back(png::rgb_pixel(143,0,255));
}

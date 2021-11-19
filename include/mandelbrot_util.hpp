/*
    Class : Mandelbrot_util
    Written By : Sankalp Parashar
    Header File for mandelbrot_util.cpp containing declarations for some
    utility functions used in drawing a mandelbrot set
*/

#include <iostream>
#include <SFML/Graphics.hpp>

class Mandelbrot_util
{
    public:
        static void mandelbrot_set(sf::VertexArray& vertexarray, int pixel_shift_x,
                                   int pixel_shift_y, int precision, float zoom,
                                   const int width, const int height, int color_scheme);
};

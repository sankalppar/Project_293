/*
    Class : Mandelbrot_util
    Written By : Sankalp Parashar
    This file contains the implementation for the class mandelbrot_util defined
    for handling functions related to drawing the mandelbrot set
*/

#include <complex.hpp>
#include <mandelbrot_util.hpp>

/*
    Function : mandelbrot_set
    Written By : Sankalp Parashar
    This function takes the vertex array containing the pixel colors and alters
    it so as to draw the mandelbrot set given the horizontal shift, vertical shift,
    precision, zoom, width and height
*/
void Mandelbrot_util::mandelbrot_set(sf::VertexArray& vertexarray, int pixel_shift_x,
                                     int pixel_shift_y, int precision, float zoom,
                                     const int width, const int height, int color_scheme)
{
    //To run multiple parallel threads so that rendering is faster

    #pragma omp parallel for

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;
            complex_num c(x, y);
            complex_num z = c;
            int iterations = 0;
            //Finding the number of iterations needed to check if the sequence diverges
            for (int k = 0; k < precision; k++)
            {
                complex_num z2;
                z2 = z.square();
                z2 = z2 + c;
                z = z2;
                iterations++;
                if (z.modulus() > 4)
                    break;
            }

            //Setting the color of the values for which the sequence diverged
            //based on how soon it diverged for color scheme 1
            if (color_scheme == 1)
            {
                if (iterations < precision / 4.0)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0 / (precision / 4.0), 0, 0);
                    vertexarray[i*width + j].color = color;
                }
                else if (iterations < precision / 2.0)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0 / (precision / 2.0), 0);
                    vertexarray[i*width + j].color = color;
                }
                else if (iterations < precision)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0 / precision);
                    vertexarray[i*width + j].color = color;
                }
            }

            //Setting the color of the values for which the sequence diverged
            //based on how soon it diverged for color scheme 2
            if (color_scheme == 2)
            {
                if (iterations < precision / 4.0)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0 / (precision / 4.0));
                    vertexarray[i*width + j].color = color;
                }
                else if (iterations < precision / 2.0)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0 / (precision / 2.0), 0);
                    vertexarray[i*width + j].color = color;
                }
                else if (iterations < precision)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0 / precision, 0, 0);
                    vertexarray[i*width + j].color = color;
                }
            }

            //Setting the color of the values for which the sequence diverged
            //based on how soon it diverged for color scheme 3
            if (color_scheme == 3)
            {
                if (iterations < precision / 4.0)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, iterations * 255.0 / (precision / 4.0), 0);
                    vertexarray[i*width + j].color = color;
                }
                else if (iterations < precision / 2.0)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(0, 0, iterations * 255.0 / (precision / 2.0), 0);
                    vertexarray[i*width + j].color = color;
                }
                else if (iterations < precision)
                {
                    vertexarray[i*width + j].position = sf::Vector2f(j, i);
                    sf::Color color(iterations * 255.0 / precision, 0, 0);
                    vertexarray[i*width + j].color = color;
                }
            }
        }
    }
}

/*
Program to generate and plot mandelbrot set using SFML
Written By : Sankalp Parashar(200050127)
*/


#include <SFML/Graphics.hpp>
#include <complex.hpp>

//Global variables to store size of the window
const int width = 1280;
const int height = 720;

/*
    Function : mandelbrot_set
    Generates the pixel color values based on the precision, zoom and pixel_shift
    and places it in a vertex array.
*/
void mandelbrot_set(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int precision, float zoom)
{
    #pragma omp parallel for   //To run multiple parallel threads so that rendering is faster
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

            //Setting the colour of the values for which the sequence diverged
            //based on how soon it diverged
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
    }
}

int main()
{
    sf::String title_string = "Mandelbrot Zoom";
    sf::RenderWindow window(sf::VideoMode(width, height), title_string);
    window.setFramerateLimit(30);
    sf::VertexArray pointmap(sf::Points, width * height);

    float zoom = 300.0;
    int precision = 50;
    int x_shift = width / 2;
    int y_shift = height / 2;

    mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Waiting for left click event for zooming in
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift -= position.x - x_shift;
            y_shift -= position.y - y_shift;
            zoom *= 2.0;
            precision += 150;
            #pragma omp parallel for  //To use parallel threads for faster rendering
            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
        }

        //Waiting for right click event for zooming out
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift += position.x - x_shift;
            y_shift += position.y - y_shift;
            if(zoom > 1 && precision > 50)
            {
                zoom /= 2.0;
                precision -= 150.0;
            }
            #pragma omp parallel for //To use parallel threads for faster rendering
            for(int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
        }
        window.clear();
        window.draw(pointmap);
        window.display();
    }

    return 0;
}

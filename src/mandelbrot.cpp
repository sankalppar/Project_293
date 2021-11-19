/*
Program to generate and plot mandelbrot set using SFML
Written By : Sankalp Parashar(200050127)
*/


#include <cassert>
#include <chrono>
#include <thread>
#include <mandelbrot_util.hpp>


//Global variables to store size of the window
const int width = 1280;
const int height = 720;

/*
    The main function, it starts a window in sfml and waits for different events
    and calls functions from Mandelbrot_util accordingly.
*/

int main()
{
    //Used for sleep_for function
    using namespace std::this_thread;
    //Used for seconds
    using namespace std::chrono;
    sf::String title_string = "Mandelbrot Zoom";
    int fps = 30;

    //Making sure that the window does not get outide the screen

    assert(width < 2000);
    assert(height < 1500);

    //Creating window with set width, height and title
    sf::RenderWindow window(sf::VideoMode(width, height), title_string);
    //Setting fps for changes
    window.setFramerateLimit(fps);
    //VertexArray is a data structure of SFML library that stores pixel information(color in this case)
    sf::VertexArray pointmap(sf::Points, width * height);

    float zoom = 300.0;
    int precision = 50;
    int x_shift = width / 2;
    int y_shift = height / 2;
    int color_scheme = 1;

    //Setting the amount of shift when arrow keys are pressed
    int horizontal_shift = 20;
    int vertical_shift = 15;

    Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom,
                                    width, height, color_scheme);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }

        /* The following lines wait for us to hit one of the control keys and
           alter the center, zoom and precision appropriately when one of those
           keys is pressed, calling mandelbrot_set function to draw the set with
           the new value of the parameters.
           The main controls are:
           Left Click : Zoom In at a particular point
           Right Click : Zoom Out
           Left Arrow Key : Move Left on the Mandelbrot Set
           Right Arrow Key : Move Right on the Mandelbrot Set
           Up Arrow Key : Move Up on the Mandelbrot Set
           Down Arrow Key : Move Down on the Mandelbrot Set
           Numbers 2 - 9 : Zoom in the number of times chosen with point of
                           zooming chosen internally
           Number 0 : Zoom in 10 times into the point
           R : Change Primary Color to Red
           G : Change Primary Color to Green
           B : Change Primary Color to Blue
       */

        //Waiting for left click event for zooming in
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift -= position.x - x_shift;
            y_shift -= position.y - y_shift;
            zoom *= 2.0;
            precision += 150;

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black for faster rendering

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        //Waiting for right click event for zooming out
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift += position.x - x_shift;
            y_shift += position.y - y_shift;
            if(zoom >= 600.0 && precision >= 200)
            {
                zoom /= 2.0;
                precision -= 150.0;

                // Making sure the zoom out does not exceed certain limit

                assert(zoom >= 300.0);
                assert(precision >= 50);
            }

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black before drawing the mandelbrot set

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Checking if Left Arrow Key has been pressed and changing x_shift accordingly

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            x_shift += horizontal_shift;

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black before drawing the mandelbrot set

            for(int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }

            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Checking if Right Arrow Key has been pressed and changing x_shift accordingly

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            x_shift -= horizontal_shift;

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black before drawing the mandelbrot set

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Checking if Up Arrow Key has been pressed and changing y_shift accordingly

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            y_shift += vertical_shift;

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black before drawing the mandelbrot set

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Checking if Down Arrow Key has been pressed and changing y_shift accordingly

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            y_shift -= vertical_shift;

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black before drawing the mandelbrot set

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Automatic Zoom upto 2 iterations when the 2 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            for (int j = 0; j < 2; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 3 iterations when the 3 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            for (int j = 0; j < 3; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 4 iterations when the 4 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            for (int j = 0; j < 4; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 5 iterations when the 5 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            for (int j = 0; j < 5; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 6 iterations when the 6 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            for (int j = 0; j < 6; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 7 iterations when the 7 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        {
            for (int j = 0; j < 7; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 8 iterations when the 8 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        {
            for (int j = 0; j < 8; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 9 iterations when the 9 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        {
            for (int j = 0; j < 9; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Automatic Zoom upto 10 iterations when the 0 key is pressed

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        {
            for (int j = 0; j < 10; j++)
            {
                //Setting the center for the zoom
                x_shift = x_shift + 0.7492*zoom;
                y_shift = y_shift + 0.1*zoom;

                //To use parallel threads for faster rendering

                #pragma omp parallel for

                //Coloring the screen black before drawing the mandelbrot set

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                zoom *= 2.0;
                precision += 150;

                Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                                zoom, width, height, color_scheme);
                // Added to display the window at intermediate zoom steps
                window.clear();
                window.draw(pointmap);
                window.display();
                sleep_for(milliseconds(10));
            }
        }

        // Changing Color Scheme To Red Primary

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            color_scheme = 1;

            //To use parallel threads for faster rendering

            #pragma omp parallel for

            //Coloring the screen black before drawing the mandelbrot set

            for(int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }

            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Changing Color Scheme to Blue Primary

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            color_scheme = 2;

            // To use parallel threads for faster rendering

            #pragma omp parallel for

            // Coloring the screen black before drawing the mandelbrot set

            for (int i = 0; i < width * height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }

            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        // Changing Color Scheme to Green Primary

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            color_scheme = 3;

            // To use parallel threads for faster rendering

            #pragma omp parallel for

            // Coloring the screnn black before drawing the mandelbrot set

            for (int i = 0; i < width * height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }

            Mandelbrot_util::mandelbrot_set(pointmap, x_shift, y_shift, precision,
                                            zoom, width, height, color_scheme);
        }

        window.clear();
        window.draw(pointmap);
        window.display();
    }

    return 0;
}

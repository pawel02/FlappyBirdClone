#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

#include "Renderer.h"

#if IS_DEBUG == 1

std::mutex g_FPS_mutex;
void PrintFPS(int& FPS, bool& isRunning)
{
    while (isRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //make sure that when accessing this data by reference you dont run into problems such as writing to the same place at the same time
        std::lock_guard<std::mutex> guard(g_FPS_mutex); 
        std::cout << FPS << "\n";
        FPS = 0;
    }
}

#endif

int main()
{
    sf::Vector2f windowSize = {1000, 600};

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Flappy bird clone!");


#if IS_DEBUG == 1    
    int FPS = 0;
    bool showFPS = true;
    std::thread t( PrintFPS, std::ref(FPS), std::ref(showFPS));
#endif

    //create the renderer
    Renderer renderer(windowSize);

    //create the background for the game
    sf::Texture background;
    sf::Sprite sprite_bg;
    if (!background.loadFromFile("E:\\pawel\\yt\\flappyBirdRef\\flappyBirdRef\\res\\images\\background.png"))
    {
        std::cout << "Could not load the backgorund" << std::endl;
    }

    sprite_bg.setTexture(background);
    sprite_bg.scale(sf::Vector2f(1.0f, 1.0f));

    while (window.isOpen())
    {
        //just to show the FPS
#if IS_DEBUG == 1
        FPS++;
#endif

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            renderer.EventDispatch(event);
        }

        window.clear(sf::Color::Black);
        
        //draw the background first
        window.draw(sprite_bg);

        //drawing everything in the window
        renderer.draw(&window);

        window.display();
    }

#if IS_DEBUG == 1 
    showFPS = false;
    t.detach();
#endif

    return 0;
}
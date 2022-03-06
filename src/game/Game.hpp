#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "InputSystem.hpp"
#include "Elements.hpp"
#include "Utils.hpp"

class Game {
public:
    Game(char* windowTitle, int windowWidth, int windowHeight);
    ~Game();

    void Run();

private:
    static const int PIXEL_SIZE = 20;
    
    char* windowTitle;
    int windowWidth;
    int windowHeight;

    int lastFrames = 0;
    int frames = 0;
    long double frameTime = currTime();

    long double updatePixelDelay = 50;
    long double updatePixelTime = currTime();

    Pixel*** map;
    Pixel* choosenElement = new Sand(false);

    sf::RenderWindow window;
    InputSystem inputSystem;

    bool isPaused = false;

    void Update();
    void Render();
};

#endif
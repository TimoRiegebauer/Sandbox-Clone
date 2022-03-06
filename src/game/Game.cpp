#include "Game.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

Game::Game(char* windowTitle, int windowWidth, int windowHeight) {
    this->windowTitle = windowTitle;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    // Initialize the Map
    map = new Pixel**[windowHeight / PIXEL_SIZE];
    for (int y = 0; y < windowHeight / PIXEL_SIZE; y++) {
        map[y] = new Pixel*[windowWidth / PIXEL_SIZE];
        for (int x = 0; x < windowWidth / PIXEL_SIZE; x++) {
            map[y][x] = new Pixel();
        }
    }
}

Game::~Game() {
    // Destroy the map
    for (int y = 0; y < windowHeight / PIXEL_SIZE; y++) {
        delete [] map[y];
    }
}

/* Public methods */

void Game::Run() {
    window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle);
    
    while (window.isOpen()) {
        // Updating the game (GameLogic, Events, etc...)
        Update();
        // Rendering the game
        Render();
    }
}

/* Private methods */

void Game::Update() {
    frames++;

    // Check FPS
    if ((currTime() - frameTime) >= 1000) {
        lastFrames = frames;
        std::cout << "FPS: " << lastFrames << std::endl;
        frames = 0;
        frameTime = currTime();
    }

    // Checking for Events
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape: {
                    window.close();
                } break;
                case sf::Keyboard::P: {
                    isPaused = !isPaused;
                } break;
                case sf::Keyboard::Num1: {
                    choosenElement = new Sand(false);
                } break;
                case sf::Keyboard::Num2: {
                    choosenElement = new Stone(false);
                } break;
                case sf::Keyboard::Num3: {
                    choosenElement = new Water(true, false);
                } break;

                default: break;
            }
        }

        inputSystem.Input(event, windowWidth, windowHeight);
    }

    // Ignore updating when isPaused
    if (isPaused) return;

    if (inputSystem.MouseButtonDown(0)) {
        if (map[inputSystem.GetMouseY() / PIXEL_SIZE][inputSystem.GetMouseX() / PIXEL_SIZE]->GetName() == "Void")
            map[inputSystem.GetMouseY() / PIXEL_SIZE][inputSystem.GetMouseX() / PIXEL_SIZE] = choosenElement;
    } else if (inputSystem.MouseButtonDown(1)) {
        if (map[inputSystem.GetMouseY() / PIXEL_SIZE][inputSystem.GetMouseX() / PIXEL_SIZE]->GetName() != "Void")
            map[inputSystem.GetMouseY() / PIXEL_SIZE][inputSystem.GetMouseX() / PIXEL_SIZE] = new Pixel();
    }

    // Update the map
    for (int y = 0; y < windowHeight / PIXEL_SIZE; y++) {
        for (int x = 0; x < windowWidth / PIXEL_SIZE; x++) {
            map[y][x]->SetUpdated(false);
        }
    }

    if ((currTime() - updatePixelTime) >= updatePixelDelay) {
        updatePixelTime = currTime();
        for (int y = (windowHeight / PIXEL_SIZE) - 1; y >= 0; y--) {
            for (int x = 0; x < windowWidth / PIXEL_SIZE; x++) {
                map[y][x]->Update(map, x, y, windowWidth / PIXEL_SIZE, windowHeight / PIXEL_SIZE);
            }
        }
    }
}

void Game::Render() {
    sf::Font font;
    font.loadFromFile("./build/fonts/Fredoka-Regular.ttf");

    // Draw the Pixels
    for (int y = 0; y < windowHeight / PIXEL_SIZE; y++) {
        for (int x = 0; x < windowWidth / PIXEL_SIZE; x++) {
            Pixel* pixel = map[y][x];
            sf::RectangleShape pixelRect = sf::RectangleShape();
            pixelRect.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
            pixelRect.setFillColor(sf::Color(pixel->GetR(), pixel->GetG(), pixel->GetB()));
            pixelRect.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
            window.draw(pixelRect);
        }
    }

    if (!isPaused) {
        // Draw the Element info
        sf::Text elementText = sf::Text("Choosen Element: " + choosenElement->GetName() + "\nLeft Click - Place\nRight Click - Delete\n1, 2, 3 - Switch Elements\nP - Pause", font);
        elementText.setCharacterSize(22);
        elementText.setPosition(10, 10);
        elementText.setFillColor(sf::Color(255, 255, 255));

        window.draw(elementText);
    }

    if (isPaused) {
        // Draw the paused background
        sf::RectangleShape foregroundRect = sf::RectangleShape();
        foregroundRect.setPosition(0, 0);
        foregroundRect.setSize(sf::Vector2f(windowWidth, windowHeight));
        foregroundRect.setFillColor(sf::Color(255, 255, 255, 122));

        // Draw the paused text
        sf::Text pausedText = sf::Text("Paused", font);
        pausedText.setCharacterSize(48);
        pausedText.setPosition((windowWidth / 2.0) - (pausedText.getLocalBounds().width / 2), (windowHeight / 2.0) - (pausedText.getLocalBounds().height / 2));
        pausedText.setFillColor(sf::Color(0, 0, 0));

        window.draw(foregroundRect);
        window.draw(pausedText);
    }

    window.display();
}
#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <SFML/Window.hpp>
#include <iostream>

class InputSystem {
public:
    InputSystem();
    ~InputSystem();

    void Input(sf::Event event, int windowWidth, int windowHeight);
    bool MouseButtonDown(int mouseButtonCode);
    int GetMouseX() const;
    int GetMouseY() const;

private:
    static const int MOUSE_BUTTON_COUNT = 5;

    bool* mouseButtonsDown = new bool[MOUSE_BUTTON_COUNT];
    int mouseX = 0;
    int mouseY = 0;
};

#endif
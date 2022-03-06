#include "InputSystem.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

InputSystem::InputSystem() {}

InputSystem::~InputSystem() {}

/* Public Methods */

void InputSystem::Input(sf::Event event, int windowWidth, int windowHeight) {
    if (event.type == sf::Event::MouseButtonPressed) {
        mouseButtonsDown[event.mouseButton.button] = true;
    } else if (event.type == sf::Event::MouseButtonReleased) {
        mouseButtonsDown[event.mouseButton.button] = false;
    } else if (event.type == sf::Event::MouseMoved) {
        mouseX = event.mouseMove.x;
        mouseY = event.mouseMove.y;

        if (mouseX < 0) mouseX = 0;
        if (mouseY < 0) mouseY = 0;
        if (mouseX >= windowWidth) mouseX = windowWidth-1;
        if (mouseY >= windowHeight) mouseY = windowHeight-1;
    }
}

bool InputSystem::MouseButtonDown(int mouseButtonCode) {
    return mouseButtonsDown[mouseButtonCode];
}

int InputSystem::GetMouseX() const {
    return mouseX;
}

int InputSystem::GetMouseY() const {
    return mouseY;
}
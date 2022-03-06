#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "Pixel.hpp"
#include <iostream>

class Sand : public Pixel {
public:
    Sand(bool updated) : Pixel("Sand", 255, 255, 0, updated) {}
    ~Sand() {}

    void Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight);
};

class Water : public Pixel {
public:
    Water(bool left, bool updated) : left(left), Pixel("Water", 64, 164, 223, updated) {}
    ~Water() {}

    void Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight);
private:
    bool left = false;
};

class Stone : public Pixel {
public:
    Stone(bool updated) : Pixel("Stone", 155, 155, 155, updated) {}
    ~Stone() {}

    void Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight);
};

#endif
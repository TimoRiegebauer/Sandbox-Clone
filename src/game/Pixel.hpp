#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <iostream>
#include <string>

class Pixel {
public:
    Pixel();
    Pixel(std::string name, int r, int g, int b, bool updated);
    virtual ~Pixel();

    std::string GetName() const;
    int GetR() const;
    int GetG() const;
    int GetB() const;
    void SetUpdated(bool updated);
    
    virtual void Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight);

protected:
    std::string name;
    bool updated = false;
    int r;
    int g;
    int b;
};

#endif
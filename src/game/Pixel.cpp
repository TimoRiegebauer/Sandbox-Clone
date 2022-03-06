#include "Pixel.hpp"

Pixel::Pixel() {
    name = "Void";
    r = 0;
    g = 0;
    b = 0;
}

Pixel::Pixel(std::string name, int r, int g, int b, bool updated) {
    this->name = name;
    this->r = r;
    this->g = g;
    this->b = b;
    this->updated = updated;
}

Pixel::~Pixel() {}

/* Getter and Setter */

std::string Pixel::GetName() const {
    return name;
}

int Pixel::GetR() const {
    return r;
}

int Pixel::GetG() const {
    return g;
}

int Pixel::GetB() const {
    return b;
}

void Pixel::SetUpdated(bool updated) {
    this->updated = updated;
}

/* Public methods */

void Pixel::Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight) {
}
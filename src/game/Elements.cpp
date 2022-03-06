#include "Elements.hpp"

/* Sand Pixel Update method */

void Sand::Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight) {
    if (updated) return;
    if (posY == (mapHeight - 1)) return;

    if (map[posY+1][posX]->GetName() == "Water") {
        map[posY][posX] = new Water(true, false);
        map[posY+1][posX] = new Sand(true);
    } else if (map[posY+1][posX]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY+1][posX] = new Sand(true);
    } else if (posX != 0 && map[posY+1][posX-1]->GetName() == "Water") {
        map[posY][posX] = new Pixel();
        map[posY][posX-1] = new Water(true, true);
        map[posY+1][posX-1] = new Sand(true);
    } else if (posX != 0 && map[posY+1][posX-1]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY+1][posX-1] = new Sand(true);
    } else if (posY != (mapWidth - 1) && map[posY+1][posX+1]->GetName() == "Water") {
        map[posY][posX] = new Pixel();
        map[posY][posX+1] = new Water(true, true);
        map[posY+1][posX+1] = new Sand(true);
    } else if (posY != (mapWidth - 1) && map[posY+1][posX+1]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY+1][posX+1] = new Sand(true);
    }
}

/* Water Pixel Udpate method */

void Water::Update(Pixel ***map, int posX, int posY, int mapWidth, int mapHeight) {
    if (updated) return;
    if (posY != (mapHeight - 1) && map[posY+1][posX]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY+1][posX] = new Water(left, true);
        return;
    }
    
    if (left && (posX == 0 || map[posY][posX-1]->GetName() != "Void")) {
        left = false;
    } else if (left && map[posY][posX-1]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY][posX-1] = new Water(left, true);
    } else if (!left && (posX == (mapWidth - 1) || map[posY][posX+1]->GetName() != "Void")) {
        left = true;
    } else if (!left && map[posY][posX+1]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY][posX+1] = new Water(left, true);
    }
}

/* Stone Pixel Update method */

void Stone::Update(Pixel*** map, int posX, int posY, int mapWidth, int mapHeight) {
    if (updated) return;

    if (posY != (mapHeight - 1) && map[posY+1][posX]->GetName() == "Water") {
        map[posY][posX] = new Water(true, false);
        map[posY+1][posX] = new Stone(true);
    } else if (posY != (mapHeight - 1) && map[posY+1][posX]->GetName() == "Void") {
        map[posY][posX] = new Pixel();
        map[posY+1][posX] = new Stone(true);
    }
}
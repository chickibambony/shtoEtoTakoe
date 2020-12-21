#pragma once
#include "Entity.h"

class Tile : public Entity{
public:
    int spriteX, spriteY;
    bool isCollidable;
};



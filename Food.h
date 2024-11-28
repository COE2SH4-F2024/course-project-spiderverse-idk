#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"

class Food
{
    private:
        objPos foodPos;
    
    public:
        Food();
        void generateFood(const objPos& blockOff, int boardSizeX, int boardSizeY);
        objPos getFoodPos() const;
};
#endif
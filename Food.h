#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPos foodPos;
    
    public:
        Food();
        void generateFood(const objPosArrayList& blockOff, int boardSizeX, int boardSizeY);
        objPos getFoodPos() const;
};
#endif
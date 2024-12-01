#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

#define DEFAULTFOODSYM '$'
#define SPECFOODSYM1 '+'
#define SPECFOODSYM2 '2'

class Food
{
    private:
        objPosArrayList* foodList;
    
    public:
        Food();
        Food(int size);
        void generateFood(const objPosArrayList& blockOff, int boardSizeX, int boardSizeY);
        objPos getFoodPos(int index) const;
        int getFoodListSize() const;
};
#endif
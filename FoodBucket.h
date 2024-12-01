#ifndef FOODBUCKET_H
#define FOODBUCKET_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "food.h"

class FoodBucket
{
    private:
        objPosArrayList foodList;
    
    public:
        FoodBucket();
        FoodBucket(int size);
        void generateFood(const objPosArrayList& blockOff, int boardSizeX, int boardSizeY);
        objPos getFoodPos(int index) const;
};
#endif
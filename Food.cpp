#include "Food.h"
#include <cstdlib>

Food::Food() {
    // Default food position and symbol
    // one food in bucket

    foodList = new objPosArrayList();
    foodList->insertTail(objPos(0, 0, DEFAULTFOODSYM));
}

Food::Food(int size) {
    // Default food position and symbol
    // custom number of food in bucket

    int i;
    size = (size >= 3)? size: 3;
    
    foodList = new objPosArrayList();
    
    foodList->insertTail(objPos(0, 0, SPECFOODSYM1));
    foodList->insertTail(objPos(0, 0, SPECFOODSYM2));

    for(i=2; i<size; i++)
    {
        foodList->insertTail(objPos(0, 0, DEFAULTFOODSYM));
    }
}

void Food::generateFood(const objPosArrayList& blockOff, int boardSizeX, int boardSizeY)
{
    objPos tempBlock, tempFood;
    bool same;
    int i,j;

    for(i=0; i<foodList->getSize(); i++)
    {
        do
        {
            same = false;

            // Generate a random position
            int randX = rand() % (boardSizeX - 2) + 1;
            int randY = rand() % (boardSizeY - 2) + 1;
            foodList->setElement(objPos(randX, randY, foodList->getElement(i).symbol), i);
            tempFood = foodList->getElement(i);

            // Check for overlap with snake
            for (j = 0; j < blockOff.getSize(); j++)
            {
                tempBlock = blockOff.getElement(j);
                if (tempFood.isPosEqual(&tempBlock))
                {
                    same = true;
                    break;
                }
            }

            // Check for overlap with other food items
            if (!same)
            {
                for (j = 0; j < i; j++)
                {
                    tempBlock = foodList->getElement(j);
                    if (tempFood.isPosEqual(&tempBlock))
                    {
                        same = true;
                        break;
                    }
                }
            }

        } while (same);  // Retry until no overlap
    }
}

objPos Food::getFoodPos(int index) const {
    return foodList->getElement(index);  // Return the current food position
}

int Food::getFoodListSize() const {
    return foodList->getSize(); // Return number of food in bucket
}
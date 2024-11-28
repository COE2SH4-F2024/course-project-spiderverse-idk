#include "Food.h"
#include <cstdlib>

Food::Food() {
    // Default food position and symbol
    objPos(0, 0, '$');
}

void Food::generateFood(const objPos& blockOff, int boardSizeX, int boardSizeY)
{
    do
    {
        // Generate a random position
        int randX = rand() % (boardSizeX - 2) + 1;
        int randY = rand() % (boardSizeY - 2) + 1;
        foodPos.setObjPos(randX, randY, '$');
    } while (foodPos.isPosEqual(&blockOff));
    
}

objPos Food::getFoodPos() const {
    return foodPos;  // Return the current food position
}
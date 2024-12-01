#include "Food.h"
#include <cstdlib>

Food::Food() {
    // Default food position and symbol
    objPos(0, 0, '$');
}

void Food::generateFood(const objPosArrayList& blockOff, int boardSizeX, int boardSizeY)
{
    objPos temp;
    bool same;

    do
    {
        same = false;

        // Generate a random position
        int randX = rand() % (boardSizeX - 2) + 1;
        int randY = rand() % (boardSizeY - 2) + 1;
        foodPos.setObjPos(randX, randY, '$');

        // Check for overlap with snake
        for (int i = 0; i < blockOff.getSize(); i++)
        {
            temp = blockOff.getElement(i);
            if (foodPos.isPosEqual(&temp))
            {
                same = true;
                break;
            }
        }
    } while (same);  // Retry until no overlap
}

objPos Food::getFoodPos() const {
    return foodPos;  // Return the current food position
}
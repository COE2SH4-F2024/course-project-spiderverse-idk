#include "Food.h"
#include <cstdlib>

Food::Food() {
    // Default food position and symbol
    objPos(0, 0, '$');
}

void Food::generateFood(const objPosArrayList& blockOff, int boardSizeX, int boardSizeY)
{
    int i;
    bool same = false;
    objPos temp;
    
    do
    {
        // Generate a random position
        int randX = rand() % (boardSizeX - 2) + 1;
        int randY = rand() % (boardSizeY - 2) + 1;
        foodPos.setObjPos(randX, randY, '$');

        for(i = 0; i<blockOff.getSize(); i++)
        {
            temp = blockOff.getElement(i);
            same &= foodPos.isPosEqual(&temp);
        }
        

    } while (same);
    
    

}

objPos Food::getFoodPos() const {
    return foodPos;  // Return the current food position
}
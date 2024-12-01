#include "Player.h"
#include "Food.h"
#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef, Food* foodRef) : mainFoodRef(foodRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(5, 5, '*'));
}



Player::~Player()
{
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic  
        char input;
        input = mainGameMechsRef->getInput(); //retrieve current user input
        
        if(input != 0)  // if not null character
        {
            switch(input) // carry out actions depending on user input
            {                      
                case 27:  // exit
                    mainGameMechsRef->setExitTrue();
                    break;

                case 'w': //up
                    if(myDir == STOP || myDir == LEFT || myDir == RIGHT)
                        myDir = UP;
                    break;
                
                case 's': //down
                    if(myDir == STOP || myDir == LEFT || myDir == RIGHT)
                        myDir = DOWN;
                    break;

                case 'a': //left
                    if(myDir == STOP || myDir == UP || myDir == DOWN)
                        myDir = LEFT;
                    break;

                case 'd': //right
                    if(myDir == STOP || myDir == UP || myDir == DOWN)
                        myDir = RIGHT;
                    break;

                default:
                    break;
            }
        }
}

void Player::movePlayer()
{
    int i, bSizeX, bSizeY, headX, headY;
    objPos nextPos, foodPos, bodyPart;
    bool foodHit;

    if (myDir != STOP)
    {
        bSizeX = mainGameMechsRef->getBoardSizeX();
        bSizeY = mainGameMechsRef->getBoardSizeY();
        nextPos = objPos(playerPosList->getHeadElement());
        headX = nextPos.pos->x;
        headY = nextPos.pos->y;

        // Update head position based on the direction
        switch (myDir)
        {
            case UP: headY--; break;
            case DOWN: headY++; break;
            case LEFT: headX--; break;
            case RIGHT: headX++; break;
            default: break;
        }

        // Wraparound logic
        if (headY >= bSizeY - 1) headY = 1;
        else if (headY <= 0) headY = bSizeY - 2;

        if (headX >= bSizeX - 1) headX = 1;
        else if (headX <= 0) headX = bSizeX - 2;

        // Check for collision with the body (excluding the head)
        for (i = 1; i < playerPosList->getSize(); i++)  // Start from 1 to exclude head
        {
            bodyPart = playerPosList->getElement(i);
            if (bodyPart.pos->x == headX && bodyPart.pos->y == headY)
            {
                // Collision with the body, game over
                mainGameMechsRef->setLoseFlag();  // Set lose flag to true
                mainGameMechsRef->setExitTrue();  // Exit the game
                return;  // Exit the function as the game is over
            }
        }


        // Check for food collision
        foodPos;
        foodHit = false;
        
        for(i = 0; i<mainFoodRef->getFoodListSize(); i++)
        {
            foodPos = mainFoodRef->getFoodPos(i);
            nextPos.setObjPos(headX, headY);

            if (nextPos.isPosEqual(&foodPos))  // Food eaten
            {
                if(foodPos.symbol == DEFAULTFOODSYM) //Normal food
                {
                    playerPosList->insertHead(nextPos);  // Grow the snake
                    mainGameMechsRef->incrementScore();  // Update score
                    mainFoodRef->generateFood(*playerPosList, bSizeX, bSizeY);  // Generate new food
                }
                else if(foodPos.symbol == SPECFOODSYM1) //Special food 1
                {
                    playerPosList->insertHead(nextPos);  // Grow the snake
                    mainGameMechsRef->incrementScore(); // Update score by 3
                    mainGameMechsRef->incrementScore();
                    mainGameMechsRef->incrementScore();
                    mainFoodRef->generateFood(*playerPosList, bSizeX, bSizeY);  // Generate new food
                }
                else if(foodPos.symbol == SPECFOODSYM2)//Special food 2
                {
                    playerPosList->insertHead(nextPos);  // Grow the snake
                    mainGameMechsRef->setScore(mainGameMechsRef->getScore()*2);  // Update score
                    mainFoodRef->generateFood(*playerPosList, bSizeX, bSizeY);  // Generate new food
                }
            }
        }

        if (!foodHit)
        {
            playerPosList->insertHead(nextPos);  // Regular move
            playerPosList->removeTail();  // Remove the tail to maintain snake length
        }
    }
}



int Player::getPlayerDir()
{
    return myDir;
}

int Player::getScore() const
{
    return playerPosList->getSize() - 1;  // Subtract 1 to map size 1 to score 0
}
#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(5,5,'*'));
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
    if(myDir != STOP)
    {
        int bSizeX = mainGameMechsRef->getBoardSizeX();
        int bSizeY = mainGameMechsRef->getBoardSizeY();


        objPos nextPos = objPos(playerPosList->getHeadElement());
        int headX = nextPos.pos->x;
        int headY = nextPos.pos->y;

        // PPA3 Finite State Machine logic
        // update the snake head location by 1 unit in the direction stored in the program
        switch(myDir)
        {
            case UP:
                headY--;
                break;
            
            case DOWN:
                headY++;
                break;
            
            case LEFT:
                headX--;
                break;

            case RIGHT:
                headX++;
                break;
            
            default:
                break;
        }

        //wraparound if past edge of screen
        //vertically
        if(headY>=bSizeY-1)
        {
            headY=1;
        }
        else if(headY<=0)
        {
            headY=bSizeY-2;
        }
        //horizontally
        if(headX>=bSizeX-1)
        {
            headX=1;
        }
        else if(headX<=0)
        {
            headX=bSizeX-2;
        }


        //insert new position to head and remove tail
        nextPos.setObjPos(headX,headY);
        playerPosList->insertHead(nextPos);
        playerPosList->removeTail();
    }
}

int Player::getPlayerDir()
{
    return myDir;
}

// More methods to be added
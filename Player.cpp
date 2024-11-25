#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = 5; //starting horizontal player position
    playerPos.pos->y = 5; //starting vertical player position
    playerPos.symbol = '*'; //player avatar symbol
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
                    
            mainGameMechsRef->clearInput(); //clear input so it doesnt get used multiple times
        }         
}

void Player::movePlayer()
{
    int bSizeX = mainGameMechsRef->getBoardSizeX();
    int bSizeY = mainGameMechsRef->getBoardSizeY();
    
    // PPA3 Finite State Machine logic
    // update the player location by 1 unit in the direction stored in the program
    switch(myDir)
    {
        case UP:
            playerPos.pos->y--;
            break;
        
        case DOWN:
            playerPos.pos->y++;
            break;
        
        case LEFT:
            playerPos.pos->x--;
            break;

        case RIGHT:
            playerPos.pos->x++;
            break;
        
        default:
            break;
    }

    //wraparound if past edge of screen
    //vertically
    if(playerPos.pos->y>=bSizeY-1)
    {
        playerPos.pos->y=1;
    }
    else if(playerPos.pos->y<=0)
    {
        playerPos.pos->y=bSizeY-2;
    }
    //horizontally
    if(playerPos.pos->x>=bSizeX-1)
    {
        playerPos.pos->x=1;
    }
    else if(playerPos.pos->x<=0)
    {
        playerPos.pos->x=bSizeX-2;
    }
}

// More methods to be added
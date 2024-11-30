#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define BOARDSIZEX 20
#define BOARDSIZEY 10

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

//Player & GameMechs class objects
Player* player;
GameMechs* game;
Food* food;

int main(void)
{

    Initialize();

    while(!game->getExitFlagStatus())   
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    //Player & GameMechs class objects
    game = new GameMechs();
    player = new Player(game);
    food = new Food();

    food->generateFood(*player->getPlayerPos(), BOARDSIZEX, BOARDSIZEY);
}

void GetInput(void)
{
    char inputChar = '\0';  // Declare it at the start
    game->clearInput();
    
    if (MacUILib_hasChar())
    {
        inputChar = MacUILib_getChar();
    }
    game->setInput(inputChar);

    // Debug: Generate new food with key 'F'
    if (inputChar == 'F') {
         food->generateFood(*player->getPlayerPos(), BOARDSIZEX, BOARDSIZEY);
    }
}

void RunLogic(void)
{
    objPos tempHeadPos;
    objPos tempFoodPos;
    
    //update and move player object
    player->updatePlayerDir();
    player->movePlayer();
    tempHeadPos = player->getPlayerPos()->getHeadElement();
    tempFoodPos = food->getFoodPos();

    // objPos foodPosition(food->getFoodPos().pos->x, food->getFoodPos().pos->y, food->getFoodPos().symbol);
    if (tempHeadPos.isPosEqual(&tempFoodPos))
    {
        // Regenerate food at a new random position, avoiding the player
        food->generateFood(*player->getPlayerPos(), BOARDSIZEX, BOARDSIZEY);
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    int i, j, k;
    int printed = 0;
    
    //retrieve player position
    objPosArrayList* posList = player->getPlayerPos();
    objPos temp;

    //retrieve food position
    int foodX = food->getFoodPos().pos->x;
    int foodY = food->getFoodPos().pos->y;

    //iterate through game board, printing characters in grid
    for(i = 0; i < game->getBoardSizeY(); i++)
    {
        for(j = 0; j < game->getBoardSizeX(); j++)
        {
            //iterate through snake positions, printing them
            for(k = 0; k < posList->getSize(); k++)
            {
                temp.setObjPos(posList->getElement(k));

                if(j == temp.pos->x && i == temp.pos->y)
                {
                    MacUILib_printf("%c",temp.symbol);
                    printed = 1;

                    break;
                }
            }
            
            if(!printed)
            {
                if(i == 0 || j == 0 || i == game->getBoardSizeY()-1 || j == game->getBoardSizeX()-1) //print frame
                {
                    MacUILib_printf("#");
                }
                else if(j == foodX && i == foodY) //print food symbol
                {
                    MacUILib_printf("%c", food->getFoodPos().symbol);
                }
                else //print empty space
                {
                    MacUILib_printf(" ");
                }
            }

            printed = 0;
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n");

    MacUILib_printf("Input Character: %c\n", game->getInput());
    MacUILib_printf("Direction: %d", player->getPlayerDir());
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete game;  // Delete the GameMechs object
    delete player; // Delete the Player object
    delete food;

    MacUILib_clearScreen();    

    MacUILib_uninit();
}

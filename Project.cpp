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

//objPosArrayList Test
objPosArrayList* test;

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

    food->generateFood(player->getPlayerPos(), BOARDSIZEX, BOARDSIZEY);

    //objPosArrayList Test
    test = new objPosArrayList();
}

void GetInput(void)
{
    char inputChar = '\0';  // Declare it at the start
    
    if (MacUILib_hasChar())
    {
        inputChar = MacUILib_getChar();
    }
    game->setInput(inputChar);

    // Debug: Generate new food with key 'F'
    if (inputChar == 'F') {
        food->generateFood(player->getPlayerPos(), BOARDSIZEX, BOARDSIZEY);
    }
}

void RunLogic(void)
{
    //update and move player object
    player->updatePlayerDir();
    player->movePlayer();

    objPos foodPosition(food->getFoodPos().pos->x, food->getFoodPos().pos->y, food->getFoodPos().symbol);
    if (player->getPlayerPos().isPosEqual(&foodPosition))
    {
        // Regenerate food at a new random position, avoiding the player
        food->generateFood(player->getPlayerPos(), BOARDSIZEX, BOARDSIZEY);
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    int i, j;
    
    //retrieve player position
    int x = player->getPlayerPos().pos->x;
    int y = player->getPlayerPos().pos->y;

    //retrieve food position
    int foodX = food->getFoodPos().pos->x;
    int foodY = food->getFoodPos().pos->y;

    //iterate through game board, printing characters in grid
    for(i = 0; i < game->getBoardSizeY(); i++)
    {
        for(j = 0; j < game->getBoardSizeX(); j++)
        {
            if(i == 0 || j == 0 || i == game->getBoardSizeY()-1 || j == game->getBoardSizeX()-1) //print frame
            {
                MacUILib_printf("#");
            } 
            else if(j == x && i == y) //print player symbol
            {
                MacUILib_printf("%c", player->getPlayerPos().symbol);
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
        MacUILib_printf("\n");
    }
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete game;  // Delete the GameMechs object
    delete player; // Delete the Player object
    delete test; //objPosArrayList Test
    delete food;

    MacUILib_clearScreen();    

    MacUILib_uninit();
}

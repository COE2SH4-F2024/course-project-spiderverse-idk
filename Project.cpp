#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

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
}

void RunLogic(void)
{
    //update and move player object
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    int i;
    int j;
    
    //retrieve player position
    int x = player->getPlayerPos().pos->x;
    int y = player->getPlayerPos().pos->y;

    //iterate through game board, printing characters in grid
    for(i=0;i<game->getBoardSizeY();i++)
    {
        for(j=0;j<game->getBoardSizeX();j++)
        {
            if(i==0 || j==0 || i==game->getBoardSizeY()-1 || j==game->getBoardSizeX()-1) //print frame
            {
                MacUILib_printf("#");
            } 
            else if(j == x && i == y) //print arbitrary symbols (OBJPOS TESTER, DELETE LATER)
            {
                MacUILib_printf("%c",player->getPlayerPos().symbol);
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

    MacUILib_clearScreen();    

    MacUILib_uninit();
}

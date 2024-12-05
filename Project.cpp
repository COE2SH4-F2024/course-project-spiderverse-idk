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

    // Create objects for GameMechs, Player, and Food
    game = new GameMechs();
    food = new Food(5);  // Create Food object
    
    // Now pass both `game` and `food` to the Player constructor
    player = new Player(game, food);  // Pass both game and food to the constructor

    // Generate initial food at a random position
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

    // Update and move player object
    player->updatePlayerDir();
    player->movePlayer();
    tempHeadPos = player->getPlayerPos()->getHeadElement();

    if (game->getLoseFlagStatus()) {
        // If game is lost, stop the game and return (freeze the game)
        return;
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    int i, j, k;
    int score;
    int printed = 0;
    
    //retrieve player position
    objPosArrayList* posList = player->getPlayerPos();
    objPos temp;

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

            //iterate through food positions, printing them
            if(!printed)
            {
                for(k = 0; k < food->getFoodListSize(); k++)
                {
                    temp.setObjPos(food->getFoodPos(k));

                    if(j == temp.pos->x && i == temp.pos->y)
                    {
                        MacUILib_printf("%c",temp.symbol);
                        printed = 1;

                        break;
                    }
                }
            }

            if(!printed)
            {
                if(i == 0 || j == 0 || i == game->getBoardSizeY()-1 || j == game->getBoardSizeX()-1) //print frame
                {
                    MacUILib_printf("#");
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

    // Display the score
    score = player->getScore();  // Get the current score
    MacUILib_printf("Score: %d\n", score);  // Print the score

    // Display input character and direction (can be retained from previous)
    MacUILib_printf("Input Character: %c\n", game->getInput());
    MacUILib_printf("Direction: %d\n", player->getPlayerDir());

    //Describe food types
    MacUILib_printf("Collect %c to get 1 point\n", DEFAULTFOODSYM);
    MacUILib_printf("Collect %c to get 3 points\n", SPECFOODSYM1);
    MacUILib_printf("Collect %c to double your points\n", SPECFOODSYM2);


    // Check for game over condition
    if (game->getLoseFlagStatus()) 
    {
        MacUILib_printf("\nGame Over! You crashed into yourself!\n");

        // Ask if the player wants to restart or exit
        MacUILib_printf("Press 'p' to play again or 'Esc' to exit.\n");

        // Freeze the game until player presses 'p' or 'Esc'
        char inputChar = '\0';
        while (true) {
            if (MacUILib_hasChar()) {
                inputChar = MacUILib_getChar();
                if (inputChar == 'p') {
                    // Restart the game
                    Initialize();
                    break;
                } else if (inputChar == 27) {  // Escape key (ASCII value 27)
                    game->setExitTrue();  // Exit the game
                    break;
                }
            }
        }
        return;  // Exit to prevent further game updates
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
    delete food;

    MacUILib_clearScreen();    

    MacUILib_uninit();
}

#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

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

//arbitrary objPos testers (OBJPOS TESTER, DELETE LATER)
objPos arb1;
objPos arb2;
objPos arb3;


int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    //arbitrary objPos testers (OBJPOS TESTER, DELETE LATER)
    arb1 = objPos(4,5,'A');
    arb2 = objPos(8,7,'B');
    arb3 = objPos(2,6,'C');
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    


    int i;
    int j;
    //iterate through game board, printing characters in grid
    for(i=0;i<BOARDSIZEY;i++)
    {
        for(j=0;j<BOARDSIZEX;j++)
        {
            if(i==0 || j==0 || i==BOARDSIZEY-1 || j==BOARDSIZEX-1) //print frame
            {
                MacUILib_printf("#");
            } 
            else if(j== arb1.pos->y && i==arb1.pos->x) //print arbitrary symbols (OBJPOS TESTER, DELETE LATER)
            {
                MacUILib_printf("%c",arb1.symbol);
            }
            else if(j== arb2.pos->y && i==arb2.pos->x) //print arbitrary symbols (OBJPOS TESTER, DELETE LATER)
            {
                MacUILib_printf("%c",arb2.symbol);
            }
            else if(j== arb3.pos->y && i==arb3.pos->x) //print arbitrary symbols (OBJPOS TESTER, DELETE LATER)
            {
                MacUILib_printf("%c",arb3.symbol);
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
    MacUILib_clearScreen();    

    MacUILib_uninit();
}

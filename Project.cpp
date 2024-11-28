#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
#define height 10
#define length 20


Player *myPlayer; //global pointer
GameMechs *myGM; // global pointer


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    myGM = new GameMechs();
    myPlayer=new Player(myGM);

}

void GetInput(void)
{
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myPlayer->border();
    // myGM->setInput(0);
}

void DrawScreen(void)
{
    //int i,j;
    MacUILib_clearScreen();

    //implement copy assignment operator to make work
    objPos playerPos=myPlayer->getPlayerPos();
    //MacUILib_printf("Player[x,y]=[%d,%d], %c",playerPos.pos->x,playerPos.pos->y,playerPos.symbol); 

    for (int i=0;i<height;i++)
    {
        for (int j=0;j<length;j++)
        {
            if (i==0 || i==height-1 || j==0 ||j==length-1) {
                MacUILib_printf("#"); 
            } else if (playerPos.pos->x == j && playerPos.pos->y == i)
                MacUILib_printf("%c", playerPos.symbol);
            else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    }
    //MacUILib_printf("Player[x,y]=[%d,%d], %c",playerPos.pos->x,playerPos.pos->y,playerPos.symbol); 
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}

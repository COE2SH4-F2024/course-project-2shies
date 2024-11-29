#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define height 10
#define length 20


Player *myPlayer; //global pointer
GameMechs *myGM; // global pointer
Food *myFood; //global pointer


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

    srand(time(NULL));


    myGM = new GameMechs();
    myPlayer=new Player(myGM);
    myFood = new Food(myGM->getBoardSizeX(), myGM->getBoardSizeY());

    //objPos blockOff = myPlayer->getPlayerPos(); //this way doesn't seem to work- do it directly
   //myFood->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    //check we can randomly move food around 
    /* if(myGM->getInput() == 't') {
        myFood->generateFood(myPlayer->getPlayerPos());
        myGM->setInput(0);
    } */
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    // myGM->setInput(0);
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //implement copy assignment operator to make work
    objPosArrayList* playerPos=myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();


    //objPos foodPos = myFood->getFoodPos();
    //MacUILib_printf("Player[x,y]=[%d,%d], %c",playerPos.pos->x,playerPos.pos->y,playerPos.symbol); 

    for (int i=0;i<height;i++)
    {
        for (int j=0;j<length;j++)
        {
            for(int k = 0; k < playerSize; k++) {
                objPos thisSeg = playerPos->getElement(k);
                //check if current segment at x y matches the (j,i) coordinates. If yes, print the symbol

                //skip if else block below if you have printed something in that spot
            }
            if (i==0 || i==height-1 || j==0 ||j==length-1) {
                MacUILib_printf("#"); 
            }
            //} else if (playerPos.pos->x == j && playerPos.pos->y == i) {
            //    MacUILib_printf("%c", playerPos.symbol);
            //else if (foodPos.pos->x == j && foodPos.pos->y == i) {
            //    MacUILib_printf("%c", foodPos.symbol);
            else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    }
    //MacUILib_printf("Food[x,y]=[%d,%d], %c",foodPos.pos->x,foodPos.pos->y,foodPos.symbol); 
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
    delete myFood;

    MacUILib_uninit();
}

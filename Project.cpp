#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000


Player *myPlayer; //global pointer
objPosArrayList* playerPosList;

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
    myFood = new Food(myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer=new Player(myGM,myFood);

    myFood->generateFood(myPlayer->getPlayerPos()->getHeadElement());
}

void GetInput(void)
{
    //check we can randomly move food around 
    if(myGM->getInput() == 't') {
        myFood->generateFood(myPlayer->getPlayerPos()->getHeadElement());
        myGM->setInput(0);
    }
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
    //myGM->setInput(0);
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    /*if (!myGM || !myPlayer || !myFood) {
        MacUILib_printf("big problemo \n");
    }*/
    //implement copy assignment operator to make work
    objPosArrayList* playerPos=myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    objPos tempBody;


    bool snake;

    objPos tempFood;
    objPos foodPos = myFood->getFoodPos();
    //MacUILib_printf("Player[x,y]=[%d,%d], %c",playerPos.pos->x,playerPos.pos->y,playerPos.symbol); 

    for (int i=0;i<myGM->getBoardSizeY();i++)
    {
        for (int j=0;j<myGM->getBoardSizeX();j++)
        {
            snake = false;
            for(int k = 0; k < playerSize; k++) {
                tempBody=playerPos->getElement(k); //this was error forgot to assign 
                if(j == tempBody.pos->x && i == tempBody.pos->y) {
                    MacUILib_printf("%c", tempBody.getSymbol());
                    snake = true;
                    break;
                }
            }

            if(snake) continue;
            if (j==foodPos.pos->x && i==foodPos.pos->y){
                MacUILib_printf("%c", foodPos.getSymbol());
                //snake = true;
                break;
            }

            if(snake) continue;
            if (i==0 || i==myGM->getBoardSizeY()-1 || j==0 ||j==myGM->getBoardSizeX()-1) {
                MacUILib_printf("#"); 
            } else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Food[x,y]=[%d,%d], %c",foodPos.pos->x,foodPos.pos->y,foodPos.symbol); 
    /* if(myGM->getLoseFlagStatus()) {
        MacUILib_clearScreen();
        MacUILib_printf("Womp womp, you lost. Your final score was %d", myGM->getScore());
    } */
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    myGM->~GameMechs();
    myPlayer->~Player();
    delete myFood;

    MacUILib_uninit();
}

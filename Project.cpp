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
objPosArrayList* playerPosList; //global pointer

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

    srand(time(NULL)); //for random food position generation

    myGM = new GameMechs();
    myFood = new Food(myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer=new Player(myGM,myFood);

    myFood->generateFood(myPlayer->getPlayerPos()->getHeadElement());
}

void GetInput(void)
{
    //for testing random food position generation
    /* if(myGM->getInput() == 't') {
        myFood->generateFood(myPlayer->getPlayerPos()->getHeadElement());
        myGM->setInput(0);
    } */
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
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
                tempBody=playerPos->getElement(k);
                if(j == tempBody.pos->x && i == tempBody.pos->y) {
                    MacUILib_printf("%c", tempBody.getSymbol());
                    snake = true;
                    break;
                }
            }

            if(snake) continue;
            if (j==foodPos.pos->x && i==foodPos.pos->y){
                MacUILib_printf("%c", foodPos.getSymbol());
                //snake = true; replaced with continue
                continue;
            }

            //if(snake) continue; redundant
            if (i==0 || i==myGM->getBoardSizeY()-1 || j==0 ||j==myGM->getBoardSizeX()-1) {
                MacUILib_printf("#"); 
            } else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n", myGM->getScore());
    //MacUILib_printf("Food[x,y]=[%d,%d], %c",foodPos.pos->x,foodPos.pos->y,foodPos.symbol); 
    if(myGM->getExitFlagStatus()) {
        MacUILib_clearScreen();
        if(myGM->getLoseFlagStatus())
            MacUILib_printf("Womp womp, you lost. Your final score was %d\n", myGM->getScore());
        else
            MacUILib_printf("You quit the game. Your final score was %d\n", myGM->getScore());
    } 
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen(); was deleting exit messages (lose message/quitting message)

    //delete off the heap
    myGM->~GameMechs();
    myPlayer->~Player();
    playerPosList->~objPosArrayList();
    delete myFood;

    MacUILib_uninit();
}

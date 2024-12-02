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
objPosArrayList* foodBucket; //global pointer
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

    myFood->generateFood(myPlayer->getPlayerPos());
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
    objPosArrayList* foodBucket = myFood->getFoodList();
    int playerSize = playerPos->getSize();
    objPos tempBody, tempFood;

    bool itemPlaced; //to check if item is already placed at a point

    //for testing player
    //MacUILib_printf("Player[x,y]=[%d,%d], %c",playerPos.pos->x,playerPos.pos->y,playerPos.symbol); 

    for (int i=0;i<myGM->getBoardSizeY();i++)
    {
        for (int j=0;j<myGM->getBoardSizeX();j++)
        {
            itemPlaced = false;
            for(int k = 0; k < playerSize; k++) //prints player body
            {
                tempBody=playerPos->getElement(k);
                if(j == tempBody.pos->x && i == tempBody.pos->y) 
                {
                    MacUILib_printf("%c", tempBody.getSymbol());
                    itemPlaced = true;
                    break;
                }
            }

            if(itemPlaced) continue;
            for(int k = 0; k < foodBucket->getSize(); k++) //prints food
            {
                tempFood=foodBucket->getElement(k);
                if(tempFood.pos->x==j && tempFood.pos->y== i) 
                {
                    MacUILib_printf("%c", tempFood.getSymbol());
                    itemPlaced = true;
                    break;
                }
            }

            if(itemPlaced) continue; 
            if (i==0 || i==myGM->getBoardSizeY()-1 || j==0 ||j==myGM->getBoardSizeX()-1) //prints border and empty spaces
            {
                MacUILib_printf("#"); 
            } else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore()); //display score
    MacUILib_printf("\nTo play, use WASD to move your snake. Eat the food to grow, but watch out for the minus signs...\n"); //game instructions
    MacUILib_printf("If you collide with yourself or your score gets too low, you lose!\n"); //game instructions
    MacUILib_printf("Press space to exit the game.\n"); //game instructions

    //for testing food
    //MacUILib_printf("Food[x,y]=[%d,%d], %c",foodPos.pos->x,foodPos.pos->y,foodPos.symbol); 

    if(myGM->getExitFlagStatus()) 
    {
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

    //delete off the heap for no memory leakage
    myGM->~GameMechs();
    myPlayer->~Player();
    myFood->~Food();

    MacUILib_uninit();
}




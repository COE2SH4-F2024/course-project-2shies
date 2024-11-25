#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
#define height 10
#define length 20

Player *myPlayer; //global pointer

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



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

    myPlayer=new Player(nullptr);

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    //int i,j;
    MacUILib_clearScreen();

    //implement copy assignment operator to make work
    objPos playerPos=myPlayer->getPlayerPos();
    MacUILib_printf("Player[x,y]=[%d,%d], %c",playerPos.pos->x,playerPos.pos->y,playerPos.symbol); 

    /* for (i=0;i<height;i++)
    {
        for (j=0;j<length;j++)
        {
            if (i==0 || i==height-1 || j==0 ||j==length-1) 
            {
                cout<<"#"<<endl; //which one to use
                MacUILib_printf("#"); 
            }
            else if (i==2&&j==9)
                cout<<"P"<<endl;
            else if (i==6&&j==12)
                cout<<"~"<<endl;
            else if (i==7&&j==3)
                cout<<"o"<<endl;
            else if (i==4&&j==16)
                cout<<"+"<<endl;
            else if (i==3&j==14)
                cout<<"X"<<endl;
            else
                cout<<" "<<endl;
        }
    } */
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;

    MacUILib_uninit();
}

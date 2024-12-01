#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* foodref)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();

    food=foodref;

    myDir = STOP;

    // more actions to be included
    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos);
    /* //make multiple to run
    objPos headPos1(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos1);
    objPos headPos2(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos2);
    objPos headPos3(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos3); */
    /*
    playerPos.pos->x=mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y=mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol='@';*/

}


Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
    //no keyword "new" in constuctor therefore no heap memebers to delete
    //leaving empty for now
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    //get input from pookie
    char input = mainGameMechsRef->getInput();

        // PPA3 input processing logic       
    switch(input)
    {
        case ' ': //exit
            mainGameMechsRef->setExitTrue();
            break;
        case 'W': case 'w':
            {
                if (myDir==LEFT || myDir==RIGHT || myDir==STOP)
                {
                    myDir=UP;
                }
                break;
            }
            case 'A': case 'a':
            {
                if (myDir==UP || myDir==DOWN || myDir==STOP)
                {
                    myDir=LEFT;
                } 
                break;           
            }
            case 'D': case 'd':
            {
                if (myDir==UP || myDir==DOWN || myDir==STOP)
                {
                    myDir=RIGHT;
                } 
                break; 
            }
            case 'S': case 's':
            {
                if (myDir==LEFT || myDir==RIGHT || myDir==STOP)
                {
                    myDir=DOWN;
                }
                break;
            }
            default:
                break;
    } 
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{

    updatePlayerDir();
    //insert new objPos in head of list
    //check if delete tail element
    objPos tempHead;
    tempHead=playerPosList->getHeadElement();

    //Food food(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2);

    

    //temp objPos calculate new head pos
    //get head element of playerposlist

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case LEFT:    
            tempHead.pos->x--; // Shift Left
            if (tempHead.pos->x==0)
            {
                tempHead.pos->x=(mainGameMechsRef->getBoardSizeX()-1);
            }

            /* if (temp.pos->x!=food.getFoodPos().pos->x)//food position)
            {
                playerPosList->removeTail();
            } */

            //for loop to check if any position of head is same

            playerPosList->insertHead(tempHead);
            playerPosList->removeTail();
            
            break;

        case RIGHT:
            tempHead.pos->x++; // Shift Right
            if (tempHead.pos->x==(mainGameMechsRef->getBoardSizeX()-1))
            {
                tempHead.pos->x=1;
            }
            playerPosList->insertHead(tempHead);
            playerPosList->removeTail();
            break;
        
        case DOWN:
            tempHead.pos->y++; // Shift String down by 1 Character
            if (tempHead.pos->y==(mainGameMechsRef->getBoardSizeY()-1))
            {
                tempHead.pos->y=1;
            }
            playerPosList->insertHead(tempHead);
            playerPosList->removeTail();
            break;

        case UP:
            tempHead.pos->y--; // Shift String up by 1 Character
            if (tempHead.pos->y==0)
            {
                tempHead.pos->y=(mainGameMechsRef->getBoardSizeY()-1);
            }
            playerPosList->insertHead(tempHead);
            playerPosList->removeTail();
            break;
    }

    if (checkFoodConsumption()){
        increasePlayerLength();
        food->generateFood(tempHead); //will probably need to change
        mainGameMechsRef->incrementScore();
    }

}


//get food pos
//check for food consumption
//if food consumed increment snake length
//generate new food

// More methods to be added
bool Player::checkFoodConsumption(){
    objPos tempHead;
    tempHead=playerPosList->getHeadElement();

    objPos tempFood;
    tempFood=food->getFoodPos();

    if (tempHead.pos->x==tempFood.pos->x&&tempHead.pos->y==tempFood.pos->y)
    {
        true;
    }
    false;
}

void Player::increasePlayerLength(){
    objPos tempHead;
    playerPosList->insertHead(tempHead);
}
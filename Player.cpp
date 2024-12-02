#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* foodref)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();

    food=foodref;

    myDir = STOP;

    // more actions to be included
    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList->insertHead(headPos);
    /* 
    Used to test iteration 3 part 1 (make multiple to run)
    objPos headPos1(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos1);
    objPos headPos2(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos2);
    objPos headPos3(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos3); */
}


Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic       
    switch(input)
    {
        case ' ': //exit key
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
}

void Player::movePlayer()
{
   
    updatePlayerDir();

    objPos tempHead;
    tempHead=playerPosList->getHeadElement();
    //temp objPos calculate new head pos
    //get head element of playerposlist

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case LEFT:    
            tempHead.pos->x--; 
            if (tempHead.pos->x==0)
            {
                tempHead.pos->x=(mainGameMechsRef->getBoardSizeX()-2);
            }
            break;

        case RIGHT:
            tempHead.pos->x++; 
            if (tempHead.pos->x==(mainGameMechsRef->getBoardSizeX()-1))
            {
                tempHead.pos->x=1;
            }
            break;
        
        case DOWN:
            tempHead.pos->y++; 
            if (tempHead.pos->y==(mainGameMechsRef->getBoardSizeY()-1))
            {
                tempHead.pos->y=1;
            }
            break;

        case UP:
            tempHead.pos->y--; 
            if (tempHead.pos->y==0)
            {
                tempHead.pos->y=(mainGameMechsRef->getBoardSizeY()-2);
            }
            break;
    }

    playerPosList->insertHead(tempHead);
    playerPosList->removeTail(); //for regular size

    if (checkFoodConsumption())
    {
        objPosArrayList* foodBucket = food->getFoodList();
        objPos tempFood,tempTail;
        tempTail = playerPosList->getTailElement();
        char foodChar = 0;
        
        for(int i = 0; i < 5; i++) 
        {
            tempFood = foodBucket->getElement(i);
            foodChar = tempFood.getSymbolIfPosEqual(&tempHead);
            if(foodChar != 0) break; //getSymbolIfPosEqual() returns 0 if position is not equal
        }

        if(foodChar == '+') //adds 5 to score and increases player body by 5
        {
            for(int i = 0; i < 5; i++) 
            {
                mainGameMechsRef->incrementScore();
                playerPosList->insertTail(tempTail);
            }
        } 

        else if (foodChar == '-') //removes 5 from score and decreases player body by 5
        {
            for(int i = 0; i < 5; i++) 
            {
                mainGameMechsRef->reduceScore();
                playerPosList->removeTail();
                
                if(mainGameMechsRef->getScore() < 0) //to ensure player body is never less than 1 character and just displays lose screen
                {
                    mainGameMechsRef->setScore(); //sets score to 0 to ensure no negative score displayed
                    mainGameMechsRef->setLoseFlag();
                    mainGameMechsRef->setExitTrue();
                } 
            }
        } 
        else if (foodChar == '^') //regular food (increase by 1)
        {
            increasePlayerLength();
            mainGameMechsRef->incrementScore();
        }


        food->generateFood(playerPosList); //generate new food in new posisition after food collision
    } 
    
    else if(checkSelfCollision()) //lose screen if player head hits any part of the body
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

// More methods to be added
bool Player::checkFoodConsumption()
{
    objPos tempHead, tempFood;
    tempHead=playerPosList->getHeadElement();
    objPosArrayList* foodBucket = food->getFoodList();

    for(int i = 0; i < foodBucket->getSize(); i++) 
    {
        tempFood=foodBucket->getElement(i);
        if (tempHead.pos->x==tempFood.pos->x&&tempHead.pos->y==tempFood.pos->y)
        {
            return true;
        }
    }
    return false;
}

void Player::increasePlayerLength()
{
    objPos tempHead;
    tempHead=playerPosList->getHeadElement();
    playerPosList->insertHead(tempHead);
}

bool Player::checkSelfCollision() 
{
    objPos tempHead;
    tempHead=playerPosList->getHeadElement();
    
    for(int i = 1; i < playerPosList->getSize(); i++) 
    {
        objPos tempElement = playerPosList->getElement(i);
        if(tempHead.isPosEqual(&tempElement))
            return true;
    }
    return false;
}
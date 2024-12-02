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
    /* //Used to test iteration 3 part 1 (make multiple to run)
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
    //no keyword "new" in constuctor therefore no heap memebers to delete
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

    if (checkFoodConsumption()){
        objPosArrayList* foodBucket = food->getFoodList();
        objPos tempFood;
        objPos tempTail;
        char foodChar = 0;

        tempTail = playerPosList->getTailElement();
        
        for(int i = 0; i < 5; i++) {
            tempFood = foodBucket->getElement(i);
            foodChar = tempHead.getSymbolIfPosEqual(&tempFood);
            if(foodChar != 0) break;
        }

        if(foodChar == '+') {
            for(int i = 0; i < 5; i++) {
                mainGameMechsRef->incrementScore();
                playerPosList->insertTail(tempTail);
            }
        } 
        else if (foodChar == '-') {
            for(int i = 0; i < 5; i++) {
                mainGameMechsRef->reduceScore();
                playerPosList->removeTail();
                
                if(mainGameMechsRef->getScore() < 0) {
                    mainGameMechsRef->setLoseFlag();
                    mainGameMechsRef->setExitTrue();
                } 
            }
        } 
        else if (foodChar == '^') {
            increasePlayerLength();
            mainGameMechsRef->incrementScore();
        }
        food->generateFood(playerPosList); 
    } 
    
    else if(checkSelfCollision()) {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    playerPosList->insertHead(tempHead);
    playerPosList->removeTail(); //for regular size
    

}

// More methods to be added
bool Player::checkFoodConsumption(){
    objPos tempHead;
    objPosArrayList* foodBucket = food->getFoodList();
    tempHead=playerPosList->getHeadElement();

    objPos tempFood;
    //tempFood=food->getFoodPos();
    for(int i = 0; i < foodBucket->getSize(); i++) {
        tempFood=foodBucket->getElement(i);
        if (tempHead.pos->x==tempFood.pos->x&&tempHead.pos->y==tempFood.pos->y)
        {
            return true;
        }
    }

    return false;
}

void Player::increasePlayerLength(){
    objPos tempHead;
    tempHead=playerPosList->getHeadElement();
    playerPosList->insertHead(tempHead);
}

bool Player::checkSelfCollision() {
    objPos tempHead;
    tempHead=playerPosList->getHeadElement();
    for(int i = 1; i < playerPosList->getSize(); i++) {
        objPos tempElement = playerPosList->getElement(i);
        if(tempHead.isPosEqual(&tempElement))
            return true;
    }
    return false;
}
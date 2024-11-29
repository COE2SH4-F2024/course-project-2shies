#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    // more actions to be included
    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(headPos);

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
}

void Player::movePlayer()
{

    updatePlayerDir();
    //insert new objPos in head of list
    //check if delete tail element
    objPos temp;
    temp=playerPosList->getHeadElement();

    //Food food(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2);

    

    //temp objPos calculate new head pos
    //get head element of playerposlist

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case LEFT:    
            temp.pos->x--; // Shift Left
            if (temp.pos->x==0)
            {
                temp.pos->x=(mainGameMechsRef->getBoardSizeX()-1);
            }

            if (temp.pos->x!=food.getFoodPos().pos->x)//food position)
            {
                playerPosList->removeTail();
            }

            //for loop to check if any position of head is same

            playerPosList->insertHead(temp);
            
            break;

        case RIGHT:
            playerPos.pos->x++; // Shift String Right by 1 Character
            if (playerPos.pos->x==(mainGameMechsRef->getBoardSizeX()-1))
            {
                playerPos.pos->x=1;
            }
            break;
        
        case DOWN:
            playerPos.pos->y++; // Shift String down by 1 Character
            if (playerPos.pos->y==(mainGameMechsRef->getBoardSizeY()-1))
            {
                playerPos.pos->y=1;
            }
            break;

        case UP:
            playerPos.pos->y--; // Shift String up by 1 Character
            if (playerPos.pos->y==0)
            {
                playerPos.pos->y=(mainGameMechsRef->getBoardSizeY()-1);
            }
            break;
    }
}


// More methods to be added
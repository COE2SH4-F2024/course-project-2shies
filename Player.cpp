#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x=mainGameMechsRef->getBoardSizeX() / 2; //later will be boardsize/2
    playerPos.pos->y=mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol='@';

}


Player::~Player()
{
    // delete any heap members here
    //no keyword "new" in constuctor therefore no heap memebers to delete
    //leaving empty for now
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    //get input from pookie
    char input = mainGameMechsRef->getInput();

        // PPA3 input processing logic       
    switch(input)
    {
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
    // PPA3 Finite State Machine logic
}

// More methods to be added
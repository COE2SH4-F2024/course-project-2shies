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
    switch(myDir)
    {
        case LEFT:    
            playerPos.pos->x--; // Shift String Left by 1 Character
            break;

        case RIGHT:
            playerPos.pos->x++; // Shift String Right by 1 Character
            break;
        
        case DOWN:
            playerPos.pos->y++; // Shift String down by 1 Character
            break;

        case UP:
            playerPos.pos->y--; // Shift String up by 1 Character
            break;
    }
}

void Player::border()
{
    if (playerPos.pos->y==9)
    {
        playerPos.pos->y=1;
    }
    else if (playerPos.pos->y==0)
    {
        playerPos.pos->y=8;
    }

    if (playerPos.pos->x==19)
    {
        playerPos.pos->x=1;
    }
    else if (playerPos.pos->x==0)
    {
        playerPos.pos->x=19;
    }
}
// More methods to be added
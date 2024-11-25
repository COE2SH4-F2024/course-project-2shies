#include "GameMechs.h"

GameMechs::GameMechs()
{
    char input = 0;
    bool exitFlag = false;
    bool loseFlag = false;
    int score = 0;

    int boardSizeX = 20;
    int boardSizeY = 10;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    char input = 0;
    bool exitFlag = false;
    bool loseFlag = false;
    int score = 0;

    int boardSizeX = boardX;
    int boardSizeY = boardY; 
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{

}
    

char GameMechs::getInput()
{
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
    return input;

}

int GameMechs::getScore() const
{

}

void GameMechs::incrementScore()
{
    
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{

}

void GameMechs::setLoseFlag()
{
    
}

void GameMechs::setInput(char this_input)
{

}

void GameMechs::clearInput()
{

}

// More methods should be added here
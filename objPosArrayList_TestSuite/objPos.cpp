#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
objPos::objPos(const objPos& thisPos)
{
    
    pos=new Pos(*thisPos.pos); //using copy constructor
    //if (pos!=nullptr) delete pos;
    //pos->x=thisPos.pos->x;
    //pos->y=thisPos.pos->y;
    symbol=thisPos.symbol;
}
objPos::~objPos()
{
    delete pos;
}
objPos& objPos::operator=(const objPos &thisPos)
{
    if(this != &thisPos)
    {
        //if(pos!=nullptr) delete pos;
        //pos=new Pos;
        //pos->x=thisPos.pos->x;
        //pos->y=thisPos.pos->y;
        //symbol=thisPos.symbol;
        *pos=*thisPos.pos;
        symbol=thisPos.symbol;
    }
    return *this;
}

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}

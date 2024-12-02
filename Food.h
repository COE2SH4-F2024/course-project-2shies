#ifndef FOOD_H
#define FOOD_H

//do we need these all? or do they need this class
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
//#include "Player.h"

class Food {

    private:
        objPos foodPos;
        int boardSizeX;
        int boardSizeY;

    public:
        Food(int boardX, int boardY);
        ~Food();

        Food(const Food &other);
        Food& operator=(const Food &other);

        void generateFood(objPos blockOff);
        objPos getFoodPos() const;

};

#endif
#include "Food.h"
#include <ctime>
#include <cstdlib>



Food::Food(int boardX, int boardY){
    foodPos = objPos(-1, -1, '^'); //off board initialization
    boardSizeX = boardX;
    boardSizeY = boardY; 
   
}

Food::~Food() {
}

Food::Food(const Food &other) {
    this->foodPos = other.foodPos;
}

Food& Food::operator=(const Food &other) {
    if (this != &other) {
        this->foodPos = other.foodPos;
    }
}

void Food::generateFood(objPos blockOff) {

    
    //int boardSizeX = thisGMRef->getBoardSizeX();
    //int boardSizeY = thisGMRef->getBoardSizeY();
    int bitVector[11][21] = {0}; // ideally would put boardsize x and y variables here but need to figure out how to do that for an array
    bool placedFood = false;

    while (!placedFood) {
        int x = (rand() % (boardSizeX - 2)) + 1;
        int y = (rand() % (boardSizeY - 2)) + 1;

        if(bitVector[y][x] == 0 && !(blockOff.pos->x == x && blockOff.pos->y == y)) {
            foodPos.pos->x = x;
            foodPos.pos->y = y;
            bitVector[y][x] = 1;
            placedFood = true;
        }
    }
}

objPos Food::getFoodPos() const {
    return foodPos;
}
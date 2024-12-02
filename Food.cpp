#include "Food.h"
#include <ctime>
#include <cstdlib>



Food::Food(int boardX, int boardY)
{
    foodPos = objPos(-1, -1, '+'); //off board initialization
    boardSizeX = boardX;
    boardSizeY = boardY; 

    foodBucket = new objPosArrayList();
}

Food::~Food() 
{

}

Food::Food(const Food &other) 
{
    this->foodPos = other.foodPos;
}

Food& Food::operator=(const Food &other) 
{
    if (this != &other) {
        this->foodPos = other.foodPos;
    }
}

void Food::generateFood(objPosArrayList* blockOff) 
{
    int bitVector[16][31] = {0}; // ideally would put boardsize x and y variables here but unable to use for array initialization
    int placedFood = 0;
    objPos tempBody;
    objPos tempFood;
    objPos newFood;

    foodBucket->clearList();

    for(int k = 0; k < 5; k++) 
    {
        int x = (rand() % (boardSizeX - 2)) + 1;
        int y = (rand() % (boardSizeY - 2)) + 1;   

        for(int i = 0; i < blockOff->getSize(); i++) //do not generate food on player
        {
            tempBody = blockOff->getElement(i);
            if(x == tempBody.pos->x && y == tempBody.pos->y) 
            {
                x = (rand() % (boardSizeX - 2)) + 1;
                y = (rand() % (boardSizeY - 2)) + 1;   
                i--;
            }
        }  
        for(int j = 0; j < k; j++)  //do not generate food on other food
        {
            tempFood = foodBucket->getElement(j);
            if(x == tempFood.pos->x && y == tempFood.pos->y) 
            {
                x = (rand() % (boardSizeX - 2)) + 1;
                y = (rand() % (boardSizeY - 2)) + 1;   
                j--;
            }
        }  

        if(k < 3) //to randomize position of food
        {
            newFood.setObjPos(x, y, '^');
        }
        else if (k == 3) //to randomize position of food
        {
            newFood.setObjPos(x, y, '+');
        } 
        else //to randomize position of food
        {
            newFood.setObjPos(x, y, '-');
        }

        foodBucket->insertTail(newFood);
    }
}

objPos Food::getFoodPos() const 
{
    return foodPos;
}

objPosArrayList* Food::getFoodList() const 
{
    return foodBucket;
}

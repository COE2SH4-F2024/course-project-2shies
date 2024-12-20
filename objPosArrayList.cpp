#include "objPosArrayList.h"
#include <iostream>
using namespace std;
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize=0;
    arrayCapacity=ARRAY_MAX_CAP;
    aList= new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize==arrayCapacity)
    {
        cout<<"Array list is full"<<endl; //for error handling
        return;
    }
    for (int i=listSize;i>0;i--)
    {
        aList[i]=aList[i-1];
    }
    aList[0]=thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize==arrayCapacity)
    {
        cout<<"Array list is full"<<endl; //for error handling
        return;
    }
    aList[listSize]=thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize==0)
    {
        cout<<"Array list is empty"<<endl; //for error handling
        return;
    }
    for (int i=0;i<listSize-1;i++)
    {
        aList[i]=aList[i+1];
    }
    listSize--;

}

void objPosArrayList::removeTail()
{
    if (listSize==0)
    {
        cout<<"Array list is empty"<<endl; //for error handling
        return;
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}

void objPosArrayList::clearList() //to overwrite generated food once food collision occurs
{
    listSize = 0;
}
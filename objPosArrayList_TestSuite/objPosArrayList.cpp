#include "objPosArrayList.h"

objPosArrayList::objPosArrayList() //default constuctor
{
    listSize = 0; //0 valid elements
    arrayCapacity = 200; //default capacity of 200

    aList = new objPos[arrayCapacity]; //list of objPos on heap
}

objPosArrayList::~objPosArrayList() //destructor
{
    delete[] aList; //deallocate list of objPos
}

int objPosArrayList::getSize() const
{
    return listSize; //return number of valid elements
}

void objPosArrayList::insertHead(objPos thisPos)
{
    int i;

    //shift every element one down
    for(i = listSize-1; i>=0; i--)
    {
        aList[i+1] = aList[i];
    }

    //set first element
    aList[0] = thisPos;

    //increment size of list
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    //set next element
    aList[listSize] = thisPos;

    //increment size of list
    listSize++;
}

void objPosArrayList::removeHead()
{
    int i;

    //shift every element one up
    for(i = 0; i<listSize-1; i++)
    {
        aList[i] = aList[i+1];
    }

    //deincrement size of list
    listSize--;
}


void objPosArrayList::removeTail()
{
    //deincrement size of list
    aList[listSize-1] = objPos();
    listSize--;
}


        
objPos objPosArrayList::getHeadElement() const
{
    //return first item in list
    return aList[0];
}


objPos objPosArrayList::getTailElement() const
{
    //return last item in list
    return aList[listSize-1];
}


objPos objPosArrayList::getElement(int index) const
{
    //return the item at index n
    return aList[index];
}


#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList(); //Default constructor
        objPosArrayList(const objPosArrayList& other); //Copy constructor
        objPosArrayList& operator = (const objPosArrayList& other); //Copy assignment operator
        ~objPosArrayList(); //Destructor

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;

        void setElement(objPos insert, int index);
};

#endif
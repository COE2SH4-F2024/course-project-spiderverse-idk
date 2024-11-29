#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos();
        objPos(int xPos, int yPos, char sym);
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule
        objPos(const objPos& other); //Copy constructor
        objPos& operator = (const objPos& other); //Copy assignment operator
        ~objPos(); //Destructor


        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  
        void setObjPos(int xPos, int yPos); 

        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif
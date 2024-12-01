#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

// Forward declaration of Food class
class Food;

class Player
{
public:
    enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // Direction states

    // Constructor that takes GameMechs and Food references
    Player(GameMechs* thisGMRef, Food* foodRef); 
    ~Player();  // Destructor to handle cleanup

    // Accessor methods
    objPosArrayList* getPlayerPos() const;  // Get player positions
    int getPlayerDir();                    // Get player direction
    void updatePlayerDir();                // Update player direction
    void movePlayer();                     // Move player
    int getScore() const;                  

private:
    objPosArrayList* playerPosList;        // List of player positions
    enum Dir myDir;                        // Direction the player is facing

    GameMechs* mainGameMechsRef;           // Reference to the main game mechanisms
    Food* mainFoodRef;                     // Reference to the food object (optional for now)
};

#endif

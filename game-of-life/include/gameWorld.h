/**
  * @headerfile gameworld.h
  * @brief Klass för att hantera spelvärlden.
  *
  * Innehåller funktioner för att skapa en spelvärld,
  * placera och hämta tecken på en viss plats i världen
  * samt kopiera innehållet från en spelvärld till en annan.
  * @version 1.0
  * @author Anna Hansson, Henrik Johansson & Marcus Stenroos
  */

#ifndef GAME_WORLD_H
#define GAME_WORLD_H
#include <cstring>

class GameWorld
{
public:
    //GameWorld();
    GameWorld(int xWidth, int yHeight);
    ~GameWorld();
    /** Inline hämtar spelvärldens bredd.
         * @returns Integer.*/
    int getWidth() const {return width;}
    /** Inline hämtar spelvärldens höjd.
         * @returns Integer.*/
    int getHeight() const {return height;}
    unsigned char charAtPosition( int xPos, int yPos) const;
    void setCharAt(int xPos, int yPos, unsigned char uChar);
    void copyWorld(GameWorld* otherWorld);

private:
    int width;
    int height;
    unsigned char* worldGrid;
};

#endif // GAME_WORLD_H

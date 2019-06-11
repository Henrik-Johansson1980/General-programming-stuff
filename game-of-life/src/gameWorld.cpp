/**
  * @file gameworld.cpp
  * @author Anna Hansson, Henrik Johansson & Marcus Stenroos
  * @version 0.3
  * @brief Implementationsfil för gameWorld klassen.
  */

#include "gameworld.h"

GameWorld::GameWorld(int xWidth = 80, int yHeight = 24): width(xWidth), height(yHeight)
{
    /** Beräknar minnesutrymmet som krävs för denna värld och initerar
       den 2-D array som representerar spelvärlden.*/

    /**
     * @param xWidth Parameter för att sätta spelvärldens bredd. Default är 80.
     * @param yHeight Parameter för att sätta spelvärldens höjd. Default är 24.
     */
    //Breäkna storlek
    int size = width * height * sizeof(unsigned char);
    //Allokera utrymme för array
    worldGrid = new unsigned char[size];
    //Initera elementen i arrayen till 0.
    memset( worldGrid, 0, size);
}

GameWorld::~GameWorld()
{
    /** Destruktorn frigör allokerat minnesutrymme.*/
    delete [] worldGrid;
    worldGrid = nullptr;
}

unsigned char GameWorld::charAtPosition(int xPos, int yPos) const
{
    /** Returnerar tecknet på positionen (x,y) i worldGrid
     * @param xPos Den X-koordinat som skall undersökas.
     * @param yPos Den Y-koordinat som skall undersökas.
     * @return Det tecken som finns på denna plats (unsigned char).
     */
    return worldGrid[xPos + yPos * width];
}

void GameWorld::setCharAt(int xPos, int yPos, unsigned char uChar)
{
    /** Sätt in ett tecken på den plats i världen som motsvaras av xPos och yPos.
     * @param xPos Den X-koordinat som skall undersökas.
     * @param yPos Den Y-koordinat som skall undersökas.
     * @param uChar Det tecken som skall ättas in (vanligtvis 1 eller 0). */
        worldGrid[ xPos + yPos * width] = uChar;
}

void GameWorld::copyWorld(GameWorld *otherWorld)
{
    /** Kopiera innehållet i från den värld som ges som parameter till kopian.
     * @param *otherWorld är en pekare till en spelvärld. */
    memcpy(worldGrid, otherWorld->worldGrid, width * height * sizeof(unsigned char));
}

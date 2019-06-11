/**
  * @file ruleset.cpp
  * @author Anna Hansson, Henrik Johansson & Marcus Stenroos
  * @version 1.0
  * @brief Implementationsfil för rulesetklassen.
  */

#include "ruleset.h"
#include <iostream>
Ruleset::Ruleset(GameWorld* w) : world(w)
{
    /**
      * Konstruktorn tar en parameter i form av ett GameWorld objekt och initerar datamedlemmar,
      * samt skapar en kopia av den medförda spelvärlden.
      * @param w är en pekare till ett GameWorld objekt.
      */
    width = world->getWidth();
    height = world->getHeight();
    tempWorld = new GameWorld(width, height);
}

Ruleset::~Ruleset()
{
    /** Destruktorn frigör det utrymmer som allokeras för den temporära världen. */

    if (tempWorld)
        delete tempWorld;
}


bool Ruleset::hasLivingCells()
{
    /**
     * Funktion som kontrollerar om det finns levande celler i världen
     * @return Sant om det finns levande celler i världen.
     */
    //gå igenom varje "ruta" i världen och kolla om det finns levande celler.
    for (int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(world->charAtPosition(x,y))
                return true;
        }
     }
    return false;
}

void Ruleset::applyRules()
{
    /** Går igenom varje ruta i spelvärlden och applicerar de gällande
     * spelreglerna och skriver nästa generations data till en kopia av
     * den aktuella världen.
     */
    int numOfNeighbours; //Platshållare för antal grannar
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Räkna grannar för denna cell/ruta
            numOfNeighbours = countNeighbours(x,y);

            if(world->charAtPosition(x,y))
            {
                //Kontrollera mot överlevnadsregeln
                if(surviveRule(numOfNeighbours))
                    tempWorld->setCharAt(x,y,1);
                if(!surviveRule(numOfNeighbours))
                    tempWorld->setCharAt(x,y,0);
            }
            else
            //Kontrollera mot födelseregel
            {
                if(birthRule(numOfNeighbours))
                    tempWorld->setCharAt(x,y,1);
                if(!birthRule(numOfNeighbours))
                    tempWorld->setCharAt(x,y,0);
            }
        }
    }
}

int Ruleset::countNeighbours(int worldPosX, int worldPosY)
{
    //Funktion för att räkna grannar runt en cell/position i världen.
    int neighbourCounter = 0;
    int neighbourPosX, neighbourPosY;

    for(int y = -1; y < 2; y++) //Loopa igenom y-le från ugångspunkten (cellPosX,cellPosY)
    {
         for (int x = -1; x < 2; x++) //Loopa igenom x-led från utgångspunkten (cellPosX,cellPosY)
         {
             if(!x && !y)
                 continue;
             neighbourPosX = (width + worldPosX + x ) % width; //beräkna x-koordinat för granne
             neighbourPosY = (height + worldPosY + y)% height; //beräkna y-koordinat för granne
             //om det finns en levande cell i grannkoordinaten
             if (world->charAtPosition(neighbourPosX,neighbourPosY) > 0)
             {
                 neighbourCounter++;
             }
         }
    }
    return neighbourCounter;
}

bool Ruleset::surviveRule(int numOfNeighbours)
{
    //Leta igenom vectorn efter en regel som matchar antal grannar
    return (survive.end() != find(survive.begin(), survive.end(), numOfNeighbours));
}

bool Ruleset::birthRule(int numOfNeighbours)
{
    //Leta igenom vectorn efter en regel som matchar antal grannar
    return (birth.end() != find(birth.begin(), birth.end(), numOfNeighbours));
}

/**
  * @headerfile ruleset.h
  * @brief Klass för att hantera spelregler.
  *
  * Innehåller funktioner för att växla mellan världar,
  * kontrollera om det finns levande celler i världen,bestämma födelse- och överlevnadsregler och applicera dem inför nästa generation.
  * @version 1.0
  * @author Henrik Johansson, Anna Hansson, Marcus Stenroos
  */
#ifndef RULESET_H
#define RULESET_H

#include "gameWorld.h"
#include <vector>
#include <algorithm>

class Ruleset
{
public:
    Ruleset(GameWorld* w);
    ~Ruleset();
    bool hasLivingCells();

    /** Byter ut den aktiva världen mot en kopia innehållandes data för nästa generation. */
    void switchWorld(){ world->copyWorld(tempWorld);}

    /** Initiera vectorn birth med födelseregler */
    void setBirthRule(std::vector<int>& birthRule) { birth = birthRule; }

    /** Initirera vectorn survive med överlevnadsregler */
    void setSurvivalRule(std::vector<int>& survivalRule) {survive = survivalRule;}

    void applyRules();

private:
    int countNeighbours(int worldPosX, int worldPosY);
    bool surviveRule(int numOfNeighbours);
    bool birthRule(int numOfNeighbours);

    GameWorld *world, *tempWorld;
    int width;
    int height;
    std::vector<int> survive, birth;
};
#endif // RULESET_H

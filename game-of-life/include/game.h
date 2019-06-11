/**
  * @headerfile game.h
  * @brief Klass som hanterar körningen av spelet.
  *
  * Klassen innehåller funktioner för att köra spelet och skriva ut generationerna på skärmen.
  * @version 1.0
  * @author Anna Hansson, Henrik Johansson, Marcus Stenroos.
  */

#ifndef GAME_H
#define GAME_H

#include "gameWorld.h"
#include "ruleset.h"
#include "gamesettings.h"
#include "../terminal/terminal.h"


class Game
{
public:

    Game(GameSettings &settings);
    ~Game();
    /** @brief Pekare till ett Ruleset objekt.*/
    Ruleset *evenRule;
    /** @brief Pekare till ett Ruleset objekt.*/
    Ruleset *oddRule;
    void startGame();
    /** Inlinefunktion hämtar numret på den nuvarande generationen.
     * @return Int motsvarande den nuvarande generationen.*/
    int getGeneration() const {return generations;}
    void display();
    void generation(bool printDisplay = 1);

private:
    void applyRules(GameSettings::ruleName rule, Ruleset *pRuleset);
    void randomState();
    void fileState();
    GameWorld *gWorld;
    int generations = 1;
    GameSettings settings;
};

#endif // GAME_H

/**
 * @file testrulemarcus.cpp
 * @version 1.0
 * @author Marcus Stenroos
 * @brief Tester för Marcus specialregel.
 */
#include <catch.hpp>
#include "gameWorld.h"
#include "ruleset.h"
#include "game.h"
#include "gamesettings.h"
#include "../terminal/terminal.h"

TEST_CASE("Enhetstester för Marcus Specialregel")
{
    SECTION("Birthrule: 2 grannar föder en ny cell")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> birthRuleV;
        birthRuleV.push_back(2);
        r.setBirthRule(birthRuleV);


        w1->setCharAt(6,3,1);
        w1->setCharAt(6,5,1);

        r.applyRules();
        r.switchWorld();


        REQUIRE(w1->charAtPosition(6,4) == true);
        REQUIRE(w1->charAtPosition(6,6) == false);
        REQUIRE(w1->charAtPosition(6,5) == false);

        delete w1;
    }
SECTION("Survivalrule: Cellen överlever om den har 4 grannar")
{
    GameWorld *w1 = new GameWorld(10,10);
    Ruleset r(w1);
    std::vector<int> rv;
    //fyra grannar för att överleva
    rv.push_back(4);
    r.setSurvivalRule(rv);
    w1->setCharAt(4,5,1);
    w1->setCharAt(5,4,1);
    w1->setCharAt(5,5,1);
    w1->setCharAt(5,6,1);
    w1->setCharAt(6,5,1);

    r.applyRules();
    r.switchWorld();
    REQUIRE(w1->charAtPosition(4,5) == false);
    REQUIRE(w1->charAtPosition(5,4) == false);
    REQUIRE(w1->charAtPosition(5,5) == true);
    REQUIRE(w1->charAtPosition(5,6) == false);
    REQUIRE(w1->charAtPosition(6,5) == false);
    r.applyRules();
    r.switchWorld();
    //Cellen dör utan 4 grannar
    REQUIRE(w1->charAtPosition(5,5) == false);

    delete w1;
}
SECTION("Survivalrule: Cellen överlever om den har 6 grannar")
{  GameWorld *w1 = new GameWorld(10,10);
    Ruleset r(w1);
    std::vector<int> rv;
    //fyra grannar för att överleva
    rv.push_back(6);
    r.setSurvivalRule(rv);
    w1->setCharAt(4,4,1);
    w1->setCharAt(4,5,1);
    w1->setCharAt(4,6,1);
    w1->setCharAt(5,4,1);
    w1->setCharAt(5,5,1);
    w1->setCharAt(6,5,1);
    w1->setCharAt(6,6,1);

    r.applyRules();
    r.switchWorld();
    REQUIRE(w1->charAtPosition(4,4) == false);
    REQUIRE(w1->charAtPosition(4,5) == false);
    REQUIRE(w1->charAtPosition(4,6) == false);
    REQUIRE(w1->charAtPosition(5,4) == false);
    REQUIRE(w1->charAtPosition(5,5) == true);
    REQUIRE(w1->charAtPosition(6,5) == false);
    REQUIRE(w1->charAtPosition(6,6) == false);
    r.applyRules();
    r.switchWorld();
    //Cellen dör utan 4 grannar
    REQUIRE(w1->charAtPosition(5,5) == false);

    delete w1;
}
SECTION("Survivalrule: Cellen överlever om den har 8 grannar")
{GameWorld *w1 = new GameWorld(10,10);
    Ruleset r(w1);
    std::vector<int> rv;
    //fyra grannar för att överleva
    rv.push_back(8);
    r.setSurvivalRule(rv);
    w1->setCharAt(4,4,1);
    w1->setCharAt(4,5,1);
    w1->setCharAt(4,6,1);
    w1->setCharAt(5,4,1);
    w1->setCharAt(5,5,1);
    w1->setCharAt(5,6,1);
    w1->setCharAt(6,4,1);
    w1->setCharAt(6,5,1);
    w1->setCharAt(6,6,1);

    r.applyRules();
    r.switchWorld();
    REQUIRE(w1->charAtPosition(4,4) == false);
    REQUIRE(w1->charAtPosition(4,5) == false);
    REQUIRE(w1->charAtPosition(4,6) == false);
    REQUIRE(w1->charAtPosition(5,4) == false);
    REQUIRE(w1->charAtPosition(5,5) == true);
    REQUIRE(w1->charAtPosition(5,6) == false);
    REQUIRE(w1->charAtPosition(6,4) == false);
    REQUIRE(w1->charAtPosition(6,5) == false);
    REQUIRE(w1->charAtPosition(6,6) == false);
    r.applyRules();
    r.switchWorld();
    //Cellen dör utan 4 grannar
    REQUIRE(w1->charAtPosition(5,5) == false);

    delete w1;
}

SECTION("Testar att regeln sätts för udda generationer")
{
        char* argv[] =
        {
            (char*)"-or",
            (char*)"MARCUS",
            (char*)"-g",
            (char*)"40"
        };
        int argc = 4;
        GameSettings s(argc, argv);
        REQUIRE(s.getOddRule() == GameSettings::MARCUS);
        Game g(s);
        g.startGame();
        int height = s.getHeight();
        int width = s.getWidth();
        REQUIRE(g.getGeneration()== 1);
        do
        {
            g.generation(false);
            //Kontrollerar att regeln med udda-generationer tillämpas
            if (g.getGeneration() % 2 == 1)
            {
                REQUIRE(s.getOddRule() == GameSettings::MARCUS);
            }
        }while((g.evenRule->hasLivingCells() && g.oddRule->hasLivingCells()) && (s.getIterations() >= g.getGeneration()));
}
SECTION("Testar att regeln sätts för jämna generationer")
{
        char* argv[] =
        {
            (char*)"-er",
            (char*)"MARCUS",
            (char*)"-g",
            (char*)"40"
        };
        int argc = 4;
        GameSettings s(argc, argv);
        REQUIRE(s.getEvenRule() == GameSettings::MARCUS);
        Game g(s);
        g.startGame();
        int height = s.getHeight();
        int width = s.getWidth();
        REQUIRE(g.getGeneration()== 1);
        do
        {
            g.generation(false);
            //Kontrollerar att regeln för jämna generationer tillämpas
            if (g.getGeneration() % 2 == 0)
            {
                REQUIRE(s.getEvenRule() == GameSettings::MARCUS);
            }
        }while((g.evenRule->hasLivingCells() && g.oddRule->hasLivingCells()) && (s.getIterations() >= g.getGeneration()));
}
}

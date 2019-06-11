/**
 * @file testrulehenrik.cpp
 * @version 1.0
 * @author Henrik Johansson
 * @brief Tester för Henriks specialregel.
 */
#ifdef DEBUG
#include <memstat.hpp>
#endif
#include <catch.hpp>
#include "gameWorld.h"
#include "ruleset.h"
#include "game.h"
#include "gamesettings.h"
#include "../terminal/terminal.h"

TEST_CASE("Enhetstester för Henriks specialregel")
{
    SECTION("Birthrule: En cell föds om de har en granne.")
    {
            GameWorld *w1 = new GameWorld(10,10);
            Ruleset r(w1);
            std::vector<int> birthRuleV;
            birthRuleV.push_back(1);
            r.setBirthRule(birthRuleV);
            w1->setCharAt( 5,5,1);
            r.applyRules();
            r.switchWorld();
            REQUIRE(w1->charAtPosition(4,4) == true);
            REQUIRE(w1->charAtPosition(5,4) == true);
            REQUIRE(w1->charAtPosition(6,4) == true);
            REQUIRE(w1->charAtPosition(4,5) == true);
            REQUIRE(w1->charAtPosition(5,5) == false);
            REQUIRE(w1->charAtPosition(6,5) == true);
            REQUIRE(w1->charAtPosition(4,6) == true);
            REQUIRE(w1->charAtPosition(5,6) == true);
            REQUIRE(w1->charAtPosition(6,6) == true);
            delete w1;
    }

    SECTION("Survivalrule: Cellen överlever om den har 2 grannar.")
    {
            GameWorld *w1 = new GameWorld(10,10);
            Ruleset r(w1);
            std::vector<int> rv;
            //Två grannar för att överleva
            rv.push_back(2);
            r.setSurvivalRule(rv);
            w1->setCharAt(5,5,1); //TESTCELL
            w1->setCharAt(4,5,1);
            w1->setCharAt(6,6,1);
            r.applyRules();
            r.switchWorld();
            REQUIRE(w1->charAtPosition(6,6) == false);
            REQUIRE(w1->charAtPosition(5,5) == true);
            REQUIRE(w1->charAtPosition(4,5) == false);
            r.applyRules();
            r.switchWorld();
            //Cellen dör utan 2 grannar
            REQUIRE(w1->charAtPosition(5,5) == false);
            delete w1;
    }

    SECTION("Survivalrule: Cellen överlever om den har 3 grannar.")
    {
            GameWorld *w1 = new GameWorld(10,10);
            Ruleset r(w1);
            std::vector<int> rv;
            //Två grannar för att överleva
            rv.push_back(3);
            r.setSurvivalRule(rv);
            w1->setCharAt(5,4,1);
            w1->setCharAt(5,5,1); //TESTCELL
            w1->setCharAt(4,5,1);
            w1->setCharAt(6,6,1);
            r.applyRules();
            r.switchWorld();
            REQUIRE(w1->charAtPosition(6,6) == false);
            REQUIRE(w1->charAtPosition(5,5) == true);
            REQUIRE(w1->charAtPosition(4,5) == false);
            r.applyRules();
            r.switchWorld();
            //Cellen dör utan 3 grannar
            REQUIRE(w1->charAtPosition(5,5) == false);
            delete w1;
    }

    SECTION("Survivalrule: Cellen överlever om den har 6 grannar.")
    {
            GameWorld *w1 = new GameWorld(10,10);
            Ruleset r(w1);
            std::vector<int> rv;
            //Två grannar för att överleva
            rv.push_back(6);
            r.setSurvivalRule(rv);
            w1->setCharAt(4,4,1);
            w1->setCharAt(5,4,1);
            w1->setCharAt(6,4,1);
            w1->setCharAt(4,5,1);
            w1->setCharAt(5,5,1); //TESTCELL
            w1->setCharAt(6,5,1);
            w1->setCharAt(6,6,1);
            r.applyRules();
            r.switchWorld();
            REQUIRE(w1->charAtPosition(5,5) == true);
            r.applyRules();
            r.switchWorld();
            //Cellen dör utan 6 grannar
            REQUIRE(w1->charAtPosition(5,5) == false);
            delete w1;
    }

    SECTION("Survivalrule: Cellen överlever om den har 8 grannar.")
    {
            GameWorld *w1 = new GameWorld(10,10);
            Ruleset r(w1);
            std::vector<int> rv;
            //Två grannar för att överleva
            rv.push_back(8);
            r.setSurvivalRule(rv);
            w1->setCharAt(4,4,1);
            w1->setCharAt(5,4,1);
            w1->setCharAt(6,4,1);
            w1->setCharAt(4,5,1);
            w1->setCharAt(5,5,1); //TESTCELL
            w1->setCharAt(6,5,1);
            w1->setCharAt(4,6,1);
            w1->setCharAt(5,6,1);
            w1->setCharAt(6,6,1);
            r.applyRules();
            r.switchWorld();
            REQUIRE(w1->charAtPosition(5,5) == true);
            r.applyRules();
            r.switchWorld();
            //Cellen dör utan 6 grannar
            REQUIRE(w1->charAtPosition(5,5) == false);
            delete w1;
    }

    SECTION("Testa så att regeln sätts för udda generationer")
    {
            char* argv[] =
            {
                (char*)"-or",
                (char*)"HENRIK",
                (char*)"-g",
                (char*)"20"
            };
            int argc = 4;
            GameSettings s(argc, argv);
            REQUIRE(s.getOddRule() == GameSettings::HENRIK);
            Game g(s);
            g.startGame();
            int height = s.getHeight();
            int width = s.getWidth();
            REQUIRE(g.getGeneration()== 1);
            do
            {
                g.generation(false);
                //Kontrollera så att Henrik är den aktuella regeln för udda generationer
                if (g.getGeneration() % 2 == 1)
                {
                    REQUIRE(s.getOddRule() == GameSettings::HENRIK);
                }
            }while((g.evenRule->hasLivingCells() && g.oddRule->hasLivingCells()) && (s.getIterations() >= g.getGeneration()));
    }

    SECTION("Testa så att regeln sätts för jämna generationer")
    {
            char* argv[] =
            {
                (char*)"-er",
                (char*)"HENRIK",
                (char*)"-g",
                (char*)"20"
            };
            int argc = 4;
            GameSettings s(argc, argv);
            REQUIRE(s.getEvenRule() == GameSettings::HENRIK);
            Game g(s);
            g.startGame();
            int height = s.getHeight();
            int width = s.getWidth();
            REQUIRE(g.getGeneration()== 1);
            do
            {
                g.generation(false);
                //Kontrollera så att Henrik är den aktuella regeln för udda generationer
                if (g.getGeneration() % 2 == 0)
                {
                    REQUIRE(s.getEvenRule() == GameSettings::HENRIK);
                }
            }while((g.evenRule->hasLivingCells() && g.oddRule->hasLivingCells()) && (s.getIterations() >= g.getGeneration()));
    }

}

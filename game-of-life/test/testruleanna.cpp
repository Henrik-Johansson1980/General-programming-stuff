#include <catch.hpp>
#include "gameWorld.h"
#include "ruleset.h"
#include "game.h"
#include "gamesettings.h"
/**
  * @file testruleanna.cpp
  * @brief Tester för specialregeln Anna
  * @author Anna Hansson
  */
TEST_CASE("Testar specialregeln Anna")
{
    SECTION("Överlevnadsregel: cellen överlever om den har 0 eller 2 grannar")
    {
        GameWorld *gw = new GameWorld(10,10);
        Ruleset rs(gw);
        std::vector<int> rv;
        rv.push_back(0);
        rv.push_back(2);
        rs.setSurvivalRule(rv);
        //en cell = 0 grannar
        gw->setCharAt(0,1,1);
        rs.applyRules();
        rs.switchWorld();
        //cellen överlever
        REQUIRE(gw->charAtPosition(0,1)==true);
        //cellen får 2 grannar
        gw->setCharAt(1,0,1);
        gw->setCharAt(0,2,1);
        rs.applyRules();
        rs.switchWorld();
        //den första cellen har 2 grannar och överlever
        REQUIRE(gw->charAtPosition(0,1)==true);
        //de 2 grannarna 1 granne och dör
        REQUIRE(gw->charAtPosition(1,0)==false);
        REQUIRE(gw->charAtPosition(0,2)==false);
        delete gw;

    }
    SECTION("Födelseregel: en ny cell föds om den har 1 eller 2 grannar")
    {
        GameWorld *gw = new GameWorld(10,10);
        Ruleset rs(gw);
        std::vector<int> rv;
        rv.push_back(1);
        rv.push_back(2);
        rs.setBirthRule(rv);
        //sätter en cell till världen
        gw->setCharAt(2,1,1);
        rs.applyRules();
        rs.switchWorld();
        //en granne föder ny cell
        REQUIRE(gw->charAtPosition(2,0)==true);
        REQUIRE(gw->charAtPosition(1,0)==true);
        REQUIRE(gw->charAtPosition(1,1)==true);
        REQUIRE(gw->charAtPosition(1,2)==true);
        REQUIRE(gw->charAtPosition(2,2)==true);
        REQUIRE(gw->charAtPosition(3,2)==true);
        REQUIRE(gw->charAtPosition(3,1)==true);
        REQUIRE(gw->charAtPosition(3,0)==true);
        rs.applyRules();
        rs.switchWorld();
        //två grannar föder ny cell
        REQUIRE(gw->charAtPosition(0,0)==true);
        REQUIRE(gw->charAtPosition(0,2)==true);
        REQUIRE(gw->charAtPosition(1,3)==true);
        REQUIRE(gw->charAtPosition(3,3)==true);
        REQUIRE(gw->charAtPosition(4,0)==true);
        //tre grannar föder inte ny cell
        REQUIRE(gw->charAtPosition(0,1)==false);

        delete gw;
    }

}

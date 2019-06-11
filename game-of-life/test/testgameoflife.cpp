/**
 * @file testGameOfLife.cpp
 * @version 1.0
 * @author Henrik Johansson, Marcus Stenroos & Anna Hansson
 * @brief Enhetstester för alla klasser i Game of Life.
 */
#include <catch.hpp>
#include "gameWorld.h"
#include "ruleset.h"
#include "game.h"
#include "gamesettings.h"
#include "../terminal/terminal.h"

TEST_CASE("Enhetstester för Klassen GameWorld")
{
    SECTION("Test Gameworld")
    {
        GameWorld w (10,20);
        w.setCharAt(5,5,1);
        REQUIRE(w.getHeight() == 20);
        REQUIRE(w.getWidth()== 10);
        REQUIRE(w.charAtPosition(5,5) == true);
        REQUIRE(w.charAtPosition(1,0) == false);
    }

    SECTION("Test GameWorld: Alla publika funktioner ")
    {
        GameWorld *w1 = new GameWorld(10,10);
        GameWorld *w2 = new GameWorld(10,10);

        REQUIRE(w1->getWidth() == 10);
        REQUIRE(w1->getHeight() == 10);

        w1->setCharAt(2,2,1);
        w1->setCharAt(9,9,'@');

        REQUIRE(w1->charAtPosition(2,2) == true);
        REQUIRE(w1->charAtPosition(9,9) == '@');

        w2->copyWorld(w1);

        REQUIRE(w2->charAtPosition(2,2) == true);
        REQUIRE(w2->charAtPosition(9,9) == '@');

        w2->setCharAt(2,2,0);
        w2->setCharAt(9,9,0);
        w2->setCharAt(5,5,1);
        w1->copyWorld(w2);

        REQUIRE(w1->charAtPosition(2,2) == false);
        REQUIRE(w1->charAtPosition(9,9) == false);
        REQUIRE(w1->charAtPosition(5,5) == true );

        delete w1;
        delete w2;
    }
}

TEST_CASE("Enhetstester för Ruleset-klassen")
{
    SECTION("Ruleset Test: Cellen dör av ensamhet, testar setSurvivalRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        //conway överlevnad
        rv.push_back(2);
        rv.push_back(3);
        r.setSurvivalRule(rv);
        rv.clear();
        w1->setCharAt(5,5,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == false);
        delete w1;
    }

    SECTION("Ruleset Test: Cellen dör av överpopoulation (3 eller fler grannar),testar setSurvivalRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        //conway överlevnadsregel
        rv.push_back(2);
        rv.push_back(3);
        r.setSurvivalRule(rv);
        rv.clear();
        w1->setCharAt(5,5,1);
        w1->setCharAt(4,4,1);
        w1->setCharAt(5,4,1);
        w1->setCharAt(6,4,1);
        w1->setCharAt(4,5,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(4,4) == true);
        REQUIRE(w1->charAtPosition(5,4) == false);
        REQUIRE(w1->charAtPosition(6,4) ==true);
        REQUIRE(w1->charAtPosition(5,5) == false);

        delete w1;
    }

    SECTION("Ruleset Test: Cellen dör av överpopulation (4 eller fler grannar). Omringad cell."
            "Testar setSurvivalRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        //conway överlevnadsregel
        rv.push_back(2);
        rv.push_back(3);
        r.setSurvivalRule(rv);
        rv.clear();
        w1->setCharAt(4,4,1);
        w1->setCharAt(5,4,1);
        w1->setCharAt(6,4,1);
        w1->setCharAt(4,5,1);
        w1->setCharAt(5,5,1); //Testcell
        w1->setCharAt(6,5,1);
        w1->setCharAt(4,6,1);
        w1->setCharAt(5,6,1);
        w1->setCharAt(6,6,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == false);

        delete w1;
    }

    SECTION("Ruleset Test: två gannar = överlev, testar setSurvivalRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        //conway regler för överlevnad
        rv.push_back(2);
        rv.push_back(3);
        r.setSurvivalRule(rv);
        rv.clear();
        w1->setCharAt(5,5,1);
        w1->setCharAt(4,4,1);
        w1->setCharAt(6,6,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(6,6) == false);
        REQUIRE(w1->charAtPosition(5,5) == true);
        REQUIRE(w1->charAtPosition(4,4) == false);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == false);

        w1->setCharAt(4,4,1);
        w1->setCharAt(5,4,1);
        w1->setCharAt(5,5,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == true);
        REQUIRE(w1->charAtPosition(4,4) == true);
        REQUIRE(w1->charAtPosition(5,4) == true);

        w1->setCharAt(4,4,0);
        w1->setCharAt(5,4,1);
        w1->setCharAt(6,4,1);
        w1->setCharAt(5,5,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == true);
        REQUIRE(w1->charAtPosition(6,4) == true);
        REQUIRE(w1->charAtPosition(5,4) == true);

        w1->setCharAt(4,4,1);
        w1->setCharAt(5,4,0);
        w1->setCharAt(6,4,0);
        w1->setCharAt(4,6,1);
        w1->setCharAt(5,5,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == true);
        REQUIRE(w1->charAtPosition(4,6) == false);
        REQUIRE(w1->charAtPosition(4,4) == false);

        delete w1;
    }

    SECTION("Ruleset Test: överlevnadsregel 1 granne. Testar setSurvivalRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        //En granne för att överleva
        rv.push_back(1);
        r.setSurvivalRule(rv);
        rv.clear();
        w1->setCharAt(5,5,1);
        w1->setCharAt(6,6,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(6,6) == true);
        REQUIRE(w1->charAtPosition(5,5) == true);

        delete w1;
    }

    SECTION("Ruleset Test: överlevnadsregel 8 grannar för att överleva. Testar setSurvivalRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        //8 grannar för att överleva
        rv.push_back(8);
        r.setSurvivalRule(rv);
        rv.clear();
        w1->setCharAt(4,4,1);
        w1->setCharAt(5,4,1);
        w1->setCharAt(6,4,1);
        w1->setCharAt(4,5,1);
        w1->setCharAt(5,5,1); //Testcell
        w1->setCharAt(6,5,1);
        w1->setCharAt(4,6,1);
        w1->setCharAt(5,6,1);
        w1->setCharAt(6,6,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(4,4) == false);
        REQUIRE(w1->charAtPosition(5,4) == false);
        REQUIRE(w1->charAtPosition(6,4) == false);
        REQUIRE(w1->charAtPosition(4,5) == false);
        REQUIRE(w1->charAtPosition(5,5) == true);
        REQUIRE(w1->charAtPosition(6,5) == false);
        REQUIRE(w1->charAtPosition(4,6) == false);
        REQUIRE(w1->charAtPosition(5,6) == false);
        REQUIRE(w1->charAtPosition(6,6) == false);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(5,5) == false);
        delete w1;
    }

    SECTION("Ruleset Test: Blinker testar setSurvivalRule, setBirthRule, applyRules och switchWorld funktionerna."
            "Med Conways regler.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        //blinker
        std::vector<int> rv;
        //conway regler
        rv.push_back(2);
        rv.push_back(3);
        r.setSurvivalRule(rv);
        rv.clear();
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 1, 3, 1 ); w1->setCharAt( 2, 3, 1 );
        w1->setCharAt( 3, 3, 1 );
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(2,2) == true);
        REQUIRE(w1->charAtPosition(2,3) == true);
        REQUIRE(w1->charAtPosition(2,4) == true);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,3) == true);
        REQUIRE(w1->charAtPosition(2,3) == true);
        REQUIRE(w1->charAtPosition(3,3) == true);

        delete w1;
    }

    SECTION("RulesetTest Birth rule 1 granne. testar setBirthRule, applyRules och switchWorld funktionerna.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(1);
        r.setBirthRule(rv);
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

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar ovanför.")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 0,0,1);
        w1->setCharAt( 1,0,1);
        w1->setCharAt( 2,0,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);

        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar till vänster")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 0,0,1);
        w1->setCharAt( 0,1,1);
        w1->setCharAt( 0,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);

        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar till höger")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 2,0,1);
        w1->setCharAt( 2,1,1);
        w1->setCharAt( 2,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);

        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar nedanför")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 0,2,1);
        w1->setCharAt( 1,2,1);
        w1->setCharAt( 2,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);

        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar två över en under")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 0,0,1);
        w1->setCharAt( 1,0,1);
        w1->setCharAt( 0,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);
        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar två över en under #2")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 1,0,1);
        w1->setCharAt( 2,0,1);
        w1->setCharAt( 0,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);
        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar två över en under #3")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 0,0,1);
        w1->setCharAt( 2,0,1);
        w1->setCharAt( 2,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);
        delete w1;
    }

    SECTION("RulesetTest Conway: Testar setBirthRule för att se om det föds celler när en"
            "ruta har 3 grannar två till vänster en under")
    {
        GameWorld *w1 = new GameWorld(10,10);
        Ruleset r(w1);
        std::vector<int> rv;
        rv.push_back(3);
        r.setBirthRule(rv);
        w1->setCharAt( 0,0,1);
        w1->setCharAt( 2,0,1);
        w1->setCharAt( 2,2,1);
        r.applyRules();
        r.switchWorld();
        REQUIRE(w1->charAtPosition(1,1) == true);
        delete w1;
    }
SECTION("Ruleset test: Conway survival, celler i ett hörn")
    {
        GameWorld *gw = new GameWorld(10,10);
        Ruleset rs(gw);
        std::vector<int> rv;
        rv.push_back(2);
        rv.push_back(3);
        rs.setSurvivalRule(rv);
        //alla har 2 grannar, alla överlever
        gw->setCharAt(0,0,1);
        gw->setCharAt(0,1,1);
        gw->setCharAt(1,0,1);
        rs.applyRules();
        rs.switchWorld();
        REQUIRE(gw->charAtPosition(0,0)==true);
        REQUIRE(gw->charAtPosition(0,1)==true);
        REQUIRE(gw->charAtPosition(1,0)==true);
        //alla har 3 grannar, alla överlever
        gw->setCharAt(1,1,1);
        rs.applyRules();
        rs.switchWorld();
        REQUIRE(gw->charAtPosition(0,0)==true);
        REQUIRE(gw->charAtPosition(0,1)==true);
        REQUIRE(gw->charAtPosition(1,0)==true);
        REQUIRE(gw->charAtPosition(1,1)==true);
        //1,1 får 4 grannar och dör
        gw->setCharAt(2,2,1);
        rs.applyRules();
        rs.switchWorld();
        REQUIRE(gw->charAtPosition(0,0)==true);
        REQUIRE(gw->charAtPosition(0,1)==true);
        REQUIRE(gw->charAtPosition(1,0)==true);
        REQUIRE(gw->charAtPosition(1,1)==false);
        REQUIRE(gw->charAtPosition(2,2)==false);
        delete gw;

    }
    SECTION("Ruleset test: Conway survival, celler i en kant")
       {
           GameWorld *gw = new GameWorld(10,10);
           Ruleset rs(gw);
           std::vector<int> rv;
           rv.push_back(2);
           rv.push_back(3);
           rs.setSurvivalRule(rv);
           gw->setCharAt(0,1,1);
           gw->setCharAt(0,2,1);
           gw->setCharAt(0,3,1);
           gw->setCharAt(0,4,1);
           rs.applyRules();
           rs.switchWorld();
           REQUIRE(gw->charAtPosition(0,1)==false);
           REQUIRE(gw->charAtPosition(0,2)==true);
           REQUIRE(gw->charAtPosition(0,3)==true);
           REQUIRE(gw->charAtPosition(0,4)==false);
           rs.applyRules();
           rs.switchWorld();
           REQUIRE(gw->charAtPosition(0,2)==false);
           REQUIRE(gw->charAtPosition(0,3)==false);
           delete gw;
       }

    SECTION("Kontrollera om alla celler är döda. Test av haslivingCells funktionen.")
    {
        GameWorld *w = new GameWorld(10,10);
        Ruleset rules(w);
        REQUIRE(rules.hasLivingCells() == false);
        delete w;
    }

    SECTION("Kontrollera om det finns levande celler i världen, Test av haslivingCells funktionen.")
    {
        GameWorld *w = new GameWorld(10,10);
        w->setCharAt(1,1,'d');
        Ruleset rules(w);
        REQUIRE(rules.hasLivingCells() == true);
        delete w;
    }
}

TEST_CASE("Enhetstester för game och gamesettings klasserna.")
{

   SECTION("Game test: Default Game test. Starta nytt spel och kolla så att "
           "generationerna räknas upp. Kontrollerar även så att spelet startar"
           "med levande celler.")
   {
       char* argv[] = {};
       int argc = 0;
       GameSettings settings(argc, argv);
       REQUIRE(settings.getWidth() == 80);
       REQUIRE(settings.getHeight() == 24);
       REQUIRE(settings.getIterations()== 500);
       Game g(settings);
       g.startGame();
       REQUIRE(g.getGeneration() == 1);
       REQUIRE(g.evenRule->hasLivingCells() == true);
       bool print = 0;
       g.generation(print);
       REQUIRE(g.getGeneration() == 2);
   }

   SECTION("Game test: Game with options")
   {
       SECTION("Game test: Game with options")
          {
              // Argumenten "GameOfLife.exe -s 20x20 -g 100 -f ../game-of-life/textfiles/test001.txt
              char* argv[] = {
                  (char*)"-s",
                  (char*)"20x20",
                  (char*)"-g",
                  (char*)"200",
                  (char*)"-f",
                  (char*)"../game-of-life/textfiles/test001.txt"
              };
              // Antal argument
              int argc = 6;
              GameSettings settings(argc, argv);
              REQUIRE(settings.getWidth() == 20);
              REQUIRE(settings.getHeight() == 20);
              REQUIRE(settings.getIterations() == 200);
              Game g(settings);
              g.startGame();
              REQUIRE(g.getGeneration() == 1);
              REQUIRE(g.evenRule->hasLivingCells() == true);
              int ctr = 2;
              do
              {
                  g.generation(false);
                  REQUIRE(g.getGeneration() == ctr);
                  ctr++;
              }while((g.evenRule->hasLivingCells() && g.oddRule->hasLivingCells()) && (settings.getIterations() >= g.getGeneration()));


          }
   }

}

TEST_CASE("Game Settings: Tester för gamesettingsklassen.")
{
    SECTION("Gamesettingstest: -er /or. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-er",
            (char*)"heNrik"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getEvenRule() == 1);
    }

    SECTION("Gamesettingstest: -er argumentet. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-er",
            (char*)"henrik"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getEvenRule() == 1);
    }


    SECTION("Gamesettingstest: -er. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-er",
            (char*)"henrik"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getEvenRule() == 1);
    }

    SECTION("Gamesettingstest: -er. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-er",
            (char*)"HENRIK"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getEvenRule() == 1);
    }

    SECTION("Gamesettingstest: Används för att köra GameOfLife med en specialregel för udda generationer. "
            "Om inte parametern anges används samma regel som för jämna generationer (Extrauppgift)")
    {
        char* argv[] =
        {
            (char*)"-er",
            (char*)"MARCUS"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getOddRule() == GameSettings::MARCUS);
    }

    SECTION("Gamesettingstest: -or. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-or",
            (char*)"henrik"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getOddRule() == 1);
    }
    SECTION("Gamesettingstest: -er /or. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-or",
            (char*)"Anna"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getOddRule() == 2);
    }
    SECTION("Gamesettingstest: -er /or. Konvertera argument till stora bokstäver.")
    {
        char* argv[] =
        {
            (char*)"-or",
            (char*)"marCus"
        };
        int argc = 2;
        GameSettings s(argc, argv);
        REQUIRE(s.getOddRule() == 3);
    }
}



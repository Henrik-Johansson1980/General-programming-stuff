/**
  * @file game.cpp
  * @author Anna Hansson, Henrik Johansson, Marcus Stenroos.
  * @version:  1.0
  * @brief Implementationsfil för Game-klassen.
  */
#include "game.h"
#include "gamesettings.h"
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>

//Konstruktor för att skapa ett nytt spel
//Inställningarna för spelet finns i klassen GameSettings
Game::Game(GameSettings &settings) : evenRule(0), oddRule(0), settings(settings)
{
    /**
    * Konstruktor för att starta ett nytt spel.
    * @param settings Inställningar från GameSettings klassen.
    */
    gWorld = new GameWorld(settings.getWidth(), settings.getHeight());
}

Game::~Game()
{
    /** Frigör allokerat minnesutrymme. */
    if (evenRule)
        delete evenRule;

    if (oddRule)
        delete oddRule;

    delete gWorld;
}

void Game::applyRules(GameSettings::ruleName rule, Ruleset *pRuleset)
{
    std::vector<int> ruleVec;

    //Sätter regler.
    switch(rule)
    {
        case GameSettings::CONWAY: //Conways Game of Life
            //2 eller 3 grannar för att överleva.
            ruleVec.push_back(2);
            ruleVec.push_back(3);
            //Initera regelvektor.
            pRuleset->setSurvivalRule(ruleVec);
            //Rensa vectorn för att ta emot födelseregler.
            ruleVec.clear();
            //3 grannar föder en ny cell
            ruleVec.push_back(3);
            //Initera regelvector (birth)
            pRuleset->setBirthRule(ruleVec);
            break;
        case GameSettings::HENRIK: //Henriks
             ruleVec.push_back(2);
             ruleVec.push_back(3);
             ruleVec.push_back(6);
             ruleVec.push_back(8);
             //Initera regelvektor.
             pRuleset->setSurvivalRule(ruleVec);
             //Rensa vectorn för att ta emot födelseregler.
             ruleVec.clear();
             ruleVec.push_back(1);
             //Initera regelvector (birth)
             pRuleset->setBirthRule(ruleVec);
             break;
        case GameSettings::ANNA:
             ruleVec.push_back(0);
             ruleVec.push_back(2);
             pRuleset->setSurvivalRule(ruleVec);
             ruleVec.clear();
             ruleVec.push_back(1);
             ruleVec.push_back(2);
             pRuleset->setBirthRule(ruleVec);
             break;
        case GameSettings::MARCUS:
            //4, 6 eller 8 grannar för att överleva.
            ruleVec.push_back(4);
            ruleVec.push_back(6);
            ruleVec.push_back(8);
            //Initera regelvektor.
            pRuleset->setSurvivalRule(ruleVec);
            //Rensa vectorn för att ta emot födelseregler.
            ruleVec.clear();
            //2 grannar föder en ny cell
            ruleVec.push_back(2);
            //Initera regelvector (birth)
            pRuleset->setBirthRule(ruleVec);
            break;

            delete pRuleset;

    }
}

void Game::startGame()
{
    /** Startar spelet med angivna inställningar. */
    evenRule = new Ruleset(gWorld); // Skapar regel för jämna generationer
    oddRule = new Ruleset(gWorld); // Skapar regel för udda generationer

    //Använda positioner från fil/Slumpa värld.
    //Förenklad if/else
    settings.hasPositions() ? fileState() : randomState();
    // Sätter reglerna
    applyRules(settings.getEvenRule(), evenRule);
    applyRules(settings.getOddRule(), oddRule);
}
/**
 * @brief Skriver ut spelplan och celler på skärmen och innehåller våra specialregler.
 */
void Game::display()
{
    Terminal terminal;
    int width = gWorld->getWidth();
    int height = gWorld->getHeight();
    //Övre kant
    std::cout << "+" << std::string(width,'-') << "+\n";
    for(int y = 0; y < height; y++)
    {
        //vänsterkant
        std::cout << '|';
        for (int x = 0; x < width; x++)
        {
            if(gWorld->charAtPosition(x,y))
            {
                //Conway
                if(settings.getRuleForGeneration(generations) == GameSettings::CONWAY)
                    std::cout << 'C';
                //Henriks specialregel
                /**
                  *  #### HENRIKS SPECIALREGEL
                  *
                  * Om denna regel anges som argument vid bygge av spelet kommer De aktiva cellerna att
                  * skrivas ut som bokstaven 'H' i grön färg. Om antalet generationer är delbart med
                  * 16 eller 17 (beroende på om regeln körs  jämna eller ojämna generationer) kommer texten
                  * för cellerna att bli gul och spelplanen röd den genrationen när ett stort område rensas
                  * från celler.
                  */
                else if (settings.getRuleForGeneration(generations) == GameSettings::HENRIK)
                {
                    if (generations % 16 == 0 && settings.getEvenRule() == GameSettings::HENRIK)
                    {
                        terminal.pushColor(TerminalColor(COLOR::YELLOW));
                        std::cout << 'H';
                        terminal.popColor();
                    }
                    else if (generations % 17 == 0 && settings.getOddRule() == GameSettings::HENRIK)
                    {
                        terminal.pushColor(TerminalColor(COLOR::YELLOW));
                        std::cout << 'H';
                        terminal.popColor();
                    }
                    else
                    {
                        terminal.pushColor(TerminalColor(COLOR::GREEN));
                        std::cout << 'H';
                        terminal.popColor();
                    }

                    if (generations % 16 == 0 && settings.getEvenRule() == GameSettings::HENRIK)
                    {
                        terminal.pushColor(TerminalColor(COLOR::RED));
                        for(int y = (height - height +5 ); y < height - 5; y++)
                        {
                            for (int x = 5; x < width-5; x++)
                            {
                                if(gWorld->charAtPosition(x,y))
                                {
                                    gWorld->setCharAt(x,y,0);
                                }
                            }
                        }

                    }
                    else if (generations % 17 == 0 && settings.getOddRule() == GameSettings::HENRIK)
                    {
                        terminal.pushColor(TerminalColor(COLOR::RED));
                        for(int y = (height - height +5 ); y < height - 5; y++)
                        {
                            for (int x = 5; x < width-5; x++)
                            {
                                if(gWorld->charAtPosition(x,y))
                                {
                                    gWorld->setCharAt(x,y,0);
                                }

                            }
                        }
                    }
                }
                //Annas specialregel
               else if (settings.getRuleForGeneration(generations)==GameSettings::ANNA)
                {

                    if(generations % 10 ==0)
                    {
                        terminal.pushColor(TerminalColor(COLOR::GREEN));
                        for(int i=0; i<height; i++)
                        {
                            for(int j=0; j<width; j++)
                             {
                               if(gWorld->charAtPosition(j,i)==true)
                                gWorld->setCharAt(j,i,0);

                             }
                        }
                        gWorld->setCharAt(width-2, height-3,1); gWorld->setCharAt(2,3,1);
                        gWorld->setCharAt(width-5, height-2,1); gWorld->setCharAt(5,2,1);
                        gWorld->setCharAt(width-4, height-5, 1); gWorld->setCharAt(5,5,1);
                        std::cout << 'A';
                        terminal.popColor();
                    }
                    else if (generations % 11 ==0)
                    {

                        terminal.pushColor(TerminalColor(COLOR::GREEN));
                        for(int i=0; i<height; i++)
                        {
                            for(int j=0; j<width; j++)
                             {
                               if(gWorld->charAtPosition(j,i)==true)
                                gWorld->setCharAt(j,i,0);

                             }
                        }
                        gWorld->setCharAt(width-2, height-3,1); gWorld->setCharAt(2,3,1);
                        gWorld->setCharAt(width-5, height-2,1); gWorld->setCharAt(5,2,1);
                        gWorld->setCharAt(width-4, height-5, 1); gWorld->setCharAt(5,5,1);
                        std::cout << 'A';
                        terminal.popColor();
                    }
                    else if(generations % 2==0)
                    {
                        terminal.pushColor(TerminalColor(COLOR::MAGENTA));
                        std::cout << 'A';
                        terminal.popColor();
                    }
                    else
                    {
                    terminal.pushColor(TerminalColor(COLOR::BLUE));
                    std::cout << 'A';
                    terminal.popColor();
                    }

                       if(generations % 2 == 0)
                       {
                        terminal.pushColor(TerminalColor(COLOR::BLUE));
                       }
                       else
                       {
                        terminal.pushColor(TerminalColor(COLOR::MAGENTA));
                       }
                }
                //Marcus specialregel
                else if (settings.getRuleForGeneration(generations) == GameSettings::MARCUS)
                {
                    terminal.pushColor(TerminalColor(COLOR::RED));
                    std::cout << 'M';
                    terminal.popColor();
                }
                else
                {
                    std::cout << '.';
                }
            }
            else
            {
                if (settings.getRuleForGeneration(generations) == GameSettings::MARCUS)
                {
                    terminal.pushColor(TerminalColor(COLOR::GREEN));
                    std::cout << '#';
                    terminal.popColor();
                }
                else
                {
                    std::cout << '.';
                }
            }
        }
        //höger kant
        std::cout << "|\n";
    }
    //nedre kant
     std::cout << "+" << std::string(width,'-') << "+\n";
}
/**
  * @brief Funktionen utför de diverse olika funktionsanrop som ska ske under en generation.
  * @param printDisplay är en bool som sätts på/ av beroende om man vill att skärmen ska uppdateras eller inte
  * default är true, av (false) är främst menat för tester när diplayen inte är önskvärd.
  */
void Game::generation(bool printDisplay)
{    /** Funktionen utför de diverse olika funktionsanrop som ska ske under en generation.
     * Beroende på om printDisplay är påslagen (default) kommer den nuvarande generationen att
     * skrivas ut på skärmen. Därefter appliceras gällande regler för överlevnad/födsel. Denna
     * informnation skrivs till en kopia av den aktiva världen. Avlutningsvis byts den nuvarande
     * världen ut mot den värld som innehåller nästa generation.

     */
    if(printDisplay)
    {
        display();
    }

    if (generations % 2 == 0) // Jämn generation
    {
        evenRule->applyRules();
        evenRule->switchWorld();
    }
    else // Ojämn generation
    {
        oddRule->applyRules();
        oddRule->switchWorld();
    }

    generations++;


}

//------------------------------------------------------------------------------------------------------
//PRIVATA MEDLEMSFUNKTIONER
//------------------------------------------------------------------------------------------------------

void Game::randomState() //Privat
{
   //Slumpa fram aktiva celler på spelbrädet.
   int width= gWorld->getWidth();
   int height = gWorld->getHeight();
   std::default_random_engine generator(static_cast<unsigned> (time(0)));
   std::uniform_int_distribution<int> random(0, 10);
   for(int y=0; y < height; y++)

   {
       for (int x=0; x<width; x++)
       {
           int num=random(generator);

           if(num==0 || num == 1)
             gWorld->setCharAt(x,y,num);
       }
   }
}

void Game::fileState() //Privat
{
    settings.adjustPositions();
    auto positions = settings.getPositions();

    for(int y = 0; y < positions.size(); y++)
    {
        auto row = positions[y];
        for (int x = 0; x < row.size(); x++)
        {
            int i = row[x];
            gWorld->setCharAt(x, y, i);
        }
    }
}

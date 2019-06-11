/**
  * Filnamn gameoflife.cpp
  * @author Anna Hansson, Henrik Johansson, Marcus Stenroos.
  * @version:  1.0
  * @brief Mainfunktion och gameloop.
  */

#ifdef DEBUG
#include <memstat.hpp>
#endif

#include "game.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

int main( int argc, char* argv[] )
{
    Terminal terminal;
    terminal.pushColor(TerminalColor(COLOR::WHITE, COLOR::BLACK));
    terminal.showCursor(false);
    GameSettings settings(argc, argv);
    Game game(settings);
    game.startGame();
    /**
      * @brief GAME LOOP
      *
      * Denna do-while kontrollerar vilken regel som ska användas för varje generation.
      * Detta upprepas till dess att det inte finns några levande celler kvar eller valt antal generationer
      * uppnåtts. Då skrivs ett Game Over meddelande ut. Uppdateringshastigheten är satt till en halv sekund.
      */
    do
    {
        if(settings.getEvenRule()==1 && game.getGeneration() % 2 == 0 || settings.getOddRule()==1 && game.getGeneration()%2!=0)
        {
            game.generation();
            cout << "\nGeneration: " << game.getGeneration()-1 << "\nRule: Henrik\t" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else if(settings.getEvenRule()==2 && game.getGeneration()%2==0||settings.getOddRule()==2&& game.getGeneration()%2 !=0)
        {
            game.generation();
            cout << "\nGeneration: " << game.getGeneration()-1<< "\nRule: Anna\t" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else if(settings.getEvenRule()==3 && game.getGeneration()%2==0||settings.getOddRule()==3&& game.getGeneration()%2 !=0)
        {
            game.generation();
            cout << "\nGeneration: " << game.getGeneration()-1<< "\nRule: Marcus\t" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else
        {
            game.generation();
            cout << "\nGeneration: " << game.getGeneration()-1 << "\nRule: Conway\t" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        if (game.evenRule->hasLivingCells() == false && game.oddRule->hasLivingCells() == false)
        {
            terminal.clear();
            terminal.setCursor(settings.getWidth()/3,settings.getHeight()/2);
            std::cout << "\t\t\tGAME OVER!!!\n" << endl;
            std::cout << "\t\t\tAll cells have perished...\nGAME OVER!!!" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            terminal.clear();

        }
        else if(settings.getIterations() < game.getGeneration())
        {
            terminal.clear();
            terminal.setCursor(settings.getWidth()/2,settings.getHeight()/2);
            std::cout << "GAME OVER!!!";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            terminal.clear();
        }
        terminal.resetCursor();
    }while((game.evenRule->hasLivingCells() && game.oddRule->hasLivingCells()) && (settings.getIterations() >= game.getGeneration()));

    terminal.clearColors();
    return 0;
}

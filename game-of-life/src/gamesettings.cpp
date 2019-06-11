/**
  * @file gameSettings.cpp
  * @author Anna Hansson, Henrik Johansson, Marcus Stenroos
  * @version 1.0
  * @brief Implementationsfil för GameSettingsklassen.
  */

#include "gamesettings.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

GameSettings::GameSettings(int pArgc, char* pArgv[]): args(pArgv, pArgv+pArgc)// : argc(pArgc), argv(pArgv)
{
    /**
     * Konstruktor som initerar ett gamesettingsobjekt med de argument som skickas med
     * som parametrar.\n
     * Exempel:\n Argumenten "GameOfLife.exe -s 20x20 -g 100 -f test002.txt läses in som: \n
       char* argv[] = {\n
       (char*)"-s",\n
       (char*)"20x20",\n
       (char*)"-g",\n
       (char*)"200",\n
       (char*)"-f",\n
       (char*)"test002.txt"
     *
     * @param pArgc Antal argument som skickas med.
     * @param pArgv argument och värden.
     */
    //GameOfLife ­-s 160x24 -­er micke -­g 1000 -­f test.txt

    //Försöker finna om -f parameter finns
    std::vector<std::string>::iterator it;
    it = std::find(args.begin(), args.end(), "-f");

    //Om fil finns ska den läsas först
    if(it != args.end())
    {
        int idx = std::distance(args.begin(), it);
        //Läser data från filen
        readFile(args.at(idx + 1));
    }

    //Tolkar argument. Skriver över inställningar från fil,
    //om sådana finns
    for (int i = 0; i < args.size(); i++)
    {
        string arg = args.at(i);
        if (arg == "-h") {
            displayHelp(); //Visa hjälp
        } else if (arg == "-g") {
            int generations = stoi(args.at(i + 1)); //Antal generationer
            setGenerations(generations);
            i++; //Hoppar över nästa argument (antal generationer)
        } else if (arg == "-s") {
            string size(args.at(i + 1)); // T.ex. "20x30"
            setSize(size); //Storlek
            i++; //Hoppar över nästa argument (storlek)
        } else if (arg == "-f") {
            i++; //Hoppar över nästa argument (filnamn)
        }
        else if (arg == "-or")
        {
            string ruleName (args.at( i + 1 ));
            //Gör till versaler.
            for (auto &i : ruleName)
                 i = toupper(i);

            if (ruleName == "HENRIK")
               odd = HENRIK;
            else if (ruleName == "ANNA")
               odd = ANNA;
            else if (ruleName == "MARCUS")
               odd = MARCUS;
            i++;
        }
        else if (arg == "-er")
        {
            string ruleName (args.at( i + 1 ));
            //Gör till stora bokstäver
            for (auto &i : ruleName)
                 i = toupper(i);
            if (ruleName == "HENRIK")
               even = HENRIK;
            else if (ruleName == "ANNA")
               even = ANNA;
            else if (ruleName == "MARCUS")
               even = MARCUS;
            i++;
        }
    }

    it = std::find(args.begin(), args.end(), "-or");

    //Om -er inte finns
    if(it == args.end())
    {
       odd = even;
    }
}

void GameSettings::readFile(string fileName)
{
    try
    {
        int row = 1;
        string data;

        ifstream file;
        file.open(fileName);

        while (std::getline(file, data))
        {
            std::istringstream iss(data);

            if (data.length() > 0)
            {
                if (row == 1) { // Regel för jämna generationer
                    even = stoi(data);
                }
                else if (row == 2){ // Regel för ojämna generationer
                    odd = stoi(data);
                }
                else if (row == 3) { // Generations
                    setGenerations(stoi(data));
                }
                /*if (row == 4) { // Size
                    setSize(data);
                }*/
                else if (row > 3) {
                    std::vector<int> vrow; //Nuvarande rad
                    for (int i = 0; i < data.size(); i++)
                    {
                        char c = data.at(i);
                        vrow.push_back(c - 48);
                    }
                    //Lägger till vectorn i positions vectorn
                    positions.push_back(vrow);
                }
            }
            else if (row == 2 && data.length() == 0) {
                odd = even;
            }
            row++;
        }

        //Höjden är samma som antal rader i positions
        height = positions.size();

        if (height > 0)
        {
            //Första raden avgör spelplanens bredd
            std::vector<int> firstRow = positions.at(0);
            width = firstRow.size();
        }
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        cout << "Something is wrong with the file!" << endl;
    }
}

void GameSettings::displayHelp()
{
    /** Funktion som skriver ut en lista med hjälp och information. */
   cout << "Game Of Life help:" << endl;
       cout << "-h\tHelp" << endl;
       cout << "-er\t<even rulename> [default=conway]" << endl;
       cout << "         {MARCUS, HENRIK, ANNA}" << endl;
       cout << "-or\t<odd rulename> [default=conway]" << endl;
       cout << "         {MARCUS, HENRIK, ANNA}" << endl;
       cout << "-s\t<widthxheight> [default=80x24]" << endl;
       cout << "-g\t<generations> [default=500]" << endl;
       cout << "-f\t<file name for initial state> [default=random state)" << endl;
       exit(1);
}

void GameSettings::setGenerations(int pIterations)
{
    iterations = pIterations;
    if (iterations <= 0) {
        cout << "Parameter -g is either 0 or not a number." << endl;
    }
}

void GameSettings::setSize(string pSizeValue)
{
    try
    {
        size_t xpos = pSizeValue.find('x'); //Hittar positionen av x
        string sw = pSizeValue.substr(0, xpos); //Får ut första värdet från strängen
        string sh = pSizeValue.substr(xpos + 1, pSizeValue.length() - (xpos + 1)); //Får ut sista värdet i strängen (efter x)

        try
        {
            width = stoi(sw); //Konverterar sträng till int (lägnd)
            height = stoi(sh); //Konverterar sträng till int (höjd)
        }
        catch (exception& e)
        {
            throw 1;
        }
    }
    catch (int e)
    {
        if (e == 1) { //Konverteringen går inte att genomföra
            cout << "An exception occurred. Parameter -s is invalid.";
        }
    }
}

void GameSettings::adjustPositions()
{
    /** Läser av cellpositionerna från en .txt fil om en sådan används och anpassar
      * spelplanens storlek efter informationen i filen.*/
    int rowDiff = height - positions.size();

    //Korrigerar antal rader för att passa spelplanen
    if (rowDiff < 0)
    {
        //Ta bort rader
        for (int i = rowDiff; i < 0; i++)
        {
            positions.pop_back();
        }
    }
    else if (rowDiff > 0)
    {
        //Lägga till rader
        for (int i = 0; i < rowDiff; i++)
        {
            std::vector<int> vrow;
            positions.push_back(vrow);
        }
    }


    //Korreigerar radens bredd för att passa spelplanen
    for_each(positions.begin(), positions.end(), [&](std::vector<int> &row)
    {
        int charDiff = width - row.size();

        if (charDiff < 0)
        {
            //Ta bort rader
            for (int i = charDiff; i < 0; i++)
            {
                row.pop_back();
            }
        }
        else if (charDiff > 0)
        {
            //Lägga till rader
            for (int i = 0; i < charDiff; i++)
            {
                row.push_back(0);
            }
        }
    });
}

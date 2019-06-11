/**
  * @headerfile gamesettings.h
  *
  * Innehåller funktioner för att bestämma inställningar för storlek,
  * starttillstånd och spelregler samt defaultvärden för dessa.
  * @version 1.0
  * @author Anna Hansson, Henrik Johansson & Marcus Stenroos
  */

#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Klass som hanterar spelinställningarna.
 */
class GameSettings
{
public:
    //Publika medlemsfunktioner och konstruktor/destruktor.
    enum ruleName {
        CONWAY,
        HENRIK,
        ANNA,
        MARCUS
    };

    GameSettings(int pArgc, char* pArgv[]);
    /** Destruktor */
    ~GameSettings(){}
	//Doxykommentera sen
    void adjustPositions();
    /**
     * Inlinefunktion som bestämmer om aktuell genration är udda eller jämn
     * @param generation int
     * @return ruleName(Enum)
     */
    ruleName getRuleForGeneration(int generation) const
    {
        if (generation % 2 == 0)
        {
            return (ruleName)even;
        }

        return (ruleName)odd;
    }

    /**
     * Inlinefunktion som hämtar värdet på den regel som ska appliceras på jämna generationer.
     * @return ruleName(Enum)
     */
    ruleName getEvenRule() const { return (ruleName)even; }

    /**
     * Inlinefunktion som hämtar värdet på den regel som ska appliceras på jämna generationer.
     * @return ruleName(Enum)
     */
    ruleName getOddRule() const { return (ruleName)odd; }

    /** Inline hämtar inmatat värde för witdth (bredd).
     * @returns Integer.*/
    int getWidth() const { return width; }

    /** Inline hämtar inmatat värde för height(höjd).
     * @returns Intteger*/
    int getHeight() const { return height; }

    /** Inlinefunktion som hämtar inmatat värde för antal Generationer (iterations).
     * @returns Integer */
    int getIterations() const { return iterations; }

    /** Inlinefunktion som kontrollerar om det finns ett argument om att läsa från fil.
     * Om så är fallet ska den läsas först.
     * @return Boolean.*/
    bool hasPositions() const { return positions.size() > 0; }

    /** Läser de olika startpositionerna för cellerna ifrån en textfil.
     * @return Vector av typ Integer.*/
    std::vector<std::vector<int>> getPositions() const { return positions; }

private:
    //Datamedlemmar
    std::vector<std::string> args;

    int even = CONWAY;
    int odd = CONWAY;
    int iterations = 500;
    int width = 80;
    int height = 24;
    std::vector<std::vector<int>> positions;
    //Medlemsfunktioner
    void readFile(string fileName);
    void displayHelp();
    void setGenerations(int pIterations);
    void setSize(string pSizeValue);
};

#endif // GAMESETTINGS_H

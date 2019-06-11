/*
 * Autor       : Mikael Nilsson
 * Filename    : main.cpp
 * Description : Exempel program för att interaktivt testa MathExpresion
 *
*/

#include <memstat.hpp>
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

using namespace std;

#include "MathExpression.h"

int main()
{
    cout << "MathExpression REPL (Read-Eval-Print-Loop)." << endl << "Type quit to exit." << endl;

    string input;

    cout << "Enter a math expression : ";
    getline(cin, input);

    while(input != "quit")
    {
        MathExpression me(input);

        if(me.isValid())
        {
            cout << "'" << me.infixNotation() << "' ==> '"
                 << me.postfixNotation() << "' = '"
                 << me.calculate() << "'" << endl;
        }
        else
        {
            cout << me.errorMessage() << endl;
        }

        cout << "Enter a math expression : ";
        getline(cin, input);
    }

    return 0;
}


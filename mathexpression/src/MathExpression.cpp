/*
*   Author: Anna hansson, Henrik Johansson, Marcus Stenroos
*   File name: MathExpression.cpp
*   Description: Implementationsfil för klassen MathExpression
*/

#include "MathExpression.h"
#include <string>
#include <sstream>
#include <stack>
#include <iostream>
#include <algorithm>

MathExpression::MathExpression(const std::string &expression)
{
    startExpression = expression;
}

std::string MathExpression::infixNotation() const
{
    return startExpression;
}

std::string MathExpression::postfixNotation() const
{
   return infixToPostfix();
}

double MathExpression::calculate()const
{
    return calculatePostfix();
}

bool MathExpression::isValid() const
{
    std::string eq = startExpression;
    int length = eq.length();
    int operators = 0;
    bool flag = true;

    const_cast<std::string&>(message) = ""; //Säkerställer att message är en tom sträng

    // Uttrycket måste vara minst 1 tecken långt
    if (length < 1)
    {
        const_cast<std::string&>(message) = "Expression too short!";
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        //Hämtar tecknet vid position i
        char cc = eq.at(i);
        //Om tecknet inte är en siffra, +, -, /, * eller parentes så är uttrycket/inmatningen felaktig/t
        if (!isdigit(cc) && (cc != '+') && (cc != '-') && (cc != '/') && (cc != '*') && (cc != ',') && (cc != '(') && (cc != ')'))
        {
            const_cast<std::string&>(message) = "Invalid character! Only digits, operators and parentheses allowed.";
            return false;
        }

        if (cc == '(')
        {
            int next = i + 1;

            //Kontrollerar att vi inte är utanför uttryckets totala längd
            if (next <= length)
            {
                for (int y = next; y < length; y++)
                {
                    char nc = eq.at(y);

                    if (nc == ')')
                    {
                        if (y + 1 < length) //Kontrollerar att vi inte hamnat utanför uttryckets längd
                        {
                            char ap = eq.at(y + 1);

                            if (!((ap == '+') ^ (ap == '-') ^ (ap == '/') ^ (ap == '*'))) //Kontrollerar att nästa tecken är en operator
                            {
                                const_cast<std::string&>(message) = "Missing operator between parentheses! Ex (1+1)(5+5)";
                                return false;
                            }
                        }

                        std::string temp = eq.substr(i + 1, y - i - 1); //Plockar ut uttrycket ur parentesen och gör en kontroll
                        MathExpression ime(temp);

                        if (!ime.isValid()) //Det inreuttrycket är ogiltigt
                        {
                            const_cast<std::string&>(message) = "The inner expression '" + temp + "' is not valid! " + ime.errorMessage();
                            return false;
                        }

                        operators++;
                        i = y; //Flyttar fram den yttre for-loopen till positionen efter parentesen
                        break;
                    }
                    else if (nc == '(') //Endast onestlade parenteser är tillåtna
                    {
                        const_cast<std::string&>(message) = "Inner parenthes is found, its not allowed to have double parenthesis! Ex ((2+2)).";
                        return false;
                    }
                    else if (y == length - 1) // Loopat igenom hela uttrycket utan att hitta slutparentes
                    {
                        const_cast<std::string&>(message) = "If you used start '(' than you must end it with ')'!";
                        return false;
                    }
                }
            }
        }
        else if (cc == ')')
        {
            const_cast<std::string&>(message) = "You didn't start with '('!";
            return false;
        }

        //Kontrollerar om inmatningen innehåller följande operatorer
        if ((cc == '+') || (cc == '-') || (cc == '/') || (cc == '*'))
        {
            if (flag && i > 1)
            {
                const_cast<std::string&>(message) = "Double operators are not allowed. Ex ++, --, **, //, +-, etc!.";
                return false;
            }
            else if (flag) //Första tecknet får inte vara en operator
            {
                const_cast<std::string&>(message) = "It is not allowed to start the expression with an operator!";
                return false;
            }
            //Kontrollerar så att ingen operator får finnas sist i uttrycket
            if (i == length - 1)
            {
                const_cast<std::string&>(message) = "The expression can not end with following operators + - / *!";
                return false;
            }
            flag = true;
            operators++;
        }
        else
        {
            flag = false;
        }
    }

    return true;
}

std::string MathExpression::errorMessage() const
{
    return message;
}

MathExpression& MathExpression::operator=(const std::string& expression)
{
    startExpression = "";
    startExpression=expression;
}
std::string MathExpression::infixToPostfix()const
{
    std::string infix = infixNotation();
    //ta bort blanksteg från strängen
    infix.erase(remove_if(infix.begin(), infix.end(), isspace), infix.end());
    std::stringstream ss(infix);
    std::string postfix;
    std::stack<char> operatorStack;
    char c;

    for (int i = 0; i < infix.size(); i++)
        {
            ss >> c;
           //Om c är en operator
            if (c == '+' || c == '-' ||c == '*' || c == '/' )
            {
                postfix.append(" "); //separera operander med mellanslag

                //När det som ligger överst på stacken inte är "(" och operatorn som ska pushas har samma eller lägre prioritet än den som ligger överst
                while (!operatorStack.empty() && operatorStack.top() != '(' && operatorPriority(c) <= operatorPriority(operatorStack.top()))
                {
                    postfix += operatorStack.top();
                    postfix.append(" ");    //separera operatorer med mellanslag
                    operatorStack.pop();
                }
                operatorStack.push(c);
            }
            //Vänsterparentes pushas direkt till stacken
            else if (c == '(')
            {
                operatorStack.push(c);
            }
            //Om högerparentes poppa och lägg till postfix tills vänsterparentes
            else if (c == ')')
            {
                while (!operatorStack.empty() && operatorStack.top() != '(')
                {
                    postfix.append(" ");
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
            //När c inte är en operator eller en parentes lägg direkt i postfix
            else
            {
                postfix += c;
            }
        }

        //Om det finns nåt kvar i stacken lägg det i postfix
        while (!operatorStack.empty()) {
            postfix.append(" ");
            postfix += operatorStack.top();
            operatorStack.pop();
        }

        return postfix;
    }

int MathExpression::operatorPriority(char ch)const
{
    switch (ch)
    {
    case '+':
    case '-': return 1;
    case '/':
    case '*': return 2;
    }
}
double MathExpression::operation(double op1, double op2, char ch) const
{
    switch (ch)
    {
    case '+': return (static_cast<double> (op1 + op2));
        break;
    case '-': return (static_cast<double> (op1 - op2));
        break;
    case'*': return (static_cast<double> (op1 * op2));
        break;
    case '/': return (static_cast<double> (op1 / op2));
        break;
    }
}
double MathExpression::calculatePostfix() const
{

   std::stack<double> operandStack;
   std::string postfix = postfixNotation();
   double op1 = 0;
   double op2 = 0;

        //läs av strängen  från vänster till höger
        for (auto i = 0; i < postfix.size(); i++)
        {
            if(postfix[i] == ' ')
                continue;
            //om tecknet är ett blanksteg forstätt
            else if (isOperator(postfix[i]))
            {
                //Poppa två operander
                op2 = operandStack.top();
                operandStack.pop();
                op1 = operandStack.top();
                operandStack.pop();
                //utför beräkning;
                double result = operation(op1, op2, postfix[i]);
                //pusha resultatet till stacken;
                operandStack.push(result);
            }
            //om tecknet är ett tal
            else if(isdigit(postfix[i]))
            {
                int operand = 0;
                //plocka ut operanden från strängen
                //fortsätt att inkrementera i medan tecknet är en siffra
                while(i < postfix.length() && isdigit(postfix[i]))
                {
                    //Om talet är större än en siffra mulitplicera med 10
                    //och subrahera charkoden för tecknet '0' (dvs 48)
                      operand = (operand*10) + ((postfix[i]) - '0');
                      i++;
                }
                //Gå tillbaka ett steg för att kompensera sista steget
                i--;
                //pusha operanden på stacken
                operandStack.push(operand);
            }
    }
        //Returnera resultatet på stacken;
        return operandStack.top();
}

//Kontrollera om ett tecken är en operator
bool MathExpression::isOperator(const char & aChar) const
{
    char c = aChar;
    if ( c == '+' || c == '-' || c == '*' || c == '/' )
        return true;
    else
        return false;
}


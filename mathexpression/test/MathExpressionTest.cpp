/*
 *  Author: Anna Hansson, Henrik Johansson, Marcus Stenroos
 * Filename: MathExpressionTest.cpp
 * Description: Enhetstester för att testa MathExpressions olika medlemsfunktioner
*/

#ifdef DEBUG
#include <memstat.hpp>
#endif

#include <catch.hpp>
#include "MathExpression.h"
#include <string>
#include <iostream>

using namespace std;

TEST_CASE("MathExpression TestCase: Uttryck med en operator") {

    MathExpression me("3+4");

    SECTION("Addition")
    {

        SECTION("infixNotation")
        {
            REQUIRE(me.infixNotation() == "3+4");
        }

        SECTION("postfixNotation")
        {
            REQUIRE(me.postfixNotation() == "3 4 +");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(7.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("errorMessage")
        {
            REQUIRE(me.errorMessage() == "");
        }

        SECTION("operator =")
        {
            MathExpression nextMe("1+2");
            me = nextMe;
            REQUIRE(me.infixNotation() == "1+2");
        }
    }

    SECTION("Subtraktion")
    {

        me = "12-7";

        SECTION("infixNotation")
        {
            REQUIRE(me.infixNotation() == "12-7");
        }

        SECTION("postfixNotation")
        {
            REQUIRE(me.postfixNotation() == "12 7 -");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(5.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("errorMessage")
        {
            REQUIRE(me.errorMessage() == "");
        }

        SECTION("operator =")
        {
            MathExpression nextMe("7-7");
            me = nextMe;
            REQUIRE(me.infixNotation() == "7-7");
        }
    }

    SECTION("Multiplikation")
    {

        me = "12*7";

        SECTION("infixNotation")
        {
            REQUIRE(me.infixNotation() == "12*7");
        }

        SECTION("postfixNotation")
        {
            REQUIRE(me.postfixNotation() == "12 7 *");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(84.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("errorMessage")
        {
            REQUIRE(me.errorMessage() == "");
        }

        SECTION("operator =")
        {
            MathExpression nextMe("7*7");
            me = nextMe;
            REQUIRE(me.infixNotation() == "7*7");
        }
    }

    SECTION("Division")
    {

        me = "12/7";

        SECTION("infixNotation")
        {
            REQUIRE(me.infixNotation() == "12/7");
        }

        SECTION("postfixNotation")
        {
            REQUIRE(me.postfixNotation() == "12 7 /");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(1.714285));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("errorMessage")
        {
            REQUIRE(me.errorMessage() == "");
        }

        SECTION("operator =")
        {
            MathExpression nextMe("8/7");
            me = nextMe;
            REQUIRE(me.infixNotation() == "8/7");
        }
    }
}

TEST_CASE("MathExpression Testcase: Uttryck med flera operatorer")
{
    SECTION("Addition och multiplikation")
    {
        MathExpression me("4+6*2");

        SECTION("Testa infixnotation")
        {
            REQUIRE(me.infixNotation() == "4+6*2");
        }

        SECTION("Testa postfixnotation")
        {
            REQUIRE(me.postfixNotation() == "4 6 2 * +");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(16.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("Errormessage")
        {
            REQUIRE(me.errorMessage() == "");
        }
    }

    SECTION("Parenteser med Division och addition ")
    {
        MathExpression me("(4+6)/2");

        SECTION("Testa infixnotation")
        {
            REQUIRE(me.infixNotation() == "(4+6)/2");
        }

        SECTION("Testa postfixnotation")
        {
            REQUIRE(me.postfixNotation() == "4 6 + 2 /");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(5.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("Errormessage")
        {
            REQUIRE(me.errorMessage() == "");
        }
    }

    SECTION("Stort uttryck")
    {
        MathExpression me("15/(1+2)");

        SECTION("Testa infixnotation")
        {
            REQUIRE(me.infixNotation() == "15/(1+2)");
        }

        SECTION("Testa postfixnotation")
        {
            REQUIRE(me.postfixNotation() == "15 1 2 + /");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(5.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("Errormessage")
        {
            REQUIRE(me.errorMessage() == "");
        }
    }

    SECTION("Parenteser, Multiplikation och subtraktion ")
    {
        MathExpression me("15*2/(1-3)");

        SECTION("Testa infixnotation")
        {
            REQUIRE(me.infixNotation() == "15*2/(1-3)");
        }

        SECTION("Testa postfixnotation")
        {
            REQUIRE(me.postfixNotation() == "15 2 * 1 3 - /");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(-15.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("Errormessage")
        {
            REQUIRE(me.errorMessage() == "");
        }
    }

    SECTION("Parenteser, Multiplikation och subtraktion ")
    {
        MathExpression me("3*(5+3*6)-5+2*(9/2-3)");

        SECTION("Testa infixnotation")
        {
            REQUIRE(me.infixNotation() == "3*(5+3*6)-5+2*(9/2-3)");
        }

        SECTION("Testa postfixnotation")
        {
            REQUIRE(me.postfixNotation() == "3 5 3 6 * + * 5 - 2 9 2 / 3 - * +");
        }

        SECTION("calculate")
        {
            REQUIRE(me.calculate() == Approx(67.0));
        }

        SECTION("isValid")
        {
            REQUIRE(me.isValid() == true);
        }

        SECTION("Errormessage")
        {
            REQUIRE(me.errorMessage() == "");
        }
    }
}

TEST_CASE("Ogiltliga uttryck")
{

    SECTION("No input")
    {
        MathExpression me("");
        REQUIRE(me.isValid()== false);
        REQUIRE(me.errorMessage()==  "Expression too short!");
    }

    SECTION("Text")
    {
        MathExpression me("HejHoppiLingonSkogen");
        REQUIRE(me.isValid() == false);
        REQUIRE(me.errorMessage()== "Invalid character! Only digits, operators and parentheses allowed.");
    }

    SECTION("35+")
    {
        MathExpression me("35+");
        REQUIRE(me.isValid()== false);
        REQUIRE(me.errorMessage()== "The expression can not end with following operators + - / *!");
    }

    SECTION("(1*2)(3+56)")
    {
        MathExpression me ("(1*2)(3+56)");
        REQUIRE(me.isValid()==false);
        REQUIRE(me.errorMessage()=="Missing operator between parentheses! Ex (1+1)(5+5)");
    }

    SECTION("(2+3")
    {
        MathExpression me ("(2+3");
        REQUIRE (me.isValid()==false);
        REQUIRE (me.errorMessage()==  "If you used start '(' than you must end it with ')'!");
    }
    SECTION("2 1 3")
    {
        MathExpression me ("2 1 3");
        REQUIRE (me.isValid()== false);
        REQUIRE (me.errorMessage()== "Invalid character! Only digits, operators and parentheses allowed.");
    }
    SECTION("2++8")
    {
        MathExpression me ("2++8");
        REQUIRE (me.isValid()==false);
        REQUIRE (me.errorMessage()== "Double operators are not allowed. Ex ++, --, **, //, +-, etc!.");
    }

    SECTION("+8")
    {
        MathExpression me ("+8");
        REQUIRE (me.isValid()==false);
        REQUIRE (me.errorMessage()==  "It is not allowed to start the expression with an operator!");
    }
}

TEST_CASE("Giltliga uttryck")
{

    SECTION("(32+5)-(2+1)")
    {
        MathExpression me("(32+5)-(2+1)");
        REQUIRE(me.isValid()==true);
    }
    SECTION("5*(21+1)-1")
    {
        MathExpression me ("5*(21+1)-1");
        REQUIRE(me.isValid()==true);
        REQUIRE(me.errorMessage()==  "");
    }

    SECTION("(2)+(3)")
    {
        MathExpression me("(2)+(3)");
        REQUIRE (me.isValid()==true);
        REQUIRE(me.errorMessage()==  "");
    }

    SECTION("2")
    {
        MathExpression me("2");
        REQUIRE (me.isValid()==true);
        REQUIRE(me.errorMessage()==  "");
    }

    SECTION("(35)")
    {
        MathExpression me("(35)");
        REQUIRE (me.isValid()==true);
        REQUIRE(me.errorMessage()==  "");
    }
}

TEST_CASE("=operator")
{
    SECTION("Teststuff")
    {
        MathExpression me("1+2");
        REQUIRE(me.infixNotation() == "1+2");
        REQUIRE(me.postfixNotation() == "1 2 +");
        REQUIRE(me.calculate() == 3);
        me = "3+1";
        REQUIRE(me.infixNotation() == "3+1");
        REQUIRE(me.postfixNotation() == "3 1 +");
        REQUIRE(me.calculate() == 4);
    }
}

TEST_CASE("infixtest")
{
    SECTION("simplestring")
    {
        MathExpression me("hej");
        REQUIRE(me.infixNotation() == "hej");
    }
}



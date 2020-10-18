//
// Created by AM on 10/14/2020.
//

#ifndef CALCULATOR_L3_CALCULATOR_H
#define CALCULATOR_L3_CALCULATOR_H


#include <string>
#include <limits>

class Calculator {

public:
    struct operation{
        operation * a = NULL;
        operation * b = NULL;
        operation * parent = NULL;

        std::string internal;

        enum oper {PLUS, MINU, DIVI, MULT, LOG, LN,  POW, SIN, COS, TAN, COT, NONE};
        oper op = NONE;

        double result = std::numeric_limits<double>::min();
    };

    static Calculator::operation resolveOperationResult(Calculator::operation &in); //normally private
    static Calculator::operation resolveOperationResultInt(Calculator::operation &in); //normally private
    static std::string shuntingYard(std::string&);  //priv
    static double calcPostFix(std::string&); //priv
    static double solve(std::string in);

private:

    //static Calculator::operation resolveOperationResult(Calculator::operation &in); //private but not for testing
    static std::string removeSpaces(std::string&);
//    static std::string shuntingYard(std::string&);
//    static double calcPostFix(std::string&);
    static operation makeOperations(std::string&);
    static operation makeOperations(std::string&, int, int);
    static std::string fixParenthesis(std::string&);
    static std::string modAlphas(std::string&);

};


#endif //CALCULATOR_L3_CALCULATOR_H

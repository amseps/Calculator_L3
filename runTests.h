//
// Created by AM on 10/14/2020.
//

#ifndef CALCULATOR_L3_RUNTESTS_H
#define CALCULATOR_L3_RUNTESTS_H

#include <string>
#include "Calculator.h"

class runTests {
public:

    static bool assertEquals(int, int);
    static bool assertEquals(double, double);
    static bool assertEquals(std::string, std::string);
    static bool assertEquals(std::string, double);
    static bool assertEquals(Calculator::operation, double);

    static bool runTheTests();
};



#endif //CALCULATOR_L3_RUNTESTS_H

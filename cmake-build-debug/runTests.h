//
// Created by AM on 10/14/2020.
//

#ifndef CALCULATOR_L3_RUNTESTS_H
#define CALCULATOR_L3_RUNTESTS_H

#include <string>

class runTests {

    runTests();

    bool assertEquals(int, int);
    bool assertEquals(double, double);
    bool assertEquals(std::string, std::string);

    bool runTheTests();
};


#endif //CALCULATOR_L3_RUNTESTS_H

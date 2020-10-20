#include <iostream>

#include "Calculator.h"
#include "runTests.h"


int main(int argc, char ** argv) {

    //runTests::runTheTests();
    
    if(argc > 1){ // 0 is exe location  ;  if there are any CL args then we'll assume it's the function to calculate :)
        std::string in = Calculator::collateProgramArgs(argc, argv);
        //strangely, powershell deletes parenthesis from command line arguments
        double out = Calculator::solve(in);
        std::cout <<  out;
        return out;
    }else { //In line args
        std::string in;
        double returned;
        std::cout << "AM-Calc ; ctrl+c to quit\n>>>";
        while(std::getline(std::cin, in)){
            returned = Calculator::solve(in);
            std::cout << "\t=[" << returned << "]\n>>>";
        }
    }
    return 0;
}
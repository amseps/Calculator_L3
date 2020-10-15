//
// Created by AM on 10/14/2020.
//

#include <iostream>
#include "runTests.h"
#include "Calculator.h"

#include "string"

using namespace std;



bool runTests::assertEquals(int a, int b){
    bool pass = a == b;
    if(pass){
        cout << "PASSED assertEquals " << a << " == " << b << endl;
        return true;
    }else{
        cout << "FAILED assertEquals " << a << " != " << b << endl;
        return false;
    }
}

bool runTests::assertEquals(double a , double b){
    const double epsilon = 0.005f;
    bool pass = (a - b) < epsilon;
    if(pass){
        cout << "PASSED assertEquals " << a << " == " << b << endl;
        return true;
    }else{
        cout << "FAILED assertEquals " << a << " != " << b << endl;
        return false;
    }
}

bool runTests::assertEquals(std::string a , std::string b){
    bool pass = 0 == a.compare(b);
    if(pass){
        cout << "PASSED assertEquals " << a << " == " << b << endl;
        return true;
    }else{
        cout << "FAILED assertEquals " << a << " != " << b << endl;
        return false;
    }
}


bool runTests::runTheTests(){
    try {
        runTests::assertEquals(5, 5);
        runTests::assertEquals("a", "a");
        runTests::assertEquals(1., 1.);
        cout << "Running All the tests: " << endl;

        runTests::assertEquals(Calculator::solve("5 + 7"), 12.);
        runTests::assertEquals(Calculator::solve("5+ 7"), 12.);
        runTests::assertEquals(Calculator::solve("5 +7"), 12.);
        runTests::assertEquals(Calculator::solve("5+7"), 12.);
        runTests::assertEquals(Calculator::solve("5    +    7"), 12.);

        runTests::assertEquals(Calculator::solve("50+70"), 120.);
        runTests::assertEquals(Calculator::solve("5 0+7 0"), 120.);
        runTests::assertEquals(Calculator::solve(" 5 0 + 7 0 "), 120.);
        runTests::assertEquals(Calculator::solve("50+  7  0"), 120.);
        runTests::assertEquals(Calculator::solve("  5   0   +70"), 120.);

        runTests::assertEquals(Calculator::solve("500 + 7"), 507.);
        runTests::assertEquals(Calculator::solve(" 5 0 0 +7"), 507.);

        runTests::assertEquals(Calculator::solve("13 - 10"), 3.);
        runTests::assertEquals(Calculator::solve("13- 10"), 3.);
        runTests::assertEquals(Calculator::solve("13 -10"), 3.);
        runTests::assertEquals(Calculator::solve(" 13-10 "), 3.);

        runTests::assertEquals(Calculator::solve("13 - 20"), -7.);
        runTests::assertEquals(Calculator::solve("13 -30"), -17.);
        runTests::assertEquals(Calculator::solve("100 - 20"), 80.);

        return true;
    }catch(exception e){
        cout << e.what() << endl;
        return false;
    }
}
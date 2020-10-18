//
// Created by AM on 10/14/2020.
//

#include <iostream>
#include <cfloat>
#include <cmath>
#include "runTests.h"
#include "Calculator.h"

#include "string"

using namespace std;



bool runTests::assertEquals(int a, int b){
    bool pass = a == b;
    if(pass){
        cout << "assertEquals " << a << " == " << b << endl;
        return true;
    }else{
        cout << "-> FAILED assertEquals " << a << " != " << b << endl;
        return false;
    }
}

bool runTests::assertEquals(double a , double b){
    bool pass = abs(a - b) < DBL_EPSILON;
    if(pass){
        cout << "assertEquals " << a << " == " << b << endl;
        return true;
    }else{
        cout << "-> FAILED assertEquals " << a << " != " << b << endl;
        return false;
    }
}

bool runTests::assertEquals(std::string a , std::string b){
    bool pass = 0 == a.compare(b);
    if(pass){
        cout << "assertEquals " << a << " == " << b << endl;
        return true;
    }else{
        cout << "-> FAILED assertEquals " << a << " != " << b << endl;
        return false;
    }
}

bool runTests::assertEquals(string a, double b) {
    cout << "{" << a << "} ->\t\t";
    return runTests::assertEquals(Calculator::solve(a), b);
}

bool runTests::assertEquals(Calculator::operation a, double b) {
    if(a.b != NULL) {
        cout << "bin-operation:{" << a.a->result << " " << a.op << " " << a.b->result << "} ->\t\t";
    }else{
        cout << "una-operation:{" << a.a->result << "<-" << a.op << "} ->\t\t";
    }
    Calculator::operation result = Calculator::resolveOperationResult(a);
    return runTests::assertEquals(result.result, b);
}


bool runTests::runTheTests(){
    try {
        cout << "\n\tTESTING" << endl;
        runTests::assertEquals(5, 5);
        runTests::assertEquals("a", "a");
        runTests::assertEquals(1., 1.);

        cout << "\n\tRunning Operation Tests" << endl;
        Calculator::operation main;
        Calculator::operation a;
        Calculator::operation b;
        main.a = &a;
        main.b = &b;
        //binary
        a.result = 5; b.result = 5; main.op = Calculator::operation::oper::PLUS;
        assertEquals(main, 10);
        a.result = -5; b.result = 5; main.op = Calculator::operation::oper::PLUS;
        assertEquals(main, 0);
        a.result = -5; b.result = -5; main.op = Calculator::operation::oper::PLUS;
        assertEquals(main, -10);
        a.result = 5; b.result = 5; main.op = Calculator::operation::oper::MINU;
        assertEquals(main, 0);
        a.result = 5; b.result = 5; main.op = Calculator::operation::oper::MULT;
        assertEquals(main, 25);
        a.result = 5; b.result = 5; main.op = Calculator::operation::oper::DIVI;
        assertEquals(main, 1);
        a.result = 5; b.result = 3; main.op = Calculator::operation::oper::POW;
        assertEquals(main, 125);

        main.b = NULL;

        //unary
        a.result = 5; main.op = Calculator::operation::oper::LOG;
        assertEquals(main, log(5));
        a.result = 5; main.op = Calculator::operation::oper::LN;
        assertEquals(main, log(5)/log(exp(1)));
        a.result = 5; main.op = Calculator::operation::oper::SIN;
        assertEquals(main, sin(5));
        a.result = 5; main.op = Calculator::operation::oper::COS;
        assertEquals(main, cos(5));
        a.result = 5; main.op = Calculator::operation::oper::TAN;
        assertEquals(main, tan(5));

        //???
        a.result = 5; main.op = Calculator::operation::oper::NONE;
        assertEquals(main, 5);

        cout << "\n\tShunting Yard Tests: " << endl;
        string s = "123+456";
        assertEquals("123 456 + ", Calculator::shuntingYard(s));
        s = "5*5";
        assertEquals("5 5 * ", Calculator::shuntingYard(s));
        s = "(5*5)";
        assertEquals("5 5 * ", Calculator::shuntingYard(s));
        s = "(5*5)+5";
        assertEquals("5 5 * 5 + ", Calculator::shuntingYard(s));
        s = "f5*f5";
        assertEquals("f5 f5 * ", Calculator::shuntingYard(s));
        s = "(f5*f5)+f5";
        assertEquals("f5 f5 * f5 + ", Calculator::shuntingYard(s));
        s = "(f5^f5)/5";
        assertEquals("f5 f5 ^ 5 / ", Calculator::shuntingYard(s));
        s = "s5";
        assertEquals("5 s ", Calculator::shuntingYard(s));
        s = "s(5)";
        assertEquals("5 s ", Calculator::shuntingYard(s));
        s = "s(5+5)";
        assertEquals("5 5 + s ", Calculator::shuntingYard(s));

        s = "(5+5+5)";
        assertEquals("5 5 5 + + ", Calculator::shuntingYard(s));


        cout << "\n\tRunning Basic Tests: " << endl;

        runTests::assertEquals("5 + 5 + 5", 15);

        runTests::assertEquals("", 0);
        runTests::assertEquals("()", 0);
        runTests::assertEquals("(5)", 5);
        runTests::assertEquals("(0)()", 0);

        runTests::assertEquals("5 + 7", 12.);
        runTests::assertEquals("5+ 7", 12.);
        runTests::assertEquals("5 +7", 12.);
        runTests::assertEquals("5+7", 12.);
        runTests::assertEquals("5    +    7", 12.);

        runTests::assertEquals("5.+7.", 12.);
        runTests::assertEquals("5.0+7.0", 12.);

        runTests::assertEquals("5.2+7.2", 12.4);

        runTests::assertEquals("50+70", 120.);
        runTests::assertEquals("5 0+7 0", 120.);
        runTests::assertEquals(" 5 0 + 7 0 ", 120.);
        runTests::assertEquals("50+  7  0", 120.);
        runTests::assertEquals("  5   0   +70", 120.);

        runTests::assertEquals("500 + 7", 507.);
        runTests::assertEquals(" 5 0 0 +7", 507.);

        runTests::assertEquals("13 - 10", 3.);
        runTests::assertEquals("13- 10", 3.);
        runTests::assertEquals("13 -10", 3.);
        runTests::assertEquals(" 13-10 ", 3.);

        runTests::assertEquals("13 - 20", -7.);
        runTests::assertEquals("13 -30", -17.);
        runTests::assertEquals("100 - 20", 80.);

        runTests::assertEquals("-50 + 20", -30.);
        runTests::assertEquals("-1 + 20", -19.);
        runTests::assertEquals("-0 + 20", 20.);
        runTests::assertEquals("-5 + -5", -10.);
        runTests::assertEquals("-5 - -5", 0.);
        runTests::assertEquals("-5 - -10", -5.);
        runTests::assertEquals("-50 + 20", -30.);

        runTests::assertEquals("2*2", 4.);
        runTests::assertEquals("2*0", 0.);
        runTests::assertEquals("2* 1", 2.);
        runTests::assertEquals("2*-2", -4.);
        runTests::assertEquals("-2*-2", 4.);
        runTests::assertEquals("2*100", 200.);

        runTests::assertEquals("2/2", 1.);
        runTests::assertEquals("2/4", .5);
        runTests::assertEquals("0/4", 0.);
        runTests::assertEquals("0/-4", 0.);
        runTests::assertEquals("1/0", 0.);
        runTests::assertEquals("-1/-0", 0.);

        runTests::assertEquals("2^2", 4.);
        runTests::assertEquals("2^ 4", 16);
        runTests::assertEquals("2^-2", pow(2, -2));
        runTests::assertEquals("2^20", pow(2, 20));
        runTests::assertEquals("-2^2", pow(-2, 2));
        runTests::assertEquals("-2^-2", 0);

        runTests::assertEquals("sin5", sin(5));
        runTests::assertEquals("sin(5)", sin(5));
        runTests::assertEquals("sin-5", sin(-5));
        runTests::assertEquals("sin(-5)", sin(-5));

        runTests::assertEquals("cos5", cos(5));
        runTests::assertEquals("cos(5)", cos(5));
        runTests::assertEquals("cos-5", cos(-5));
        runTests::assertEquals("cos(-5)", cos(-5));

        runTests::assertEquals("tan5", tan(5));
        runTests::assertEquals("tan(5)", tan(5));
        runTests::assertEquals("tan-5", tan(-5));
        runTests::assertEquals("tan(-5)", tan(-5));

        runTests::assertEquals("cot5", cos(5)/sin(5));
        runTests::assertEquals("cot(5)", cos(5)/sin(5));
        runTests::assertEquals("cot-5", cos(-5)/sin(-5));
        runTests::assertEquals("cot(-5)", cos(-5)/sin(-5));

        runTests::assertEquals("log(5)", log(5));
        runTests::assertEquals("log(-5)", log(-5));
        runTests::assertEquals("log5", log(5));
        runTests::assertEquals("log-5", log(-5));

        runTests::assertEquals("ln(5)", log(5) / log(exp(1)));
        runTests::assertEquals("ln5", log(5) / log(exp(1)));
        runTests::assertEquals("ln(-5)", log(-5) / log(exp(1)));
        runTests::assertEquals("ln-5", log(-5) / log(exp(1)));

        cout << "\n\tRunning Complex Tests: \n";

        runTests::assertEquals("(5) + (7)", 12.);
        runTests::assertEquals("(5 + (7))", 12.);
        runTests::assertEquals("(((5) + (7)))", 12.);
        runTests::assertEquals("(((((5 + 7", 12.);
        runTests::assertEquals("(5 + 7) / 12", 1.);
        runTests::assertEquals("(5 + 7) / 4", 3.);
        runTests::assertEquals("(5 + 7) / -12", -1.);
        runTests::assertEquals("-(5 + 7) / 12", -1.);
        runTests::assertEquals("-(-(5 + 7) / -12)", -1.);
        runTests::assertEquals("(5 + 7) / 12", 1.);

        runTests::assertEquals("(5 / 7 / 12)", 5./7./12.);
        runTests::assertEquals("2*2/2*2/2*2/2", 2.);
        runTests::assertEquals("(((1+1)+1)/(4-1)) * 12", 12.);
        runTests::assertEquals("log(5*(5)/5)", log(5.));


        return true;
    }catch(exception e){
        cout << e.what() << endl;
        return false;
    }
}
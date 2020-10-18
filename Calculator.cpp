//
// Created by AM on 10/14/2020.
//

#include "Calculator.h"

#include <iostream>
#include <string>
#include <limits>
#include <math.h>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

string Calculator::removeSpaces(string &in){
    int count = 0;
    for(int i = 0 ; in[i] != '\0'; i++){
        if(in[i] != ' ') {
            in[count++] = in[i];
        }
    }
    in[count] = '\0';
    in.resize(count);
    return in;
}

string Calculator::fixParenthesis(string &in){
    int count = 0;
    for(int i = 0; i < in.length(); i++){
        if(in[i] == '('){
            count++;
        }else if(in[i] == ')'){
            count--;
        }
    }
    if(count > 0){ // if too many opening parenthesis
        for(int i = 0 ; i < count; i++){
            in.append(")");
        }
    }else if(count < 0){ // too many closing
        for(int i = 0; i < count ; i++){
            in.insert(0, "(");
        }
    }
    double pass = true;

    int i = 0;
    return in;
}

std::string Calculator::modAlphas(std::string& in){ // you should really use some switch statements in this u ape
    //like fr who wrote this function jfc
    if(in.length() == 0) return "";
    for(int i = 0 ; i < in.length(); i++) { // FOR ALL CHARACTERS
        if ( // if legal char
                isdigit(in[i])  //legal chars ; digits
                || in[i] == '('  //parenthesis
                || in[i] == ')'
                || in[i] == '.' //dot
                || in[i] == '+'
                //|| in[i] == '-' // we handle minus specially below
                || in[i] == '/'
                || in[]
                ) {
            // ?? do nothing
        }else if(i+3 < in.length()) { // if has some chars left
            if (in[i] == 'c') {//cos
                if (in[i + 1] == 'o' && in[i + 2] == 's') { //cos
                    in = in.substr(0, i) + in.substr(i + 3, in.length() - i); // remove the os
                } else if(in[i + 1] == 'o' && in[i + 2] == 't') {//cot
                    in = in.substr(0, i) + in.substr(i + 3, in.length() - i); //^same line^
                }else {
                    in = in.substr(0, i - 1) + in.substr(i + 1, in.length() - (i + 1));
                }
            }else if (in[i] == 's') {//sin
                if (in[i + 1] == 'i' && in[i + 2] == 'n') {
                    in = in.substr(0, i) + in.substr(i + 3, in.length() - i); // remove the in
                } else {
                    in = in.substr(0, i - 1) + in.substr(i + 1, in.length() - (i + 1));
                }
            } else if (in[i] == 't') {//tan
                if (in[i + 1] == 'a' && in[i + 2] == 'n') {
                    in = in.substr(0, i) + in.substr(i + 3, in.length() - i); // remove the an
                } else {
                    in = in.substr(0, i - 1) + in.substr(i + 1, in.length() - (i + 1));
                }
            } else if(in[i] == 'l'){
                if(in[i+1] == 'o' && in[i+2] == 'g'){
                    in = in.substr(0, i) + in.substr(i + 3, in.length() - (i+3)); // remove the og
                }else if(in[i+1] == 'n') {//ln{
                    in = in.substr(0, i-1) + in.substr(i + 1, in.length() - (i+1)); //remove the l , n is code for ln
                }else {
                    in = in.substr(0, i - 1) + in.substr(i + 1, in.length() - (i + 1));
                }
            }
        }else if (i+2 < in.length()) { // check ln, if enough roome enough chars
            if(in[i+1] == 'n'){ //ln{
                in = in.substr(0, i-1) + in.substr(i + 1, in.length() - (i+1)); //remove the l , n is code for ln
            }
        }else{ //if some other dumb character, kill it, decrement i to inspect char that took its place
            in = in.substr(0, i-1) + in.substr(i + 1, in.length() - (i+1)); // remove this value
            i--;
        }
    }// FOR ALL CHARACTERS IN STRING

    if(in[0] == '-') in[0] = 'f'; // see below
    for(int i = 1 ; i < in.length(); i++){ // turn negatives into i. [-5] -> [f5] , [-5--5] -> [f5+f5];
        if(in[i] == '+' || in[i] == '*' || in[i] == '/' || in[i] == 'l' || in[i] == 'n' || in[i] == '^' || in[i] == 'c' || in[i] == 't' || in[i] == 's' || in[i] == ')' || in[i] == '('){
            // if + * / l n ^ c t o s ( )
            if(in[i+1] == '-') in[i+1] = 'f'; // if next char is -, that means negative number not sub
        }else if(in[i] == '-'){//must be subtraction
            in[i] = '+';
            in.insert(i+1, "+");
        }
    }

    return in; //idk if this function works lole
}

Calculator::operation Calculator::resolveOperationResult(Calculator::operation &in){
    resolveOperationResultInt(in);
    if(in.a != NULL) delete in.a;
    if(in.b != NULL) delete in.b;
    //done with children , kill them
    return in;
}

Calculator::operation Calculator::resolveOperationResultInt(Calculator::operation &in){
    if(in.a == NULL && in.b == NULL) { // A and B are Null
        in.result = std::numeric_limits<double>::min();
    }else if(in.b == NULL){ // B is Null only, unary operation
        switch(in.op){
            case operation::oper::LOG:
                in.result = log(in.a->result);
                break;
            case operation::oper::LN:
                in.result = (log(in.a->result)/log(exp(1)));
                break;
            case operation::oper::SIN:
                in.result = sin(in.a->result);
                break;
            case operation::oper::COS:
                in.result = cos(in.a->result);
                break;
            case operation::oper::TAN:
                in.result = tan(in.a->result);
                break;
            case operation::oper::COT:
                in.result = cos(in.a->result) / sin(in.a->result);
                break;
            case operation::oper::NONE:
                in.result = in.a->result;
                break;
            default:
                cout << "ERR";
                in.result = in.a->result;
                break;
        }
    }else { // binary operations
        switch (in.op) {
            case operation::oper::PLUS:
                in.result = in.a->result + in.b->result;
                break;
            case operation::oper::MINU:
                in.result = in.a->result - in.b->result;
                break;
            case operation::oper::DIVI:
                in.result = in.a->result / in.b->result;
                break;
            case operation::oper::MULT:
                in.result = in.a->result * in.b->result;
                break;
            case operation::oper::POW:
                in.result = pow(in.a->result , in.b->result);
                break;
            default:
                cout << "ERR";
                in.result = in.a->result;
                break;
        }
    }
    return in;
}

Calculator::operation Calculator::makeOperations(string &in){
    return makeOperations(in, 0, in.length());
}

Calculator::operation Calculator::makeOperations(string &in, int start, int end){
    /*
     * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
     * Shunting yard algorithm
    */
    Calculator::operation root;
    if(in[start] == '('){ // P

    }else {
        for (int i = start; i < end; i++) { // E
            if (in[i] == '^') {

            }
        }
        for (int i = start; i < end; i++) { //signs?
            if (in[i] == 'l' || in[i] == 's' || in[i] == 'c' || in[i] == 't' || in[i] == 'n' || in[i] == 'o') {

            }
        }
        for (int i = start; i < end; i++) { //MD
            if (in[i] == '/' || in[i] == '*') {

            }
        }
        if (in[start] == '+') {//A   S-> there should be no - signs anymore

        }
    }
    return root;
}

string Calculator::shuntingYard(string &in){
    stack<string> st;
    queue<string> qu;
    for(int i = 0 ; i < in.length() ; i++){
        char n;
        char c = in[i];
        switch(c){
            case '(':
                st.push(string(1, c));
                break;
            case ')':
                if(st.size() > 0) {
                    string thisstring = st.top();
                    n = thisstring[0]; //profound
                    while (n != '(') {
                        st.pop();
                        qu.push(string(1, n));
                        thisstring = st.top();
                        n = thisstring[0]; //profound
                    }
                    st.pop();
                }
                break;
            case '^':
                st.push(string(1,c));
                break;
            case 's': case 'c': case 't': case 'o': case 'l': case 'n':
                if(n == '^') {
                    st.push(string(1, c));
                }else{
                    st.push(string(1,c));
                }
                break;
            case '*': case '/':
                (st.size() > 0)? n = st.top()[0] : n = 'x';
                if(n == 's' || n == 'c' || n == 't' || n == 'o' || n == 'l' || n == 'n' || n == '^'){
                    qu.push(string(1, c));
                }else{
                    st.push(string(1, c));
                }
                break;
            case '+': case '-':
                (st.size() > 0)? n = st.top()[0] : n = 'x';
                if(
                        n == '^'
                        ||n == 's' || n == 'c' || n == 't' || n == 'o' || n == 'l' || n == 'n'
                        || n == '*' || n == '/'
                ){
                    qu.push(string(1, c));
                }else{
                    st.push(string(1, c));
                }
                break;
            case 'f':
            case '.':
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                int end = i;
                while( (isdigit(in[end]) || in[end] == 'f'|| in[end] == '.')) {
                    end++;
                    //go to end of this int I found
                }
                qu.push(in.substr(i, end-i)); // push that range
                i = end-1; // move i forward past this number
                break;
        }
    }//Iterate In string
    while(st.size() > 0){
        string n = st.top();
        st.pop();
        qu.push(n);
    }
    string out = "";
    while(qu.size() > 0){
        out += qu.front() + " ";
        qu.pop();
    }
    return out;
}

double Calculator::calcPostFix(std::string& in){ // https://www.geeksforgeeks.org/stack-set-4-evaluation-postfix-expression/
    string curr;
    size_t pos = 0;
    size_t lastpos = 0;
    double a;
    stack<double> st;
    pos = in.find(" ", lastpos);
    double thisdig;
    while(pos != string::npos){ //i'm shocked with how many needless calculations are in this function
        char c = in[lastpos];
        if(isdigit(c) || c == 'f' || c == '.' ){
            bool negative = false;
            if(c == 'f'){
                negative = true; //hmm
                lastpos = pos+1;
            }
            thisdig = stod(in.substr(lastpos, pos-lastpos));
            if(negative) thisdig = -thisdig;
            st.push(thisdig);
        }else{ //value is not a number
            thisdig = st.top();
            st.pop();
            switch(c){
                case 's': //unary operators
                    thisdig = sin(thisdig);
                    st.push(thisdig);
                    break;
                case 'c':
                    thisdig = cos(thisdig);
                    st.push(thisdig);
                    break;
                case 't':
                    thisdig = tan(thisdig);
                    st.push(thisdig);
                    break;
                case 'o':
                    a = cos(thisdig) / sin(thisdig);
                    st.push(thisdig);
                    break;
                case 'l':
                    a = log(thisdig);
                    st.push(thisdig);
                    break;
                case 'n':
                    a = log(thisdig)/log(exp(1));
                    st.push(thisdig);
                    break;

                case '+': //binary operators
                    thisdig = thisdig + st.top();
                    st.pop();
                    st.push(thisdig);
                    break;
                case '-':
                    thisdig = thisdig - st.top();
                    st.pop();
                    st.push(thisdig);
                    break;
                case '*':
                    thisdig = thisdig * st.top();
                    st.pop();
                    st.push(thisdig);
                    break;
                case '/':
                    thisdig = thisdig / st.top();
                    st.pop();
                    st.push(thisdig);
                    break;
                case '^':
                    thisdig = pow(thisdig, st.top());
                    st.pop();
                    st.push(thisdig);
                    break;

                default:
                    cout << "???" << endl;
                    throw new exception();
                    break;
            }
        }
        lastpos = pos+1;
        pos = in.find(" ", lastpos); //sometimes u just gotta clone lines idk
    }
    return a;
}

double Calculator::solve(string in){
    try {
        Calculator::removeSpaces(in);
        Calculator::fixParenthesis(in);
        Calculator::modAlphas(in);
        string post = Calculator::shuntingYard(in);
        double answer = Calculator::calcPostFix(post);
        return answer;

    }catch(exception e){
        cout << e.what();
        return std::numeric_limits<double>::min();
    }
    return -1;
}

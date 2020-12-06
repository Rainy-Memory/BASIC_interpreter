/*
 * File: Basic.cpp
 * ---------------
 * Name: [Rainy_Memory]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            processLine(getLine(), program, state);
        } catch (ErrorException &ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string first_ = scanner.nextToken();
    TokenType first_type = scanner.getTokenType(first_);
    if (first_type == NUMBER) {
        int line_number = stringToInteger(first_);
        program.addSourceLine(line_number, line);
        string command_type = scanner.nextToken();
    }
    else {
        if (first_ == "LET") {
            string var = scanner.nextToken();
            string equal_ = scanner.nextToken();
            Expression *exp = parseExp(scanner);
            int value = exp->eval(state);
            state.setValue(var, value);
            delete exp;
        }
        else if (first_ == "PRINT") {
            Expression *exp = parseExp(scanner);
            int value = exp->eval(state);
            cout << value << endl;
            delete exp;
        }
        else if (first_ == "INPUT") {
            string var = scanner.nextToken();
            string value_str = getLine("?\n");
            int value = stringToInteger(value_str);
            state.setValue(var, value);
        }
        
        
        else if (first_ == "RUN") {
            program.run(state);
        }
        else if (first_ == "LIST") {
            program.print_list();
        }
        else if (first_ == "CLEAR") {
            program.clear();
        }
        else if (first_ == "QUIT") {
            exit(0);
        }
        else if (first_ == "HELP") {
            cout << "HELP" << endl;
            //todo add help info
        }
        else {
            throw ErrorException("SYNTAX ERROR");
        }
    }
    
    
    
    /*Expression *exp = parseExp(scanner);
    int value = exp->eval(state);
    cout << value << endl;
    delete exp;*/
}

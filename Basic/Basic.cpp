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
    //cout << "Welcome to BASIC interpreter!" << endl;
    //cout << "Input \"HELP\" to get more information." << endl;
    while (true) {
        try {
            processLine(getLine(), program, state);
        } catch (ErrorException &ex) {
            string msg = ex.getMessage();
            string ErrorReport;
            if (msg == "DIVIDE BY ZERO")ErrorReport = "DIVIDE BY ZERO";
            else if (msg == "INVALID NUMBER")ErrorReport = "INVALID NUMBER";
            else if (msg == "VARIABLE NOT DEFINED")ErrorReport = "VARIABLE NOT DEFINED";
            else if (msg == "LINE NUMBER ERROR")ErrorReport = "LINE NUMBER ERROR";
            else if (msg == "SYNTAX ERROR")ErrorReport = "SYNTAX ERROR";
            else if (msg == "Divided by zero")ErrorReport = "DIVIDE BY ZERO";
            else {
                bool flag = false;
                bool flag_syntax = true;
                string msg_temp;
                for (int i = 0; i < msg.size(); i++) {
                    if (flag)msg_temp += msg[i];
                    if (msg[i] == ' ') {
                        flag = true;
                    }
                }
                if (msg_temp == "is undefined") {
                    ErrorReport = "VARIABLE NOT DEFINED";
                    flag_syntax = false;
                }
                
                flag = false;
                const string il_int = "stringToInteger: Illegal integer format";
                if (msg.size() > 40) {
                    for (int i = 0; i < 40; i++) {
                        if (msg[i] != il_int[i]) {
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag) {
                    ErrorReport = "INVALID NUMBER";
                    flag_syntax = false;
                }
                
                if (flag_syntax)ErrorReport = "SYNTAX ERROR";
            }
            //cerr << "Error: " << ex.getMessage() << endl;
            cout << ErrorReport << endl;
        }
    }
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
        if (line_number <= 0)throw ErrorException("LINE NUMBER ERROR");
        if(scanner.hasMoreTokens()){
            try {
                program.addSourceLine(line_number, line);
            } catch (ErrorException &ex) {
                program.removeSourceLine(line_number);
                throw ErrorException(ex.getMessage());
            }
        }
        else program.removeSourceLine(line_number);
    }
    else {
        if (first_ == "LET") {
            string var = scanner.nextToken();
            if (judgeReservedWords(var))throw ErrorException("SYNTAX ERROR");
            string equal_ = scanner.nextToken();
            Expression *exp;
            int value;
            exp = parseExp(scanner);
            value = exp->eval(state);
            state.setValue(var, value);
            delete exp;
        }
        else if (first_ == "PRINT") {
            Expression *exp;
            int value;
            exp = parseExp(scanner);
            value = exp->eval(state);
            cout << value << endl;
            delete exp;
        }
        else if (first_ == "INPUT") {
            string var = scanner.nextToken();
            if (scanner.hasMoreTokens())throw ErrorException("SYNTAX ERROR");
            if (judgeReservedWords(var))throw ErrorException("SYNTAX ERROR");
            string value_str;
            int value;
            while (true) {
                try {
                    value_str = getLine(" ? ");
                    value = stringToInteger(value_str);
                } catch (...) {
                    cout << "INVALID NUMBER" << endl;
                    continue;
                }
                break;
            }
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
            state.clear();
        }
        else if (first_ == "QUIT") {
            exit(0);
        }
        else if (first_ == "HELP") {
            //cout << "Input serial number of key words to know more:" << endl;
            cout << "1: available statements of BASIC" << endl;
            cout << "Available statements are as follow:" << endl;
            cout << "REM : This statement is used for comments." << endl;
            cout << "LET var = exp : This statement is BASIC’s assignment statement." << endl;
            cout << "PRINT exp : This statement print the value of the expression on the console." << endl;
            cout << "INPUT var : This statement print a prompt consisting of the string \" ? \" and then to\n"
                    "read in a value to be stored in the variable." << endl;
            cout << "END : Marks the end of the program. Execution halts when this line is reached.\n"
                    "Execution also stops if the program continues past the last numbered line." << endl;
            cout << "GOTO n : This statement transfers control unconditionally to line n in the program." << endl;
            cout << "IF exp cmp exp THEN n : This statement performs a conditional transfer of control. On\n"
                    "encountering such a statement, the BASIC interpreter calculate \"exp cmp exp\".\n"
                    "If the result of the comparison is true, transfers control to line n in the\n"
                    "program. if not, the program continues with the next line in sequence." << endl;
            cout << endl;
            
            cout << "2: commands of BASIC interpreter" << endl;
            cout << "Available interpreter command are as follow:" << endl;
            cout << "RUN : This command starts program execution." << endl;
            cout << "LIST : This command lists the steps in the program in numerical sequence." << endl;
            cout << "CLEAR : This command deletes all program and variables." << endl;
            cout << "QUIT : This command exits from the BASIC interpreter." << endl;
            cout << "HELP : This command provides a simple help message describing your interpreter." << endl;
            cout << endl;
            
            cout << "3: Error Reporting" << endl;
            cout << "Possible error reporting are as follow:" << endl;
            cout << "DIVIDE BY ZERO : Calculating some number divide by zero." << endl;
            cout << "INVALID NUMBER : User types wrong value to answer INPUT statement." << endl;
            cout << "VARIABLE NOT DEFINED : A variable used before assigned it." << endl;
            cout << "LINE NUMBER ERROR GOTO : statement's line number not exist." << endl;
            cout << "SYNTAX ERROR : Any other errors." << endl;
            cout << endl;
            
            cout << "Written by Rainy Memory" << endl;
        }
        else {
            throw ErrorException("SYNTAX ERROR");
        }
    }
    /*Expression *exp = parseExp(scanner);
    int value = exp->eval(state);
    cout << value << " "<<exp->toString()<<" " << exp->getType()<< endl;
    delete exp;*/
}

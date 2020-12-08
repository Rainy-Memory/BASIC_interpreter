/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"

using namespace std;

Statement *stringToStatement(string line) {
    //todo
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string lineNumber_str = scanner.nextToken();
    string commandType = scanner.nextToken();
    if (commandType == "REM") {
        return new rem_statement;
    }
    else if (commandType == "LET") {
        Expression *exp;
        exp = parseExp(scanner);
        return new let_statement(exp);
    }
    else if (commandType == "PRINT") {
        Expression *exp;
        exp = parseExp(scanner);
        return new print_statement(exp);
    }
    else if (commandType == "INPUT") {
        string var = scanner.nextToken();
        if (scanner.hasMoreTokens())throw ErrorException("SYNTAX ERROR");
        return new input_statement(var);
    }
    else if (commandType == "END") {
        if (scanner.hasMoreTokens())throw ErrorException("SYNTAX ERROR");
        return new end_statement;
    }
    else if (commandType == "GOTO") {
        string n_str = scanner.nextToken();
        if (scanner.getTokenType(n_str) != NUMBER)throw ErrorException("SYNTAX ERROR");
        if (scanner.hasMoreTokens())throw ErrorException("SYNTAX ERROR");
        return new goto_statement(stringToInteger(n_str));
    }
    else if (commandType == "IF") {
        return new if_statement(line);
    }
    else {
        throw ErrorException("SYNTAX ERROR");
    }
}


bool judgeReservedWords(string var){
    if(var=="REM")return true;
    if(var=="LET")return true;
    if(var=="PRINT")return true;
    if(var=="INPUT")return true;
    if(var=="END")return true;
    if(var=="GOTO")return true;
    if(var=="IF")return true;
    if(var=="THEN")return true;
    if(var=="RUN")return true;
    if(var=="LIST")return true;
    if(var=="CLEAR")return true;
    if(var=="QUIT")return true;
    if(var=="HELP")return true;
    return false;
}


Program::Program() {
    //do nothing?
}

Program::~Program() {
    for (const auto &element : program_body) {
        delete (element.second).parsed_representation;
    }
}

void Program::clear() {
    while (!program_body.empty()) {
        program_body.erase(program_body.begin());
    }
}

void Program::addSourceLine(int lineNumber, string line) {
    if (program_body.count(lineNumber)) {
        removeSourceLine(lineNumber);
    }
    program_line temp;
    temp.original_source_line = line;
    temp.parsed_representation = nullptr;
    program_body[lineNumber] = temp;
    setParsedStatement(lineNumber, stringToStatement(line));
}

void Program::removeSourceLine(int lineNumber) {
    if (program_body[lineNumber].parsed_representation != nullptr)delete program_body[lineNumber].parsed_representation;
    program_body.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
    return program_body[lineNumber].original_source_line;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    program_body[lineNumber].parsed_representation = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
    return program_body[lineNumber].parsed_representation;
}

int Program::getFirstLineNumber() {
    int first_line_number = -1;
    if (!program_body.empty()) {
        first_line_number = program_body.begin()->first;
    }
    return first_line_number;
}

int Program::getNextLineNumber(int lineNumber) {
    auto iter = program_body.find(lineNumber);
    iter++;
    int next_line_number = -1;
    if (iter != program_body.end()) {
        next_line_number = iter->first;
    }
    return next_line_number;
}

void Program::run(EvalState &state) {
    int execute_line = getFirstLineNumber();
    while (true) {
        if (execute_line == -1)break;
        try {
            program_body[execute_line].parsed_representation->execute(state);
            execute_line = getNextLineNumber(execute_line);
        }
        catch (ControlStatement &a) {
            execute_line = a.getMessage();
            if ((execute_line != -1) && (!program_body.count(execute_line)))throw ErrorException("LINE NUMBER ERROR");
        }
    }
}

void Program::print_list() {
    for (const auto &element : program_body) {
        cout << (element.second).original_source_line << endl;
    }
}
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
#include "parser.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/error.h"

using namespace std;

Statement *stringToStatement(string line) {
    //todo
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string lineNumber_str = scanner.nextToken();
    string commandType=scanner.nextToken();
    if(commandType=="REM"){
        return new rem_statement;
    }
    else if(commandType=="LET"){
        Expression *exp = parseExp(scanner);
        return new let_statement(exp);
    }
    else if(commandType=="PRINT"){
        Expression *exp = parseExp(scanner);
        return new print_statement(exp);
    }
    else if(commandType=="INPUT"){
        string var=scanner.nextToken();
        if(scanner.hasMoreTokens())throw ErrorException("SYNTAX ERROR");
        
    }
    else if(commandType=="END"){
    
    }
    else if(commandType=="GOTO"){
    
    }
    else if(commandType=="IF") {
    
    }
    else {
        throw ErrorException("SYNTAX ERROR");
    }
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
    //todo goto????? Consider throw & catch
    for (const auto &element : program_body) {
        (element.second).parsed_representation->execute(state);
    }
}

void Program::print_list() {
    for (const auto &element : program_body) {
        cout << (element.second).original_source_line << endl;
    }
}
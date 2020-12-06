/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/simpio.h"

using namespace std;

/* Implementation of the ControlStatement class */

ControlStatement::ControlStatement(int msg_) {
    msg=msg_;
}

int ControlStatement::getMessage() {
    return msg;
}

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}


rem_statement::rem_statement() {

}

rem_statement::~rem_statement() {

}

void rem_statement::execute(EvalState &state) {

}


let_statement::let_statement(Expression *exp_) {
    exp = exp_;
}

let_statement::~let_statement() {
    delete exp;
}

void let_statement::execute(EvalState &state) {
    exp->eval(state);
}


print_statement::print_statement(Expression *exp_) {
    exp = exp_;
}

print_statement::~print_statement() {
    delete exp;
}

void print_statement::execute(EvalState &state) {
    int value=exp->eval(state);
    cout<<value<<endl;
}


input_statement::input_statement(string var_) {
    var = var_;
}

input_statement::~input_statement() {

}

void input_statement::execute(EvalState &state) {
    string value_str = getLine("?");
    int value = stringToInteger(value_str);
    state.setValue(var, value);
}


end_statement::end_statement() {

}

end_statement::~end_statement() {

}

void end_statement::execute(EvalState &state) {
    throw ControlStatement(-1);
}


goto_statement::goto_statement(int n_) {
    n = n_;
}

goto_statement::~goto_statement() {

}

void goto_statement::execute(EvalState &state) {
    throw ControlStatement(n);
}


if_statement::if_statement() {

}

if_statement::~if_statement() {

}

void if_statement::execute(EvalState &state) {

}
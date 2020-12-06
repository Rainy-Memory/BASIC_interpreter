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

using namespace std;

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


let_statement::let_statement(Expression* exp_) {
    exp=exp_;
}

let_statement::~let_statement() {
    delete exp;
}

void let_statement::execute(EvalState &state) {

}


print_statement::print_statement(Expression* exp_) {
    exp=exp_;
}

print_statement::~print_statement() {
    delete exp;
}

void print_statement::execute(EvalState &state) {

}


input_statement::input_statement(string var_) {

}

input_statement::~input_statement() {

}

void input_statement::execute(EvalState &state) {

}


end_statement::end_statement() {

}

end_statement::~end_statement() {

}

void end_statement::execute(EvalState &state) {

}


goto_statement::goto_statement() {

}

goto_statement::~goto_statement() {

}

void goto_statement::execute(EvalState &state) {

}


if_statement::if_statement() {

}

if_statement::~if_statement() {

}

void if_statement::execute(EvalState &state) {

}
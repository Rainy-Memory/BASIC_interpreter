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

/* Implementation of the ControlStatement class */

ControlStatement::ControlStatement(int msg_) {
    msg = msg_;
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
    int value = exp->eval(state);
    cout << value << endl;
}


input_statement::input_statement(string var_) {
    var = var_;
}

input_statement::~input_statement() {

}

void input_statement::execute(EvalState &state) {
    string value_str;
    int value;
    while(true){
        try{
            value_str = getLine(" ? ");
            value = stringToInteger(value_str);
        } catch (...) {
            cout<<"INVALID NUMBER"<<endl;
            continue;
        }
        break;
    }
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


if_statement::if_statement(string line_) {
    int op_pos = -1;
    for (int i = 0; i < line_.size(); i++) {
        if (line_[i] == '<' || line_[i] == '=' || line_[i] == '>') {
            op_pos = i;
            break;
        }
    }
    if (op_pos == -1)throw ErrorException("SYNTAX ERROR");
    string left, right;
    for (int i = 0; i < line_.size(); i++) {
        (i < op_pos ? left : right) += line_[i];
    }
    TokenScanner scanner_;
    scanner_.ignoreWhitespace();
    scanner_.scanNumbers();
    scanner_.setInput(left);
    string n_str = scanner_.nextToken();
    n_str = scanner_.nextToken();
    lhs = readE(scanner_);
    scanner_.setInput(right);
    op = scanner_.nextToken();
    if (op != "<" && op != ">" && op != "=")throw ErrorException("SYNTAX ERROR");
    rhs = readE(scanner_);
    n_str = scanner_.nextToken();
    n_str = scanner_.nextToken();
    n = stringToInteger(n_str);
}

if_statement::~if_statement() {
    delete lhs;
    delete rhs;
}

void if_statement::execute(EvalState &state) {
    lhs_value = lhs->eval(state);
    rhs_value = rhs->eval(state);
    bool cmp = judge();
    if (cmp)throw ControlStatement(n);
}

bool if_statement::judge() {
    if (op == ">")return lhs_value > rhs_value;
    else if (op == "<")return lhs_value < rhs_value;
    else if (op == "=")return lhs_value == rhs_value;
    else throw ErrorException("SYNTAX ERROR");
}
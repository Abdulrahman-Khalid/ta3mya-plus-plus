#include "expressions.h"

void Literal::compile(CompileContext & compile_context ) const {
    // TODO
}

string Literal::toString() const {
    return "Literal: " + this->literal;
}

void SymbolExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string SymbolExpression::toString() const {
    return "Symbol: " + this->symbol;
}

void BinaryExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string BinaryExpression::toString() const {
    string s = "Sa7e7Expression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s ;
}

void BoolExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string BoolExpression::toString() const {
    string s = "BoolExpression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s;
}

void NegExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string NegExpression::toString() const {
    string s = "NegExpression{";
    s += toBeNegated->toString() + "}";
    return s;
}

void MshExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string MshExpression::toString() const {
    string s = "MshExpression{";
    s += toBeNegated->toString() + "}";
    return s;
}

void CallDallahExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string CallDallahExpression::toString() const {
    string argsString;
    for (int i = 0; i < _args.size(); i++) {
        if (i+1 == _args.size()) {
            argsString += _args[i]->toString();
        } else {
            argsString += _args[i]->toString() + ",";
        }
    }

    return "CallDallahExpression{name: "+_name+", args: [" + argsString +  "]}";
}

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

void IntExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string IntExpression::toString() const {
    string s = "Sa7e7Expression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s ;
}

void RealExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string RealExpression::toString() const {
    string s = "7a2i2iExpression{";
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

void ToSa7e7::compile(CompileContext & compile_context ) const {
    // TODO
}

string ToSa7e7::toString() const {
    string s = "ToSa7e7{";
    s += toBeConverted->toString() + "}";
    return s;
}

void To7a2i2i::compile(CompileContext & compile_context ) const {
    // TODO
}

string To7a2i2i::toString() const {
    string s = "To7a2i2i{";
    s += toBeConverted->toString() + "}";
    return s;
}

void SalbS7e7::compile(CompileContext & compile_context ) const {
    // TODO
}

string SalbS7e7::toString() const {
    string s = "SalbS7e7{";
    s += toBeNegated->toString() + "}";
    return s;
}

void Salb7a2i2i::compile(CompileContext & compile_context ) const {
    // TODO
}

string Salb7a2i2i::toString() const {
    string s = "Salb7a2i2i{";
    s += toBeNegated->toString() + "}";
    return s;
}

void Msh::compile(CompileContext & compile_context ) const {
    // TODO
}

string Msh::toString() const {
    string s = "Msh{";
    s += toBeNegated->toString() + "}";
    return s;
}

void CallDallahExpression::compile(CompileContext & compile_context ) const {
    // TODO
}

string CallDallahExpression::toString() const {
    return "CallDallahExpression";
}

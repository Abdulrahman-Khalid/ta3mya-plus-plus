#include "expressions.h"

Program Literal::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Literal::toString() const {
    return "Literal: " + this->literal;
}

Program Symbol::compile() const {
    // TODO
    return Program();
}

string Symbol::toString() const {
    return "Symbol: " + this->symbol;
}

Program IntExpression::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string IntExpression::toString() const {
    string s = "Sa7e7Expression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s ;
}

Program RealExpression::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string RealExpression::toString() const {
    string s = "7a2i2iExpression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s ;
}

Program BoolExpression::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string BoolExpression::toString() const {
    string s = "BoolExpression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s;
}

Program ToSa7e7::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string ToSa7e7::toString() const {
    string s = "ToSa7e7{";
    s += toBeConverted->toString() + "}";
    return s;
}

Program To7a2i2i::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string To7a2i2i::toString() const {
    string s = "To7a2i2i{";
    s += toBeConverted->toString() + "}";
    return s;
}

Program SalbS7e7::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string SalbS7e7::toString() const {
    string s = "SalbS7e7{";
    s += toBeNegated->toString() + "}";
    return s;
}

Program Salb7a2i2i::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Salb7a2i2i::toString() const {
    string s = "Salb7a2i2i{";
    s += toBeNegated->toString() + "}";
    return s;
}

Program Msh::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Msh::toString() const {
    string s = "Msh{";
    s += toBeNegated->toString() + "}";
    return s;
}

Program CallDallahExpression::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string CallDallahExpression::toString() const {
    return "CallDallahExpression";
}

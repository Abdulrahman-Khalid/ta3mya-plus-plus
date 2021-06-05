#pragma once
#include "node.h"

using std::string;

class Expression : public Node {};

class Literal : public Expression {
public:
    string literal;
    Literal(string literal) : 
        literal(literal) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};


class SymbolExpression : public Expression {
public:
    string symbol;
    SymbolExpression(string symbol) : 
        symbol(symbol) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class IntExpression : public Expression {
public:
    Expression* lhs;
    Expression* rhs;
    string operation;
    IntExpression(Expression* lhs, string operation, Expression* rhs) : 
        lhs(lhs), rhs(rhs), operation(operation) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class RealExpression : public Expression {
public:
    Expression* lhs;
    Expression* rhs;
    string operation;
    RealExpression(Expression* lhs, string operation, Expression* rhs) : 
        lhs(lhs), rhs(rhs), operation(operation) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class BoolExpression : public Expression {
public:
    Expression* lhs;
    Expression* rhs;
    string operation;
    BoolExpression(Expression*  lhs, string operation, Expression* rhs) : 
        lhs(lhs), rhs(rhs), operation(operation) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class ToSa7e7 : public Expression {
public:
    Expression* toBeConverted;
    ToSa7e7(Expression*  toBeConverted) : 
        toBeConverted(toBeConverted) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class To7a2i2i : public Expression {
public:
    Expression* toBeConverted;
    To7a2i2i(Expression*  toBeConverted) : 
        toBeConverted(toBeConverted) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class SalbS7e7 : public Expression {
public:
    Expression* toBeNegated;
    SalbS7e7(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class Salb7a2i2i : public Expression {
public:
    Expression* toBeNegated;
    Salb7a2i2i(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class Msh : public Expression {
public:
    Expression* toBeNegated;
    Msh(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class CallDallahExpression : public Expression {
public:
    virtual Program compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

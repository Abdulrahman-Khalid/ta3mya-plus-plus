#pragma once
#include "node.h"

using std::string;

class Expression : public Node {};

class Literal : public Expression {
public:
    string literal;
    Literal(string literal) : 
        literal(literal) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class SymbolExpression : public Expression {
public:
    string symbol;
    SymbolExpression(string symbol) : 
        symbol(symbol) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class BinaryExpression : public Expression {
public:
    Expression* lhs;
    Expression* rhs;
    string operation;
    BinaryExpression(Expression* lhs, string operation, Expression* rhs) : 
        lhs(lhs), rhs(rhs), operation(operation) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class BoolExpression : public Expression {
public:
    Expression* lhs;
    Expression* rhs;
    string operation;
    BoolExpression(Expression*  lhs, string operation, Expression* rhs) : 
        lhs(lhs), rhs(rhs), operation(operation) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class NegExpression : public Expression {
public:
    Expression* toBeNegated;
    NegExpression(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class MshExpression : public Expression {
public:
    Expression* toBeNegated;
    MshExpression(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class CallDallahExpression : public Expression {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

#pragma once
#include "node.h"
#include "type.h"

using std::string;

class Expression : public Node {};

class Literal : public Expression {
public:
    string literal;
    inline Literal(string literal) : 
        literal(literal) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class SymbolExpression : public Expression {
public:
    string symbol;
    inline SymbolExpression(string symbol) : 
        symbol(symbol) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class BinaryExpression : public Expression {
public:
    Expression* lhs;
    Expression* rhs;
    string operation;
    inline BinaryExpression(Expression* lhs, string operation, Expression* rhs) : 
        lhs(lhs), rhs(rhs), operation(operation) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class NegExpression : public Expression {
public:
    Expression* toBeNegated;
    inline NegExpression(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class MshExpression : public Expression {
public:
    Expression* toBeNegated;
    inline MshExpression(Expression*  toBeNegated) : 
        toBeNegated(toBeNegated) { }
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class ToSa7e7Expression : public Expression {
    Expression* _exp;
public:
    inline ToSa7e7Expression(Expression*  exp): _exp(exp) { }

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class To7a2i2iExpression : public Expression {
    Expression* _exp;
public:
    inline To7a2i2iExpression(Expression*  exp): _exp(exp) { }

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

typedef std::vector<Expression*> CallDallahArgs;

class CallDallahExpression : public Expression {
    string _name;
    CallDallahArgs _args;
    
public:
    inline CallDallahExpression(string dallahName, CallDallahArgs args):_name(dallahName), _args(args) {}

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

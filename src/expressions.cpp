#include "expressions.h"

void LiteralExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string LiteralExpression::toString() const {
    return "LiteralExpression: " + this->literal;
}

void SymbolExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string SymbolExpression::toString() const {
    return "Symbol: " + this->symbol;
}

void TarqeemInstanceExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string TarqeemInstanceExpression::toString() const {
    return "TarqeemInstance: " + _instance;
}

void BinaryExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string BinaryExpression::toString() const {
    string s = "BinaryExpression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s ;
}

void NegExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string NegExpression::toString() const {
    string s = "NegExpression{";
    s += toBeNegated->toString() + "}";
    return s;
}

void ToSa7e7Expression::compile(CompileContext& compile_context) const {
    // TODO
}

string ToSa7e7Expression::toString() const {
    string s = "ToSa7e7Expression{";
    s += _exp->toString() + "}";
    return s;
}

void To7a2i2iExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string To7a2i2iExpression::toString() const {
    string s = "To7a2i2iExpression{";
    s += _exp->toString() + "}";
    return s;
}

void MshExpression::compile(CompileContext& compile_context) const {
    // TODO
}

string MshExpression::toString() const {
    string s = "MshExpression{";
    s += toBeNegated->toString() + "}";
    return s;
}

void CallDallahExpression::compile(CompileContext& compile_context) const {
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

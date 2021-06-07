#include "expressions.h"

Result LiteralExpression::compile(CompileContext& compile_context) const {
    return Result {out: literal };
}

string LiteralExpression::toString() const {
    return "LiteralExpression: ("+ typeToString(type) + ") " + this->literal;
}

Result SymbolExpression::compile(CompileContext& compile_context) const {
    // error if symbol doesn't exist
    return {};
}

string SymbolExpression::toString() const {
    return "Symbol: " + this->symbol;
}

Result TarqeemInstanceExpression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string TarqeemInstanceExpression::toString() const {
    return "TarqeemInstance: " + _instance;
}

Result BinaryExpression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BinaryExpression::toString() const {
    string s = "BinaryExpression{";
    s += lhs->toString() + "";
    s += " " +  operation + " ";
    s += rhs->toString() + "}";
    return s ;
}

Result NegExpression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string NegExpression::toString() const {
    string s = "NegExpression{";
    s += toBeNegated->toString() + "}";
    return s;
}

Result ToSa7e7Expression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string ToSa7e7Expression::toString() const {
    string s = "ToSa7e7Expression{";
    s += _exp->toString() + "}";
    return s;
}

Result To7a2i2iExpression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string To7a2i2iExpression::toString() const {
    string s = "To7a2i2iExpression{";
    s += _exp->toString() + "}";
    return s;
}

Result MshExpression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string MshExpression::toString() const {
    string s = "MshExpression{";
    s += toBeNegated->toString() + "}";
    return s;
}

Result CallDallahExpression::compile(CompileContext& compile_context) const {
    // TODO
    return {};
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

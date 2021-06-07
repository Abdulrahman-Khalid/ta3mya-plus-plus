#include "error_registry.h"
#include <bits/stdc++.h>

#define EMPTY(s) (s.find_first_not_of(" \n\t") == std::string::npos)

string generatePrefix(int line_number = 0) {
    if (line_number == 0) {
        return "ERROR: ";
    } else {
        return "ERROR (near line " + to_string(line_number) + "): ";
    }
}

void ErrorRegistry::syntaxError(string msg, int line_number, string symbol) {
    string prefix = generatePrefix(line_number);
    if(!EMPTY(symbol)) {
        msg.append(" at symbol \"" + symbol + "\"");
    }
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::redeclaredSymbol(string symbol, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Multiple declaration of \"" + symbol + "\"";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::undeclaredSymbol(string symbol, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Undeclared symbol \"" + symbol + "\"";
    errors.push_back({ prefix + msg });
}   

void ErrorRegistry::uninitializedVariable(string symbol, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Variable \"" + symbol + "\" used without being initialized";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidExpressionType(Type expected, Type actual, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Invalid expression type, expected to be " + typeToString(expected)
        + ", but was found to be " + typeToString(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::unusedSymbol(string symbol) {
    string prefix = generatePrefix();
    string msg = "\"" + symbol + "\" defined but not used";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::nonDataSymbol(string symbol, string otherType, int line_number) {
    string prefix = generatePrefix();
    string msg = "\"" + symbol + "\" was expected to be a var/const but it's " + otherType;
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::constantAssignment(string symbol, int line_number) {
    string prefix = generatePrefix();
    string msg = "\"" + symbol + "\" is a constant, it cannot be assigned";
    errors.push_back({ prefix + msg });
}

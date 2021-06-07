#include "error_registry.h"
#include <bits/stdc++.h>

#define EMPTY(s) (s.find_first_not_of(" \n\t") == std::string::npos)

string generatePrefix(int line_number = -1) {
    if (line_number == -1) {
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

void ErrorRegistry::invalidExpressionType(vector<Type> expected, Type actual, int line_number) {
    assert(expected.size() > 0);
    string prefix = generatePrefix(line_number);
    string msg = "Invalid expression type, expected to be " + typeToString(expected[0]);
    for(int i = 1; i < expected.size(); i++) {
        msg += ", or " + typeToString(expected[i]);
    }
    msg += ", but was found to be " + typeToString(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::unusedSymbol(string symbol) {
    string prefix = generatePrefix();
    string msg = "\"" + symbol + "\" defined but not used";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::nonDataSymbol(string symbol, string otherType, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "\"" + symbol + "\" was expected to be a var/const but it's " + otherType;
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::constantAssignment(string symbol, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "\"" + symbol + "\" is a constant, it cannot be reassigned";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidReturn(int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Can't use basy statement outside function definitions";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::incorrectArgsCount(string function_name, int expected, int actual, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Incorrect number of parameters for function call of \"" + function_name + "\""
        + " expected to be " + to_string(expected)
        + ", but was found to be " + to_string(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::incorrectArgType(string function_name, string arg_name, Type expected, Type actual, int line_number) {
    string prefix = generatePrefix(line_number);
    string msg = "Incorrect parameter type for parameter \"" + arg_name + "\"" 
        + " in function call of \"" + function_name + "\"" 
        + " expected to be " + typeToString(expected)
        + ", but was found to be " + typeToString(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidEnumInstance(string instance, int line_number) {
    string prefix = generatePrefix(line_number);
    auto separatorLocation = instance.find("::");
    string intendedEnum = instance.substr(0, separatorLocation);
    string instanceName = instance.substr(separatorLocation + 2, string::npos);
    string msg = "Invalid enum instance, \"" + instanceName + "\" does not belong to \""
        + intendedEnum + "\"";
    errors.push_back({ prefix + msg });
}

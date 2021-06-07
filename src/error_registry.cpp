#include "error_registry.h"
#include <bits/stdc++.h>

#define EMPTY(s) (s.find_first_not_of(" \n\t") == std::string::npos)

string generatePrefix(string type, int line_number = -1) {
    if (line_number == -1) {
        return type + ": ";
    } else {
        return type + " (near line " + to_string(line_number) + "): ";
    }
}

string generateErrorPrefix(int line_number = -1) {
    return generatePrefix("Error", line_number);
}

string generateWarningPrefix(int line_number = -1) {
    return generatePrefix("Warning", line_number);
}

void ErrorRegistry::syntaxError(string msg, int line_number, string symbol) {
    string prefix = generateErrorPrefix(line_number);
    if(!EMPTY(symbol)) {
        msg.append(" at symbol \"" + symbol + "\"");
    }
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::redeclaredSymbol(string symbol, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Multiple declaration of \"" + symbol + "\"";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::undeclaredSymbol(string symbol, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Undeclared symbol \"" + symbol + "\"";
    errors.push_back({ prefix + msg });
}   

void ErrorRegistry::uninitializedVariable(string symbol, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Variable \"" + symbol + "\" used without being initialized";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidExpressionType(Type expected, Type actual, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Invalid expression type, expected to be " + typeToString(expected)
        + ", but was found to be " + typeToString(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidExpressionType(vector<Type> expected, Type actual, int line_number) {
    assert(expected.size() > 0);
    string prefix = generateErrorPrefix(line_number);
    string msg = "Invalid expression type, expected to be " + typeToString(expected[0]);
    for(int i = 1; i < expected.size(); i++) {
        msg += ", or " + typeToString(expected[i]);
    }
    msg += ", but was found to be " + typeToString(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::nonDataSymbol(string symbol, string otherType, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "\"" + symbol + "\" was expected to be a var/const but it's " + otherType;
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::constantAssignment(string symbol, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "\"" + symbol + "\" is a constant, it cannot be reassigned";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidReturn(int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Can't use basy statement outside function definitions";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::incorrectArgsCount(string function_name, int expected, int actual, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Incorrect number of parameters for function call of \"" + function_name + "\""
        + " expected to be " + to_string(expected)
        + ", but was found to be " + to_string(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::incorrectArgType(string function_name, string arg_name, Type expected, Type actual, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    string msg = "Incorrect parameter type for parameter \"" + arg_name + "\"" 
        + " in function call of \"" + function_name + "\"" 
        + " expected to be " + typeToString(expected)
        + ", but was found to be " + typeToString(actual);
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::invalidEnumInstance(string instance, int line_number) {
    string prefix = generateErrorPrefix(line_number);
    auto separatorLocation = instance.find("::");
    string intendedEnum = instance.substr(0, separatorLocation);
    string instanceName = instance.substr(separatorLocation + 2, string::npos);
    string msg = "Invalid enum instance, \"" + instanceName + "\" does not belong to \""
        + intendedEnum + "\"";
    errors.push_back({ prefix + msg });
}

void WarningRegistry::unusedSymbol(string symbol, int line_number) {
    string prefix = generateWarningPrefix(line_number);
    string msg = "\"" + symbol + "\" declared but not used";
    warnings.push_back({ prefix + msg });
}
void ErrorRegistry::noBedayah() {
    string prefix = generateErrorPrefix();
    string msg = "Didn't find bedayah function in file!";
    errors.push_back({ prefix + msg });
}

void ErrorRegistry::bedayahHasAnonFuncType(string actual) {
    string prefix = generateErrorPrefix();
    string msg = "bedayah function symbol is used as a name for other type, found type: " + actual;
    errors.push_back({ prefix + msg });
}

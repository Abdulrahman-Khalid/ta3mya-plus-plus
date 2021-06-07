#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "type.h"

using namespace std;

struct Error {
	string msg;
    inline void display() const { cerr << msg << endl; }
};

struct Warning {
	string msg;
    inline void display() const { cerr << msg << endl; }
};

class ErrorRegistry {
private:
    vector<Error> errors;
public:
    void syntaxError(string msg, int line_number, string symbol = "");
    void redeclaredSymbol(string symbol, int line_number);
    void undeclaredSymbol(string symbol, int line_number);
    void uninitializedVariable(string symbol, int line_number);
    void invalidExpressionType(Type expected, Type actual, int line_number);
    void invalidExpressionType(vector<Type> expected, Type actual, int line_number);
    void nonDataSymbol(string symbol, string otherType, int line_number);
    void constantAssignment(string symbol, int line_number);
    void invalidReturn(int line_number);
    void incorrectArgsCount(string function_name, int expected, int actual, int line_number);
    void incorrectArgType(string function_name, string arg_name, Type expected, Type actual, int line_number);
    void invalidEnumInstance(string instance, int line_number);
    void noBedayah();
    void bedayahHasAnonFuncType(string actual);

    inline bool empty() const { return errors.empty(); }
    inline void displayErrors() const { for(auto error : errors) error.display(); }
};

class WarningRegistry {
private:
    vector<Warning> warnings;
public:
    void unusedSymbol(string symbol, int line_number);

    inline bool empty() const { return warnings.empty(); }
    inline void displayWarnings() const { for(auto warning : warnings) warning.display(); }
};
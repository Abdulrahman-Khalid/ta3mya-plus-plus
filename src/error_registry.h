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

class ErrorRegistry {
private:
    vector<Error> errors;
public:
    void syntaxError(string msg, int line_number = 0, string symbol = "");
    void redeclaredSymbol(string symbol, int line_number = 0);
    void undeclaredSymbol(string symbol, int line_number = 0);
    void uninitializedVariable(string symbol, int line_number = 0); 
    void invalidExpressionType(Type expected, Type actual, int line_number = 0);
    void nonDataSymbol(string symbol, string otherType, int line_number = 0);
    void constantAssignment(string symbol, int line_number = 0);
    void unusedSymbol(string symbol);

    inline bool empty() const { return errors.empty(); }
    inline void displayErrors() const { for(auto error : errors) error.display(); }
};
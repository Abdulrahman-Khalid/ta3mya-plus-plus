#pragma once

#include <cstdint>
#include <string>


enum Operator : uint8_t {
    PLUS, NEG, MULT, DIV, MODULO, EXPONENT, 
    WE, AW, DOESNT_EQUAL, EQUALS, GREATER, 
    GREATER_EQUAL, LESS, LESS_EQUAL,
};

using std::string;
const string _operatorToString[] = {
    "we", "aw","!=","==",">",">=","<","<=","+","-","*","/","%","**",
};

inline string operatorToString(Operator op) {
    return _operatorToString[int(op)];
}

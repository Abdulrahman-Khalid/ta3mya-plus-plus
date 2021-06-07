#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include "quadraples.h"

using std::vector;

enum class Operator : uint8_t
{
    PLUS,
    NEG,
    MULT,
    DIV,
    MODULO,
    EXPONENT,
    WE,
    AW,
    DOESNT_EQUAL,
    EQUALS,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
};

using std::string;
const string _operatorToString[] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "**",
    "we",
    "aw",
    "!=",
    "==",
    ">",
    ">=",
    "<",
    "<=",
};

inline string operatorToString(Operator op)
{
    return _operatorToString[int(op)];
}

const vector<Operator> NumericalOperators = {Operator::PLUS, Operator::NEG, Operator::MULT, Operator::DIV, Operator::MODULO, Operator::EXPONENT};
inline bool isNumericalOperator(Operator op)
{
    return std::find(NumericalOperators.begin(), NumericalOperators.end(), op) !=
           NumericalOperators.end();
}

const vector<Operator> Comparators = {Operator::DOESNT_EQUAL, Operator::EQUALS, Operator::GREATER,
                                      Operator::GREATER_EQUAL, Operator::LESS, Operator::LESS_EQUAL};
inline bool isComparator(Operator op)
{
    return std::find(Comparators.begin(), Comparators.end(), op) != Comparators.end();
}

const vector<Operator> Combiners = {Operator::WE, Operator::AW};
inline bool isCombiner(Operator op)
{
    return std::find(Combiners.begin(), Combiners.end(), op) != Combiners.end();
}

const vector<Opcode> orderedOpcodes = {Opcode::ADD, Opcode::SUB, Opcode::MUL,
                                       Opcode::DIV, Opcode::MOD, Opcode::POW,
                                       Opcode::AND, Opcode::OR, Opcode::NEQ, Opcode::EQ,
                                       Opcode::GT, Opcode::GTE, Opcode::LT, Opcode::LTE};

inline Opcode operatorToOpcode(Operator op)
{
    return orderedOpcodes[int(op)];
}

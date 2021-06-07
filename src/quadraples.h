#pragma once

#include <vector>
#include <string>
#include <cassert>

#include "optional.h"

enum class Opcode: uint8_t {
    CPY = 0, INT, ADD, MUL, DIV, MOD, NEG, POW, REAL, 
    RADD, RMUL, RDIV, RMOD, RNEG, RPOW, CALL, RTN, JMP, 
    JZ, JNZ, GT, LT, GTE, LTE, AND, OR, NOT, NOP,
};

const std::string _opcodeToString[] = {
    "CPY", "INT", "ADD", "MUL", "DIV", "MOD", "NEG", "POW", "REAL", 
    "RADD", "RMUL", "RDIV", "RMOD", "RNEG", "RPOW", "CALL", "RTN", "JMP", 
    "JZ", "JNZ", "GT", "LT", "GTE", "LTE", "AND", "OR", "NOT", "NOP",
};
inline std::string opcodeToString(Opcode opcode) {
    return _opcodeToString[int(opcode)];
}

struct Quadruple {
    Opcode opcode;
    std::string arg1, arg2, result;
    Optional<std::string> label;

    inline std::string toString() const {
        std::string labelStr = label? (*label + ":\n") : "";

        std::string args = " ";
        for (const auto& arg : {arg1, arg2, result}) {
            if (arg.size() > 0) {
                args += arg + " ";
            }
        }

        return labelStr + opcodeToString(opcode) + args;
    }
};

typedef std::vector<Quadruple> QuadruplesTable;

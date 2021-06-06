#pragma once

#include <vector>
#include <string>

enum class Opcode: uint8_t {
    CPY = 0, INT, ADD, MUL, DIV, MOD, NEG, POW, REAL, 
    RADD, RMUL, RDIV, RMOD, RNEG, RPOW, RTN, JMP, 
    JMPZ, GT, LT, GTE, LTE, AND, OR,
};

const std::string opcodeToString[] = {
    "CPY", "INT", "ADD", "MUL", "DIV", "MOD", "NEG", "POW", "REAL", 
    "RADD", "RMUL", "RDIV", "RMOD", "RNEG", "RPOW", "RTN", "JMP", 
    "JMPZ", "GT", "LT", "GTE", "LTE", "AND", "OR",
};

struct Quadruple {
    Opcode opcode;
    std::string arg1, arg2, result;

    inline std::string toString() const {
        std::string args = " ";
        for (const auto& arg : {arg1, arg2, result}) {
            if (arg.size() > 0) {
                args += arg + " ";
            }
        }

        return opcodeToString[int(opcode)] + args;
    }
};

typedef std::vector<Quadruple> QuadruplesTable;

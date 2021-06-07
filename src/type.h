#pragma once
#include <string>

using std::string;

enum class Type: uint8_t {
    INT, REAL, ENUM, BOOLEAN
};

using std::string;
const string _typeToString[] = {
    "int", "real","enum","bool",
};

inline string typeToString(Type type) {
    return _typeToString[int(type)];
}

inline bool isNumerical(Type type) {
    return type == Type::INT || type == Type::REAL;
}

#pragma once
#include <string>

using std::string;

enum class Type: uint8_t {
    INT, REAL, BOOLEAN
};

using std::string;
const string _typeToString[] = {
    "sa7e7", "7a2i2i","tarqeem","bool",
};

inline string typeToString(Type type) {
    return _typeToString[int(type)];
}

inline bool isNumericalType(Type type) {
    return type == Type::INT || type == Type::REAL;
}

inline bool isBooleanType(Type type) {
    return type == Type::BOOLEAN;
}

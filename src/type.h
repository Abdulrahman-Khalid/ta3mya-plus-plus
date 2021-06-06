#pragma once
#include <string>

using std::string;

enum class Type: uint8_t {
    INT, REAL, ENUM
};

inline string typeToString(Type type) {
    return type == Type::INT ? "int" : type == Type::REAL ? "real" : "enum";
}

#pragma once
#include <string>

using std::string;

enum class Type {
    INT, REAL
};

inline string typeToString(Type type) {
    return type == Type::INT ? "int" : "real";
}

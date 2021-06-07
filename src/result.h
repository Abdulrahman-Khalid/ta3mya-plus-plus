#include <string>

#include "optional.h"

struct Result {
    // out is the name of the variable the holds the expression result
    // it could be a literal to be used directly
    Optional<std::string> out;
};

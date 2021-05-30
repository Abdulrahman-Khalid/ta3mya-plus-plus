#include "program.h"

using std::string;

class Node {
public:
    virtual Program compile() const = 0;

    // toString returns a string representation 
    // of the object for debugging
    virtual string toString() const = 0;
};

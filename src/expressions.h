#include "program.h"

using std::string;

class Expression {
public:
    virtual Program compile() const = 0;

    // toString returns a string representation 
    // of the object for debugging
    virtual string toString() const = 0;
};

class IntExpression : public Expression {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class RealExpression : public Expression {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class BoolExpression : public Expression {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

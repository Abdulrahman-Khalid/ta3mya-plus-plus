#include "program.h"

class Expression {
public:
    virtual Program compile() const = 0;
};

class IntExpression : public Expression {
public:
    virtual Program compile() const override;
};

class RealExpression : public Expression {
public:
    virtual Program compile() const override;
};

class BoolExpression : public Expression {
public:
    virtual Program compile() const override;
};

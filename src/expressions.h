#include "node.h"

class Expression : public Node {
public:
    Expression() = delete;
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

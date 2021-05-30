#include "node.h"

class Expression : public Node {};

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

class CallDallahExpression : public Expression {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

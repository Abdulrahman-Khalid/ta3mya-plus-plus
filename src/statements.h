#include "node.h"

class Statement : public Node {};

class BlockStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class ProgramNode : public Node {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class BasyStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class LWGroupStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class KarrarL7dStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class Ta3reefMota8ierStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class Ta3reefThabetStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class Ta3reefDallahStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class Ta3reefTarqeemStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class AssignmentStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class Fe7aletStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

class LefStatement : public Statement {
public:
    virtual Program compile() const override;
    virtual string toString() const override;
};

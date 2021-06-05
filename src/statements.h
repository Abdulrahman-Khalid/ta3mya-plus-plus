#pragma once
#include "node.h"
#include "expressions.h"

class Statement : public Node {};

class ProgramNode : public Node {
private:
    std::vector<Statement*> _stmts;

public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;

    inline void addStatement(Statement* stmt) {
        _stmts.push_back(stmt);
    }
};

class BlockStatement : public Statement {
private:
    ProgramNode* _programNode;
public:
    inline BlockStatement(ProgramNode* programNode):_programNode(programNode) {}

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class BasyStatement : public Statement {
private:
    Expression* _toBasy;
public:
    inline BasyStatement(Expression* toBasy):_toBasy(toBasy) {}

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class LWGroupStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class KarrarL7dStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class Ta3reefMota8ierStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class Ta3reefThabetStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class Ta3reefDallahStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

typedef std::vector<std::string> TarqeemList;

class Ta3reefTarqeemStatement : public Statement {
    std::string _name;
    TarqeemList _list;
public:
    inline Ta3reefTarqeemStatement(std::string name, TarqeemList list): _name(name), _list(list) {}
    
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class AssignmentStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class Fe7aletStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class LefStatement : public Statement {
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

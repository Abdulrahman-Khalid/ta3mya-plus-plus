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

    inline void addStatement(Statement* stmt) {
        _programNode->addStatement(stmt);
    }
};

class BasyStatement : public Statement {
private:
    Expression* _toBasy;
public:
    inline BasyStatement(Expression* toBasy):_toBasy(toBasy) {}

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class LwStatement : public Statement {
private:
    struct ConditionalBlock {
        Expression* condition;
        BlockStatement* block;
    };
    vector<ConditionalBlock> _conditionalBlocks;
public:
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;

    inline void addConditionalBlock(Expression* condition, BlockStatement* block) {
        _conditionalBlocks.push_back({ condition, block });
    }
};

class LwGroupStatement : public Statement {
private:
    LwStatement* _lwStatement;
    BlockStatement* _8eroBlock;
public:
    inline LwGroupStatement(LwStatement* lwStatement) :
        _lwStatement(lwStatement), _8eroBlock(nullptr) {}
    inline LwGroupStatement(LwStatement* lwStatement, BlockStatement* __8eroBlock) :
        _lwStatement(lwStatement), _8eroBlock(__8eroBlock) {}

    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class KarrarL7dStatement : public Statement {
private:
    Expression* _condition;
    BlockStatement* _block;
public:
    inline KarrarL7dStatement(Expression* condition, BlockStatement* block) :
        _condition(condition), _block(block) {}
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

class TalmaStatement : public Statement {
private:
    Expression* _condition;
    BlockStatement* _block;
public:
    inline TalmaStatement(Expression* condition, BlockStatement* block) :
        _condition(condition), _block(block) {}
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

class LefStatement : public Statement {
private:
    Statement* _init;
    TalmaStatement* _talmaStmt;
public:
    LefStatement(Statement* init, Expression* condition, Statement* b3dKolLaffa, BlockStatement* block);
    virtual void compile(CompileContext & compile_context ) const override;
    virtual string toString() const override;
};

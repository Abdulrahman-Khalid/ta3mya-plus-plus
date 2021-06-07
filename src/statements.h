#pragma once
#include "node.h"
#include "expressions.h"

class Statement : public Node
{
};

class ProgramNode : public Node
{
private:
    std::vector<Statement *> _stmts;

public:
    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;

    inline void appendStatement(Statement *stmt)
    {
        _stmts.push_back(stmt);
    }

    inline void prependStatement(Statement *stmt)
    {
        _stmts.insert(_stmts.begin(), stmt);
    }
};

class BlockStatement : public Statement
{
private:
    ProgramNode *_programNode;

public:
    inline BlockStatement(ProgramNode *programNode) : _programNode(programNode) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;

    inline void appendStatement(Statement *stmt)
    {
        _programNode->appendStatement(stmt);
    }

    inline void prependStatement(Statement *stmt)
    {
        _programNode->prependStatement(stmt);
    }
};

class BasyStatement : public Statement
{
private:
    Expression *_toBasy;

public:
    inline BasyStatement(Expression *toBasy) : _toBasy(toBasy) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

class LwStatement : public Statement
{
protected:
    struct ConditionalBlock
    {
        Expression *condition;
        BlockStatement *block;
    };
    vector<ConditionalBlock> _conditionalBlocks;
    BlockStatement *_8eroBlock;

public:
    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;

    inline void addConditionalBlock(Expression *condition, BlockStatement *block)
    {
        _conditionalBlocks.push_back({condition, block});
    }

    inline void add8eroBlock(BlockStatement *block)
    {
        _8eroBlock = block;
    }
};

class HaletStatement : public LwStatement
{
public:
    void attachSymbol(SymbolExpression *symbol);
};

class KarrarL7dStatement : public Statement
{
private:
    Expression *_condition;
    BlockStatement *_block;

public:
    inline KarrarL7dStatement(Expression *condition, BlockStatement *block) : _condition(condition), _block(block) {}
    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

class TalmaStatement : public Statement
{
private:
    Expression *_condition;
    BlockStatement *_block;

public:
    inline TalmaStatement(Expression *condition, BlockStatement *block) : _condition(condition), _block(block) {}
    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

class AssignmentStatement : public Statement
{
private:
    std::string _symbol;
    Expression *_exp;

public:
    inline AssignmentStatement(std::string symbol, Expression *exp) : _symbol(symbol), _exp(exp) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

class Ta3reefMota8ierStatement : public Statement
{
private:
    Type _type;
    std::string _symbol;
    AssignmentStatement *_assignment;

public:
    inline Ta3reefMota8ierStatement(Type type, std::string symbol, Expression *init = nullptr) : _type(type), _symbol(symbol),
                                                                                                 _assignment(init ? new AssignmentStatement(_symbol, init) : nullptr) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
    inline FuncSymbol::Arg getAsArg() {
        return {_type, _symbol};
    } 
};

class Ta3reefThabetStatement : public Statement
{
private:
    Type _type;
    std::string _symbol;
    Expression *_init;

public:
    inline Ta3reefThabetStatement(Type type, std::string symbol, Expression *init) : _type(type), _symbol(symbol), _init(init) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

typedef vector<Ta3reefMota8ierStatement *> ArgsDeclarationsList;

class Ta3reefDallahStatement : public Statement
{
private:
    Type _type;
    std::string _name;
    ArgsDeclarationsList *_args;
    BlockStatement *_block;

public:
    inline Ta3reefDallahStatement(Type type, std::string name, ArgsDeclarationsList *args,
                                  BlockStatement *block) : _type(type), _name(name), _args(args), _block(block) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

typedef std::vector<std::string> TarqeemList;

class Ta3reefTarqeemStatement : public Statement
{
    std::string _name;
    TarqeemList _list;

public:
    inline Ta3reefTarqeemStatement(std::string name, TarqeemList list) : _name(name), _list(list) {}

    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

class LefStatement : public Statement
{
private:
    Statement *_init;
    TalmaStatement *_talmaStmt;

public:
    LefStatement(Statement *init, Expression *condition, Statement *b3dKolLaffa, BlockStatement *block);
    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

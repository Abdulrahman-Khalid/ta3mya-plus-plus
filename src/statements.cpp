#include "statements.h"

Optional<Result> BlockStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BlockStatement::toString() const {
    return "BlockStatement{program: " + _programNode->toString() + "}";
}

Optional<Result> ProgramNode::compile(CompileContext& compile_context) const {
    for (const auto& stmt : _stmts) {
        stmt->compile(compile_context);
    }
    return {};
}

string ProgramNode::toString() const {
    string out = "ProgramNode{stmts: [";
    for (auto i = 0; i < _stmts.size(); i++) {
        out += _stmts[i]->toString();
        if (i+1 < _stmts.size()) {
            out += ", ";
        }
    }
    return out + "]}";
}

Optional<Result> BasyStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BasyStatement::toString() const {
    return "BasyStatement{exp: " + _toBasy->toString() + "}";
}

Optional<Result> LwStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string LwStatement::toString() const {
    string out = "LwStatement{conditional_stmts: [";
    for (auto i = 0; i < _conditionalBlocks.size(); i++) {
        out += "ConditionalBlock{condition: " + _conditionalBlocks[i].condition->toString()
            + ", block:" + _conditionalBlocks[i].block->toString() + "}";
        if (i+1 < _conditionalBlocks.size()) {
            out += ", ";
        }
    }
    return out + "]}";
}

void HaletStatement::attachSymbol(SymbolExpression* symbol) {
    for (auto& conditionalBlock: _conditionalBlocks) {
        conditionalBlock.condition = new BinaryExpression(symbol, "==", conditionalBlock.condition);
    }
}

Optional<Result> LwGroupStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string LwGroupStatement::toString() const {
    string out = "LwGroupStatement{lw_stmt: " + _lwStatement->toString();
    if (_8eroBlock) {
        return out + ", 8ero_block: " + _8eroBlock->toString() + "}";
    } else {
        return out + "}";
    }
}

Optional<Result> KarrarL7dStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string TalmaStatement::toString() const {
    return "TalmaStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

Optional<Result> TalmaStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string KarrarL7dStatement::toString() const {
    return "KarrarL7dStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

Optional<Result> Ta3reefMota8ierStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefMota8ierStatement::toString() const {
    std::string out = "Ta3reefMota8ierStatement{symbol: " + _symbol + ", type: " + typeToString(_type);
    return _init ? out + ", init_exp: " + _init->toString() + "}" : out + "}";
}

Optional<Result> Ta3reefThabetStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement{symbol: " + _symbol + ", type: " + typeToString(_type)
        + ", init_exp: " + _init->toString() + "}";
}

Optional<Result> ArgsDeclarationStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string ArgsDeclarationStatement::toString() const {
    string out = "ArgsDeclarationStatement{decls: [";
    for (auto i = 0; i < _declarations.size(); i++) {
        out += _declarations[i]->toString();
        if (i+1 < _declarations.size()) {
            out += ", ";
        }
    }
    return out + "]}";
}

Optional<Result> Ta3reefDallahStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefDallahStatement::toString() const {
    return "Ta3reefDallahStatement{type: " + typeToString(_type) + ", name: " + _name
        + ", args_declaration: " + _args->toString() + ", block: " + _block->toString();
}

Optional<Result> Ta3reefTarqeemStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefTarqeemStatement::toString() const {
    string listString;
    for (int i = 0; i < _list.size(); i++) {
        if (i+1 == _list.size()) {
            listString += _list[i];
        } else {
            listString += _list[i] + ", ";
        }
    }
    
    return "Ta3reefTarqeemStatement{name: " + _name + ", list: [" + listString +"]}";
}

Optional<Result> AssignmentStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string AssignmentStatement::toString() const {
    return "AssignmentStatement{symbol: " + _symbol + ", exp: " + _exp->toString() + "}";
}

LefStatement::LefStatement(Statement* init, Expression* condition,
                           Statement* b3dKolLaffa, BlockStatement* block) : _init(init) {
    block->addStatement(b3dKolLaffa);
    _talmaStmt = new TalmaStatement(condition, block);
}

Optional<Result> LefStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string LefStatement::toString() const {
    return "LefStatement{init: " + _init->toString() + ", talma: " + _talmaStmt->toString() + "}";
}

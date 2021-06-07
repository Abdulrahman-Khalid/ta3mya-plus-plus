#include "statements.h"

CompileResult BlockStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BlockStatement::toString() const {
    return "BlockStatement{program: " + _programNode->toString() + "}";
}

CompileResult ProgramNode::compile(CompileContext& compile_context) const {
    for (const auto& stmt : _stmts) {
        stmt->compile(compile_context);
    }
    return {};
}

string ProgramNode::toString() const {
    string out = "ProgramNode{stmts: [";
    for (auto i = 0; i < _stmts.size(); i++) {
        // out += "line_number: " + to_string(_stmts[i]->getLineNumber()) + ", stmt: ";
        out += _stmts[i]->toString();
        if (i+1 < _stmts.size()) {
            out += ", ";
        }
    }
    return out + "]}";
}

CompileResult BasyStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BasyStatement::toString() const {
    return "BasyStatement{exp: " + _toBasy->toString() + "}";
}

CompileResult LwStatement::compile(CompileContext& compile_context) const {
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

CompileResult LwGroupStatement::compile(CompileContext& compile_context) const {
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

CompileResult KarrarL7dStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string TalmaStatement::toString() const {
    return "TalmaStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

CompileResult TalmaStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string KarrarL7dStatement::toString() const {
    return "KarrarL7dStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

CompileResult Ta3reefMota8ierStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefMota8ierStatement::toString() const {
    std::string out = "Ta3reefMota8ierStatement{symbol: " + _symbol + ", type: " + typeToString(_type);
    return _init ? out + ", init_exp: " + _init->toString() + "}" : out + "}";
}

CompileResult Ta3reefThabetStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement{symbol: " + _symbol + ", type: " + typeToString(_type)
        + ", init_exp: " + _init->toString() + "}";
}

CompileResult Ta3reefDallahStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefDallahStatement::toString() const {
    string argsStr = "";
    for (int i = 0; i < _args->size(); i++) {
        if (i+1 == _args->size()) {
            argsStr += (*_args)[i]->toString();
        } else {
            argsStr += (*_args)[i]->toString() + ", ";
        }
    }

    return "Ta3reefDallahStatement{type: " + typeToString(_type) + ", name: " + _name
        + ", args_declaration: [" + argsStr + "], block: " + _block->toString();
}

CompileResult Ta3reefTarqeemStatement::compile(CompileContext& compile_context) const {
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

CompileResult AssignmentStatement::compile(CompileContext& compile_context) const {
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

CompileResult LefStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string LefStatement::toString() const {
    return "LefStatement{init: " + _init->toString() + ", talma: " + _talmaStmt->toString() + "}";
}

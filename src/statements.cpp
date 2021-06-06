#include "statements.h"

void BlockStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string BlockStatement::toString() const {
    return "BlockStatement{program: " + _programNode->toString() + "}";
}

void ProgramNode::compile(CompileContext & compile_context ) const {
    for (const auto& stmt : _stmts) {
        stmt->compile(compile_context);
    }
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

void BasyStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string BasyStatement::toString() const {
    return "BasyStatement{exp: " + _toBasy->toString() + "}";
}

void LwStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string LwStatement::toString() const {
    string out = "LwStatement{conditional_stmts: [";
     for (auto i = 0; i < _conditionalBlocks.size(); i++) {
        out += "ConditionalBlock{condition: " + _conditionalBlocks[i].condition->toString();
        out += ", block:" + _conditionalBlocks[i].block->toString();
        out += "}";
        if (i+1 < _conditionalBlocks.size()) {
            out += ", ";
        }
    }
    return out + "]}";
}

void LwGroupStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string LwGroupStatement::toString() const {
    string out =  "LwGroupStatement{lw_stmt: " + _lwStatement->toString();
    if (_8eroBlock) {
        return out + ", 8ero_block: " + _8eroBlock->toString() + "}";
    } else {
        return out + "}";
    }
}

void KarrarL7dStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string KarrarL7dStatement::toString() const {
    return "KarrarL7dStatement";
}

void Ta3reefMota8ierStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string Ta3reefMota8ierStatement::toString() const {
    return "Ta3reefMota8ierStatement";
}

void Ta3reefThabetStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement";
}

void Ta3reefDallahStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string Ta3reefDallahStatement::toString() const {
    return "Ta3reefDallahStatement";
}

void Ta3reefTarqeemStatement::compile(CompileContext & compile_context ) const {
    // TODO
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

void AssignmentStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string AssignmentStatement::toString() const {
    return "AssignmentStatement";
}

void LefStatement::compile(CompileContext & compile_context ) const {
    // TODO
}

string LefStatement::toString() const {
    return "LefStatement";
}

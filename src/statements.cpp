#include "statements.h"

Program BlockStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string BlockStatement::toString() const {
    return "BlockStatement";
}

Program ProgramNode::compile(CompileContext & compile_context ) const {
    Program program;
    for (auto stmt : _stmts) {
        auto newProgram = stmt->compile(compile_context );
        program.reserve(program.size() + newProgram.size());
        program.insert(program.end(), newProgram.begin(), newProgram.end());
    }
    return program;
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

Program BasyStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string BasyStatement::toString() const {
    return "BasyStatement{exp: " + _toBasy->toString() + "}";
}

Program LWGroupStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string LWGroupStatement::toString() const {
    return "LWGroupStatement";
}

Program KarrarL7dStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string KarrarL7dStatement::toString() const {
    return "KarrarL7dStatement";
}

Program Ta3reefMota8ierStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Ta3reefMota8ierStatement::toString() const {
    return "Ta3reefMota8ierStatement";
}

Program Ta3reefThabetStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement";
}

Program Ta3reefDallahStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Ta3reefDallahStatement::toString() const {
    return "Ta3reefDallahStatement";
}

Program Ta3reefTarqeemStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Ta3reefTarqeemStatement::toString() const {
    return "Ta3reefTarqeemStatement";
}

Program AssignmentStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string AssignmentStatement::toString() const {
    return "AssignmentStatement";
}

Program Fe7aletStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string Fe7aletStatement::toString() const {
    return "Fe7aletStatement";
}

Program LefStatement::compile(CompileContext & compile_context ) const {
    // TODO
    return Program();
}

string LefStatement::toString() const {
    return "LefStatement";
}

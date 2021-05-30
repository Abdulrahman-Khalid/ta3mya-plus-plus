#include "statements.h"

Program BlockStatement::compile() const {
    // TODO
    return Program();
}

string BlockStatement::toString() const {
    return "BlockStatement";
}

Program ProgramNode::compile() const {
    Program program;
    for (auto stmt : _stmts) {
        auto newProgram = stmt->compile();
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

Program BasyStatement::compile() const {
    // TODO
    return Program();
}

string BasyStatement::toString() const {
    return "BasyStatement{exp: " + _toBasy->toString() + "}";
}

Program LWGroupStatement::compile() const {
    // TODO
    return Program();
}

string LWGroupStatement::toString() const {
    return "LWGroupStatement";
}

Program KarrarL7dStatement::compile() const {
    // TODO
    return Program();
}

string KarrarL7dStatement::toString() const {
    return "KarrarL7dStatement";
}

Program Ta3reefMota8ierStatement::compile() const {
    // TODO
    return Program();
}

string Ta3reefMota8ierStatement::toString() const {
    return "Ta3reefMota8ierStatement";
}

Program Ta3reefThabetStatement::compile() const {
    // TODO
    return Program();
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement";
}

Program Ta3reefDallahStatement::compile() const {
    // TODO
    return Program();
}

string Ta3reefDallahStatement::toString() const {
    return "Ta3reefDallahStatement";
}

Program Ta3reefTarqeemStatement::compile() const {
    // TODO
    return Program();
}

string Ta3reefTarqeemStatement::toString() const {
    return "Ta3reefTarqeemStatement";
}

Program AssignmentStatement::compile() const {
    // TODO
    return Program();
}

string AssignmentStatement::toString() const {
    return "AssignmentStatement";
}

Program Fe7aletStatement::compile() const {
    // TODO
    return Program();
}

string Fe7aletStatement::toString() const {
    return "Fe7aletStatement";
}

Program LefStatement::compile() const {
    // TODO
    return Program();
}

string LefStatement::toString() const {
    return "LefStatement";
}

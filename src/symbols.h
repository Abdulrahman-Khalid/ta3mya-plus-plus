#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "error_registry.h"
#include "optional.h"
#include "type.h"
#include "scope.h"

using std::string;
using std::vector;

enum class SymbolType: uint8_t { FUNC, TARQEEM, DATA };

inline string symbolTypeToString(SymbolType st) {
    switch (st) {
    case SymbolType::FUNC:
        return "Function";
    case SymbolType::TARQEEM:
        return "Tarqeem";
    case SymbolType::DATA:
        return "Data";
    }

    return "????";
}

struct Symbol {
    string name;
    Scope scope;
    SymbolType symbolType;

    // {name: "a", scope: [0,1,1]}.toString() == ":0:1:1:a"
    inline string toString() const {
        return scope.toString() + name;
    }
};

struct DataSymbol : public Symbol {
    bool isVar;
    bool isUsed = false;
    bool isInitialized = false;
    int declarationLineNumber;
    Type type;
};

struct FuncSymbol : public Symbol {
    vector<DataSymbol*> args;
    Type returnType;
    Symbol* returnSymbol;
    std::string bodyLabel;
};

class SymbolTable {
private:
    std::unordered_map<string, vector<Symbol*> > Symbol_Table;

    std::vector<DataSymbol*> _getAllDataSymbols() const;
public:
    // get returns a pointer to symbol given its name and its scope
    // if not available return null
    // the returned symbol may exist in the given scope or a larger one
    Symbol* get(string name, Scope scope) const;

    // add adds symbol s
    // returns false if symbol exists, otherwise true if succeeded
    bool add(Symbol* s);

    // get the data (vars/const) and stringify them according to output-specs.md
    std::string getSections() const;

    void checkUnusedDataSymbols(WarningRegistry& w);
};

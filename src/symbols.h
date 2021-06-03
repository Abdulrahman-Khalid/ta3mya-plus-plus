#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "scope.h"

using std::string;
using std::vector;

struct Symbol {
    string name;
    Scope scope;
};

struct DataSymbol : public Symbol {
    bool isVar;
    string type;
};
struct FuncSymbol : public Symbol {};

class SymbolTable {
private:

  std::unordered_map<string, vector<Symbol*> > Symbol_Table;
  
public:
    // get returns a pointer to symbol given its name and its scope
    // if not available return null
    // the returned symbol may exist in the given scope or a larger one
    Symbol* get(string name, Scope scope) const;

    // add adds symbol s
    // returns false if symbol exists, otherwise true if succeeded
    bool add(Symbol* s);
};

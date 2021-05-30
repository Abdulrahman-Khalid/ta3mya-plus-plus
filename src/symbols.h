#pragma once
#include <string>
#include<iostream>
#include<unordered_map>

using std::string;

struct Symbol {
    string name;
};

struct DataSymbol : public Symbol {
    bool isVar;
    string type;
};
struct FuncSymbol : public Symbol {};

class SymbolTable {
private:

  std::unordered_map<string, Symbol* > Symbol_Table;
  
public:
    // get returns a pointer to symbol given its name
    // if not available return null
    Symbol* get(string name) const;

    // add adds symbol s
    // fails if symbol exists
    void add(Symbol* s);
};

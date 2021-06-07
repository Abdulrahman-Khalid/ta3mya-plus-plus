#include <algorithm>

#include "symbols.h"

Symbol* SymbolTable::get(string name, Scope scope) const {
    std::unordered_map<string, vector<Symbol *>>::const_iterator got = Symbol_Table.find(name);
    if ( got == Symbol_Table.end() )
    {
      // std::cout << "not found\n";
      return nullptr;

    }
    else
    {
      // std::cout << got->first << " is " << got->second<<std::endl;
      Symbol* tmp = nullptr;
      for (auto s : got->second) {
        if (s->scope.includes(scope)) {
          if (tmp == nullptr || s->scope.depth() >= tmp->scope.depth()) {
            tmp = s;
          }
        }
      }
      return tmp;
    }

}

bool SymbolTable::add(Symbol* s ) {
  std::string name = (*s).name;

  // if name exists
  auto got = Symbol_Table.find(name);
  if (got != Symbol_Table.end()) {
    auto symbols = got->second;

    // if same symbol, don't add
    if (std::find(symbols.begin(), symbols.end(), s) != symbols.end()) {
      return false;
    }

    // append
    symbols.push_back(s);
    Symbol_Table[name] = symbols;
    return true;
  }

  // create new vector
  Symbol_Table.insert({name, vector<Symbol*>({s})});
}

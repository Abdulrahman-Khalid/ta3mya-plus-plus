#include "symbols.h"
#include <cassert>

Symbol* SymbolTable::get(string name) const {
    std::unordered_map<string, Symbol *>::const_iterator got = Symbol_Table.find(name);
    if ( got == Symbol_Table.end() )
    {
      // std::cout << "not found\n";
      return nullptr;

    }
    else
    {
      // std::cout << got->first << " is " << got->second<<std::endl;
      return got->second;
    }

}

void SymbolTable::add(Symbol* s ) {
  std::string name = (*s).name;
  assert(get(name) != nullptr && "name already exists");
  Symbol_Table.insert({{name,s}});
}

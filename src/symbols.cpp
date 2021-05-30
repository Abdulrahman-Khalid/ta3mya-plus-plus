#include "symbols.h"
//<symbol name ,type  >

Symbol* SymbolTable::get(string name) const {
    // TODO
    std::unordered_map<string, Symbol *>::const_iterator got = Symbol_Table.find(name);
    if ( got == Symbol_Table.end() )
    {
      std::cout << "not found\n";
      return nullptr;

    }
    else
    {
      std::cout << got->first << " is " << got->second<<std::endl;
      return got->second;
    }

}

void SymbolTable::add(Symbol* s ) {
    // TODO
    std::string name = (*s).name;
    if(get(name) == nullptr)
    {
      std::cout<<"inserted\n";
      Symbol_Table.insert({{name,s}});
      return;
    }
    std::cout<<"didnt insert\n";
}

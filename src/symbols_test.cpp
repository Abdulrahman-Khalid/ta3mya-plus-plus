#include "symbols.h"
#include <iostream>

int testSymbolTable() {
    Symbol *s =new Symbol {"aa"};
    SymbolTable table;

    table.add(s);
    table.add(s);
    Symbol* a ;
    a = table.get((*s).name);
    std::cout<<(*a).name<<std::endl;

    return 0;
}

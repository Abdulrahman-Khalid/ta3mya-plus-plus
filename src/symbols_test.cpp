#include <iostream>
#include <cassert>

#include "symbols.h"

using namespace std;

void testSymbolTable() {
    SymbolTable table;

    {
        auto s = new Symbol {name: "aa", scope: Scope()};
        assert(table.add(s));
        assert(!table.add(s));
        assert(!table.add(s));
        auto a = table.get(s->name, s->scope);
        assert(a == s);

        a = table.get(s->name, Scope(vector<Level>({0, 1})));
        assert(a == s);
    }

    {
        auto s = new Symbol {name: "aa", scope: Scope(vector<Level>({1, 1}))};
        assert(table.add(s));
        assert(!table.add(s));
        assert(!table.add(s));
        auto a = table.get(s->name, s->scope);
        assert(a == s);

        a = table.get(s->name, Scope(vector<Level>({1, 1, 2, 3})));
        assert(a == s);
    }

    {
        auto s = new Symbol {name: "aa", scope: Scope(vector<Level>({1, 5, 0}))};
        assert(table.add(s));
        assert(!table.add(s));
        assert(!table.add(s));
        auto a = table.get(s->name, s->scope);
        assert(a == s);

        a = table.get(s->name, Scope(vector<Level>({1,5,0,2})));
        assert(a == s);
    }

    {
        auto s = new Symbol {name: "bb", scope: Scope(vector<Level>({1, 5, 0}))};
        assert(table.add(s));
        assert(!table.add(s));
        assert(!table.add(s));
        auto a = table.get(s->name, s->scope);
        assert(a == s);
    }
}

void testSymbol() {
    auto s = new Symbol {name: "aa", scope: Scope(vector<Level>({1, 1}))};
    assert(s->toString() == ":1:1:aa");
}


void testGetSections() {
    SymbolTable table;
    DataSymbol* s = nullptr;

    { // 1
        s =  new DataSymbol();
        s->name = "x";
        s->isVar = 1;
        s->scope= Scope(vector<Level>({0,1,2}));
        s->symbolType = SymbolType::DATA;
        s->type = Type::INT;
        table.add(s);
    }

    { // 2
        s =  new DataSymbol();
        s->name = "y";
        s->isVar = 0;
        s->scope= Scope(vector<Level>({0,1,2}));
        s->symbolType = SymbolType::DATA;
        s->type = Type::REAL;
        table.add(s);
    }

    { // 3
        s =  new DataSymbol();
        s->name = "x";
        s->isVar = 1;
        s->scope= Scope(vector<Level>({1,1,2}));
        s->symbolType = SymbolType::DATA;
        table.add(s);
    }

    cout << table.getSections();
}
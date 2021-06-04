#include "symbols.h"
#include <iostream>
#include <cassert>

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

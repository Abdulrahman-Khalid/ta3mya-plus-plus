#pragma once
#include "program.h"
#include "scope.h"
#include "symbols.h"
using std::string;
struct CompileContext
{
  ScopeTracker scope_tracker;
  SymbolTable  symbol_table;
};
class Node {
public:
    virtual void compile(CompileContext & compile_context ) const = 0;

    // toString returns a string representation
    // of the object for debugging
    virtual string toString() const = 0;
};

#pragma once
#include "program.h"
#include "scope.h"
#include "symbols.h"
#include "quadraples.h"
#include <cassert>
using std::string;
class CompileContext
{
  public:
    ScopeTracker scope_tracker;
    SymbolTable  symbol_table;
    QuadruplesTable quadruples_table;
    Program toProgram() const {
      Program p;
      for (auto &quadrauple : quadruples_table)
      {
        assert(quadrauple.size() == 4);
        AssemblyLine line = NULL; //TODO
        p.push_back(line);
      }
      return p;
    }
};
class Node {
public:
    virtual void compile(CompileContext & compile_context ) const = 0;

    // toString returns a string representation
    // of the object for debugging
    virtual string toString() const = 0;
};

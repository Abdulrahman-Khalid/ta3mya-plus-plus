#pragma once

#include "program.h"
#include "scope.h"
#include "symbols.h"
#include "quadraples.h"

struct CompileContext {
	ScopeTracker scope_tracker;
	SymbolTable  symbol_table;
	QuadruplesTable quadruples_table;

	inline Program toProgram() const {
		Program p;
		for (const auto& quadrauple : quadruples_table) {
			p.push_back(quadrauple.toString());
		}
		return p;
	}
};

using std::string;
class Node {
public:
	virtual void compile(CompileContext& compile_context) const = 0;

	// toString returns a string representation
	// of the object for debugging
	virtual string toString() const = 0;
};

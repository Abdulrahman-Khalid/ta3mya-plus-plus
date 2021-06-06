#pragma once

#include <optional>

#include "program.h"
#include "scope.h"
#include "symbols.h"
#include "quadraples.h"

using Error = std::string;

struct CompileContext {
	ScopeTracker scope_tracker;
	SymbolTable  symbol_table;
	QuadruplesTable quadruples_table;
	vector<Error> errors;

	inline Program toProgram() const {
		Program p;
		for (const auto& quadrauple : quadruples_table) {
			p.push_back(quadrauple.toString());
		}
		return p;
	}
};


template<typename T>
using Optional = std::optional<T>;

// Result is the name of the variable the holds the expression result
// it could be a literal to be used directly
using Result = std::string;

class Node {
public:
	virtual Optional<Result> compile(CompileContext& compile_context) const = 0;

	// toString returns a string representation
	// of the object for debugging
	virtual string toString() const = 0;
};

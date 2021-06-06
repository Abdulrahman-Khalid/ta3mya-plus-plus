#pragma once

#include <optional>

#include "program.h"
#include "scope.h"
#include "symbols.h"
#include "quadraples.h"
#include "tmpvars.h"

#define EMPTY(s) s.find_first_not_of(" \n\t") == std::string::npos

struct Error {
	string line_number = "";
	string msg = "";
	string symbol = "";

	void display() const {
		std::cerr << "ERROR" << (EMPTY(line_number) ? ":" : " (near line " + line_number) + "):"
			<< msg << (EMPTY(symbol) ? "" : " at symbol \"" + symbol + "\"") << std::endl;
	}
};

struct CompileContext {
	ScopeTracker scope_tracker;
	SymbolTable  symbol_table;
	QuadruplesTable quadruples_table;
	TempVarsRegistry tempVarsRegistry;
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

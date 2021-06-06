#pragma once

#include <stdio.h>

#include "program.h"
#include "scope.h"
#include "symbols.h"
#include "quadraples.h"
#include "tmpvars.h"
#include "error_registry.h"
#include "optional.h"

class LabelsCreator {
	int _i = 0;
	char buffer[1024];
public:
	inline std::string next() {
		sprintf(buffer, "LBL#%03X", _i++);
		return std::string(buffer);
	}
};

struct CompileContext {
	ScopeTracker scopeTracker;
	SymbolTable  symbolTable;
	QuadruplesTable quadruplesTable;
	TempVarsRegistry tempVarsRegistry;
	ErrorRegistry errorRegistry;
	LabelsCreator labelsCreator;

	inline Program toProgram() const {
		Program p;
		for (const auto& quadrauple : quadruplesTable) {
			p.push_back(quadrauple.toString());
		}
		return p;
	}
};

// Result is the name of the variable the holds the expression result
// it could be a literal to be used directly
using Result = std::string;

class Node {
protected:
	int _lineNumber;
public:
	virtual Optional<Result> compile(CompileContext& compile_context) const = 0;

	// toString returns a string representation
	// of the object for debugging
	virtual string toString() const = 0;

	inline void setLineNumber(int lineNumber) { _lineNumber = lineNumber; }
	inline int getLineNumber() { return _lineNumber; }
};

#pragma once

#include <stdio.h>
#include <stack>

#include "program.h"
#include "scope.h"
#include "symbols.h"
#include "quadruples.h"
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

typedef std::string EnumInstance;
typedef std::string EnumValue;
template<typename K, typename V> using Map = std::unordered_map<K, V>;

struct CompileContext {
	ScopeTracker scopeTracker;
	SymbolTable  symbolTable;
	Map<int, QuadruplesTable> quadruplesTables;
	TempVarsRegistry tempVarsRegistry;
	ErrorRegistry errorRegistry;
	WarningRegistry warningRegistry;
	LabelsCreator labelsCreator;
	stack<FuncSymbol*> functionDefinitions;
	Map<EnumInstance, EnumValue> enumsMap;

	inline void prependQuadruple(Quadruple q) {
		QuadruplesTable& qt = quadruplesTables[functionDefinitions.size()];
		qt.insert(qt.begin(), q);
	}

	inline void addQuadruple(Quadruple q) {
		QuadruplesTable& qt = quadruplesTables[functionDefinitions.size()];
		qt.push_back(q);
	}
	
	inline Program toProgram() const {
		Program p;
		
		p.push_back(symbolTable.getSections());
		p.push_back("; code segment");
		
		for (const auto& qt : quadruplesTables) {
			for (const auto& q: qt.second) {
				if(q.opcode == Opcode::PROC)
					p.push_back("");
				p.push_back(q.toString());
			}
		}

		return p;
	}
};

struct CompileResult {
    // out is the name of the variable the holds the expression result
    // it could be a literal to be used directly
    Optional<std::string> out;

	// type of expression passed to parent expression
	Optional<Type> type;

	// scope of BlockStatement
	Optional<Scope> scope;

	// whether a program node or block end with a basy stmt
	Optional<bool> endsWithBasy;
};

class Node {
protected:
	int _lineNumber;
public:
	virtual CompileResult compile(CompileContext& compile_context) const = 0;

	// toString returns a string representation
	// of the object for debugging
	virtual string toString() const = 0;

	inline void setLineNumber(int lineNumber) { _lineNumber = lineNumber; }
	inline int getLineNumber() { return _lineNumber; }
};

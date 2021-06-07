#include "statements.h"

CompileResult BlockStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BlockStatement::toString() const {
    return "BlockStatement{program: " + _programNode->toString() + "}";
}

CompileResult ProgramNode::compile(CompileContext& compile_context) const {
    for (const auto& stmt : _stmts) {
        stmt->compile(compile_context);
    }
    return {};
}

string ProgramNode::toString() const {
    string out = "ProgramNode{stmts: [";
    for (auto i = 0; i < _stmts.size(); i++) {
        // out += "line_number: " + to_string(_stmts[i]->getLineNumber()) + ", stmt: ";
        out += _stmts[i]->toString();
        if (i+1 < _stmts.size()) {
            out += ", ";
        }
    }
    return out + "]}";
}

CompileResult BasyStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string BasyStatement::toString() const {
    return "BasyStatement{exp: " + _toBasy->toString() + "}";
}

CompileResult LwStatement::compile(CompileContext& compile_context) const {
    /*
    lw (C1) {B1}
    8ero lw (C2) {B2}
    8ero lw (C3) {B3}
    8ero {B4}
    ....
    JZ C1 L1
    B1
    JMP DONE

    L1: JZ C2 L2
    B2
    JMP DONE

    L2: JZ C3 L3
    B3
    JMP DONE

    L3: NOP
    B4  (if it exists)
    DONE: NOP
    */
    string doneLabel = compile_context.labelsCreator.next(), nextJZLabel = "";
    // Create conditionals quadruples
    for(int i = 0; i < _conditionalBlocks.size(); i++) {
        // Get condition
        auto conditionResult = _conditionalBlocks[i].condition->compile(compile_context);
        if (!conditionResult.out.has_value()) compile_context.abort();
        // Get label of current JZ
        auto currentJZLabel = nextJZLabel;
        // If this is the last conditional and no _8eroBlock exists then JZ to DONE
        if (i == _conditionalBlocks.size() - 1 && !_8eroBlock) {
            nextJZLabel = doneLabel;
        } else {
            // Otherwise, create the label of the next conditional to JZ to
            nextJZLabel = compile_context.labelsCreator.next();
        }
        // Add JZ
        compile_context.quadruplesTable.push_back(Quadruple{ 
            opcode: Opcode::JZ, arg1: conditionResult.out.value(),
            arg2: nextJZLabel, label: currentJZLabel
        });
        // Add block
        _conditionalBlocks[i].block->compile(compile_context);
        // Add JMP
        compile_context.quadruplesTable.push_back(Quadruple{ 
            opcode: Opcode::JMP, arg1: doneLabel
        });
    }    
    // Add 8ero label & block if it exists
    if (_8eroBlock) {
        compile_context.quadruplesTable.push_back(Quadruple{
            opcode: Opcode::NOP, label: nextJZLabel
        });
        _8eroBlock->compile(compile_context);
    }
    // Add done label
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::NOP, label: doneLabel
    });
    return {};
}

string LwStatement::toString() const {
    string out = "LwStatement{conditional_stmts: [";
    for (auto i = 0; i < _conditionalBlocks.size(); i++) {
        out += "ConditionalBlock{condition: " + _conditionalBlocks[i].condition->toString()
            + ", block:" + _conditionalBlocks[i].block->toString() + "}";
        if (i+1 < _conditionalBlocks.size()) {
            out += ", ";
        }
    }
    return _8eroBlock ? out + "], 8ero_block: " + _8eroBlock->toString() + "}" : out + "]}";
}

void HaletStatement::attachSymbol(SymbolExpression* symbol) {
    for (auto& conditionalBlock: _conditionalBlocks) {
        conditionalBlock.condition = new BinaryExpression(symbol, "==", conditionalBlock.condition);
    }
}

CompileResult KarrarL7dStatement::compile(CompileContext& compile_context) const {
    /*
    LOOP: NOP
    B
    JNZ C LOOP
    */
    // Create LOOP label
    auto loopLabel = compile_context.labelsCreator.next();
    // Add LOOP label
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::NOP, label: loopLabel
    });
    // Add block
    _block->compile(compile_context);
    // Get condition
    auto conditionResult = _condition->compile(compile_context);
    if (!conditionResult.out.has_value()) compile_context.abort();
    // Add JNZ
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::JNZ, arg1: conditionResult.out.value(), arg2: loopLabel
    });
    return {};
}

string TalmaStatement::toString() const {
    return "TalmaStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

CompileResult TalmaStatement::compile(CompileContext& compile_context) const {
    /*
    LOOP: JZ C DONE
    B
    JMP LOOP
    DONE: NOP
    */
    // Create LOOP label
    auto loopLabel = compile_context.labelsCreator.next();
    // Create DONE label
    auto doneLabel = compile_context.labelsCreator.next();
    // Get condition
    auto conditionResult = _condition->compile(compile_context);
    if (!conditionResult.out.has_value()) compile_context.abort();
    // Add JZ
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::JZ, arg1: conditionResult.out.value(),
        arg2: doneLabel, label: loopLabel
    });
    // Add block
    _block->compile(compile_context);
    // Add JML
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::JMP, arg1: loopLabel
    });
    // Add DONE label
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::NOP, label: doneLabel
    });
    return {};
}

string KarrarL7dStatement::toString() const {
    return "KarrarL7dStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

CompileResult AssignmentStatement::compile(CompileContext& compile_context) const {
    auto s = compile_context.symbolTable.get(_symbol, compile_context.scopeTracker.get());

    // error if symbol doesn't exist
    if (s == nullptr) {
        compile_context.errorRegistry.undeclaredSymbol(_symbol, _lineNumber);
        return {};
    }

    // error if symbol is not data symbol
    if (s->symbolType != SymbolType::DATA) {
        compile_context.errorRegistry.nonDataSymbol(_symbol, symbolTypeToString(s->symbolType), _lineNumber);
        return {};
    }

    auto dataSymbol = (DataSymbol*)s;

    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) compile_context.abort();

    // TODO: Handle different enum types
    if (dataSymbol->type != expResult.type.value()) {
        compile_context.errorRegistry.invalidExpressionType(dataSymbol->type, expResult.type.value());
        return {};
    }

    compile_context.quadruplesTable.push_back(Quadruple{
        opcode: Opcode::CPY, arg1: expResult.out.value(), arg2: s->name
    });

    dataSymbol->isInitialized = true;
    return {};
}

string AssignmentStatement::toString() const {
    return "AssignmentStatement{symbol: " + _symbol + ", exp: " + _exp->toString() + "}";
}

CompileResult Ta3reefMota8ierStatement::compile(CompileContext& compile_context) const {
    // error if symbol already exists
    auto s = compile_context.symbolTable.get(_symbol, compile_context.scopeTracker.get());
    if (s != nullptr) {
        compile_context.errorRegistry.redeclaredSymbol(_symbol, _lineNumber);
        return {};
    }

    // Create a new entry in the symbol table
    DataSymbol* symbol = new DataSymbol();
    symbol->name = _symbol;
    symbol->scope = compile_context.scopeTracker.get();
    symbol->symbolType = SymbolType::DATA;
    symbol->isVar = true;
    symbol->type = _type;
    compile_context.symbolTable.add(symbol);

    // Assign the symbol if an assignment exists
    if(_assignment) {
        _assignment->compile(compile_context);
    }
    return {};
}

string Ta3reefMota8ierStatement::toString() const {
    std::string out = "Ta3reefMota8ierStatement{symbol: " + _symbol + ", type: " + typeToString(_type);
    return _assignment ? out + ", assignment_exp: " + _assignment->toString() + "}" : out + "}";
}

CompileResult Ta3reefThabetStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement{symbol: " + _symbol + ", type: " + typeToString(_type)
        + ", init_exp: " + _init->toString() + "}";
}

CompileResult Ta3reefDallahStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefDallahStatement::toString() const {
    string argsStr = "";
    for (int i = 0; i < _args->size(); i++) {
        if (i+1 == _args->size()) {
            argsStr += (*_args)[i]->toString();
        } else {
            argsStr += (*_args)[i]->toString() + ", ";
        }
    }

    return "Ta3reefDallahStatement{type: " + typeToString(_type) + ", name: " + _name
        + ", args_declaration: [" + argsStr + "], block: " + _block->toString();
}

CompileResult Ta3reefTarqeemStatement::compile(CompileContext& compile_context) const {
    // TODO
    return {};
}

string Ta3reefTarqeemStatement::toString() const {
    string listString;
    for (int i = 0; i < _list.size(); i++) {
        if (i+1 == _list.size()) {
            listString += _list[i];
        } else {
            listString += _list[i] + ", ";
        }
    }
    
    return "Ta3reefTarqeemStatement{name: " + _name + ", list: [" + listString +"]}";
}

LefStatement::LefStatement(Statement* init, Expression* condition,
                           Statement* b3dKolLaffa, BlockStatement* block) : _init(init) {
    block->addStatement(b3dKolLaffa);
    _talmaStmt = new TalmaStatement(condition, block);
}

CompileResult LefStatement::compile(CompileContext& compile_context) const {
    _init->compile(compile_context);
    _talmaStmt->compile(compile_context);
    return {};
}

string LefStatement::toString() const {
    return "LefStatement{init: " + _init->toString() + ", talma: " + _talmaStmt->toString() + "}";
}

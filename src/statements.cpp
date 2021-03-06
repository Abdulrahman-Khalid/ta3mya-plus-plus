#include "statements.h"
#include "operator.h"
#include "optional.h"

CompileResult BlockStatement::compile(CompileContext& compile_context) const {
    compile_context.scopeTracker.push();
    auto programResult = _programNode->compile(compile_context);
    auto scope = compile_context.scopeTracker.get();
    compile_context.scopeTracker.pop();
    return { out: {}, type: {}, scope: scope, endsWithBasy: *(programResult.endsWithBasy) };
}

CompileResult BlockStatement::compileAsInFunc(CompileContext &compile_context) const {
    auto result = compile(compile_context);
    // If this block is function body and it does not end with basy, add RTN
    if (!*(result.endsWithBasy)) {
        compile_context.addQuadruple(Quadruple{
        opcode: Opcode::RTN
    });
    }
    return result;
}

string BlockStatement::toString() const {
    return "BlockStatement{program: " + _programNode->toString() + "}";
}

class CallBedayahStatement : public Statement {
public:
    virtual CompileResult compile(CompileContext &compile_context) const override;
    virtual string toString() const override;
};

string CallBedayahStatement::toString() const {
    return "CallBedayahStatement";
}

CompileResult CallBedayahStatement::compile(CompileContext& compile_context) const {
    // make sure bedayah exists
    auto s = compile_context.symbolTable.get("bedayah", Scope(vector<Level>({})));
    if (s == nullptr) {
        compile_context.errorRegistry.noBedayah(); // TODO
        return {};
    }

    if (s->symbolType != SymbolType::FUNC) {
        compile_context.errorRegistry.bedayahHasAnonFuncType(symbolTypeToString(s->symbolType)); // TODO
        return {};
    }

    FuncSymbol* bd = static_cast<FuncSymbol*>(s);

    // CALL <label>
    compile_context.addQuadruple(
        Quadruple {
            opcode: Opcode::CALL,
            arg1: bd->toString(),
        }
    );

    // CPY :_bedayah_RET $0
    compile_context.addQuadruple(
        Quadruple {
            opcode: Opcode::CPY,
            arg1: bd->returnSymbol->toString(),
            arg2: "",
            result: "$0",
        }
    );

    // END
    compile_context.addQuadruple(
        Quadruple {
            opcode: Opcode::END,
        }
    );

    return {};
}

CompileResult ProgramNode::compile(CompileContext& compile_context) const {
    for (const auto& stmt : _stmts) {
        stmt->compile(compile_context);
    }

    if (_isRoot) {
        CallBedayahStatement().compile(compile_context);
    }
    bool endsWithBasy = !_stmts.empty() && dynamic_cast<BasyStatement*>(_stmts.back()) != nullptr;

    CompileResult r;
    r.endsWithBasy = endsWithBasy;
    return r;
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
    auto expResult = _toBasy->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if(compile_context.functionDefinitions.empty()) {
        compile_context.errorRegistry.invalidReturn(_lineNumber);
        return {};
    }

    auto funcSymbol = compile_context.functionDefinitions.top();
    if(expResult.type.value() != funcSymbol->returnType) {
        compile_context.errorRegistry.invalidExpressionType(funcSymbol->returnType, expResult.type.value(), _lineNumber);
        return {};
    }

    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::CPY, arg1: expResult.out.value(), arg2: funcSymbol->returnSymbol->toString()
    });

    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::RTN
    });

    compile_context.tempVarsRegistry.put(expResult.out.value());
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
    C1
    JZ C1 L1
    B1
    JMP DONE

    C2
    L1: JZ C2 L2
    B2
    JMP DONE

    C3
    L2: JZ C3 L3
    B3
    JMP DONE

    L3:
    B4  (if it exists)
    DONE:
    */
    string doneLabel = compile_context.labelsCreator.next();
    Optional<string> nextConditionlabel, currentConditionLabel;
    // Create conditionals quadruples
    for(int i = 0; i < _conditionalBlocks.size(); i++) {
        // Get label of current condition
        currentConditionLabel = nextConditionlabel;
        // If this is the last conditional and no _8eroBlock exists then JZ to DONE
        if (i == _conditionalBlocks.size() - 1 && !_8eroBlock) {
            nextConditionlabel = doneLabel;
        } else {
            // Otherwise, create the label of the next condition
            nextConditionlabel = compile_context.labelsCreator.next();
        }
        // First condition doesn't need to be labeled
        if (i != 0) {
             compile_context.addQuadruple(Quadruple{
                opcode: Opcode::LABEL, label: currentConditionLabel
            });
        }
       
        // Add condition
        auto conditionResult = _conditionalBlocks[i].condition->compile(compile_context);
        if (!conditionResult.out.has_value()) {
            return {};
        }
        // Add JZ
        compile_context.addQuadruple(Quadruple{ 
            opcode: Opcode::JZ, arg1: conditionResult.out.value(),
            arg2: nextConditionlabel.value()
        });
        compile_context.tempVarsRegistry.put(conditionResult.out.value());

        // Add block
        _conditionalBlocks[i].block->compile(compile_context);
        // Add JMP
        compile_context.addQuadruple(Quadruple{ 
            opcode: Opcode::JMP, arg1: doneLabel
        });
    }    
    // Add 8ero label & block if it exists
    if (_8eroBlock) {
        compile_context.addQuadruple(Quadruple{
            opcode: Opcode::LABEL, label: nextConditionlabel
        });
        _8eroBlock->compile(compile_context);
    }
    // Add done label
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::LABEL, label: doneLabel
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
        conditionalBlock.condition = new BinaryExpression(symbol, Operator::EQUALS, conditionalBlock.condition);
    }
}

CompileResult KarrarL7dStatement::compile(CompileContext& compile_context) const {
    /*
    LOOP:
    B
    C
    JZ C LOOP
    */
    // Create LOOP label
    auto loopLabel = compile_context.labelsCreator.next();
    // Add LOOP label
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::LABEL, label: loopLabel
    });
    // Add block
    _block->compile(compile_context);
    // Add condition
    auto conditionResult = _condition->compile(compile_context);
    if (!conditionResult.out.has_value()) {
        return {};
    }
    // Add JZ
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::JZ, arg1: conditionResult.out.value(), arg2: loopLabel
    });
    compile_context.tempVarsRegistry.put(conditionResult.out.value());

    return {};
}

string TalmaStatement::toString() const {
    return "TalmaStatement{condition: " + _condition->toString()
            + " , block: " + _block->toString() + "}";
}

CompileResult TalmaStatement::compile(CompileContext& compile_context) const {
    /*
    LOOP: 
    C
    JZ C DONE
    B
    JMP LOOP
    DONE:
    */
    // Create LOOP label
    auto loopLabel = compile_context.labelsCreator.next();
    // Add LOOP label
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::LABEL, label: loopLabel
    });
    // Create DONE label
    auto doneLabel = compile_context.labelsCreator.next();
    // Add condition
    auto conditionResult = _condition->compile(compile_context);
    if (!conditionResult.out.has_value()) {
        return {};
    }
    // Add JZ
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::JZ, arg1: conditionResult.out.value(), arg2: doneLabel
    });
    compile_context.tempVarsRegistry.put(conditionResult.out.value());
    // Add block
    _block->compile(compile_context);
    // Add JMP
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::JMP, arg1: loopLabel
    });
    // Add DONE label
    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::LABEL, label: doneLabel
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

    auto dataSymbol = static_cast<DataSymbol*> (s);

    // error if symbol is const
    if (!dataSymbol->isVar) {
        compile_context.errorRegistry.constantAssignment(_symbol, _lineNumber);
        return {};
    }

    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if (dataSymbol->type != expResult.type.value()) {
        compile_context.errorRegistry.invalidExpressionType(dataSymbol->type, expResult.type.value(), _lineNumber);
        return {};
    }

    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::CPY, arg1: expResult.out.value(), arg2: s->toString()
    });
    compile_context.tempVarsRegistry.put(expResult.out.value());

    dataSymbol->isInitialized = true;
    return {};
}

string AssignmentStatement::toString() const {
    return "AssignmentStatement{symbol: " + _symbol + ", exp: " + _exp->toString() + "}";
}

CompileResult Ta3reefMota8ierStatement::compile(CompileContext& compile_context) const {
    // error if symbol already exists in the same scope
    auto s = compile_context.symbolTable.get(_symbol, compile_context.scopeTracker.get());
    if (s != nullptr && s->scope == compile_context.scopeTracker.get()) {
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
    symbol->declarationLineNumber = _lineNumber;
    if(_argDecl) {
        // Arg declarations are always initialized by calls
        symbol->isInitialized = true;
    }
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
    // error if symbol already exists in the same scope
    auto s = compile_context.symbolTable.get(_symbol, compile_context.scopeTracker.get());
    if (s != nullptr && s->scope == compile_context.scopeTracker.get()) {
        compile_context.errorRegistry.redeclaredSymbol(_symbol, _lineNumber);
        return {};
    }

    // Create a new entry in the symbol table
    DataSymbol* symbol = new DataSymbol();
    symbol->name = _symbol;
    symbol->scope = compile_context.scopeTracker.get();
    symbol->symbolType = SymbolType::DATA;
    symbol->isVar = false;
    symbol->type = _type;
    symbol->declarationLineNumber = _lineNumber;
    compile_context.symbolTable.add(symbol);

    auto expResult = _init->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if (symbol->type != expResult.type.value()) {
        compile_context.errorRegistry.invalidExpressionType(symbol->type, expResult.type.value(), _lineNumber);
        return {};
    }

    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::CPY, arg1: expResult.out.value(), arg2: symbol->toString()
    });
    compile_context.tempVarsRegistry.put(expResult.out.value());

    symbol->isInitialized = true;
    return {};
}

string Ta3reefThabetStatement::toString() const {
    return "Ta3reefThabetStatement{symbol: " + _symbol + ", type: " + typeToString(_type)
        + ", init_exp: " + _init->toString() + "}";
}

CompileResult Ta3reefDallahStatement::compile(CompileContext& compile_context) const {
    // error if symbol already exists in the same scope
    auto s = compile_context.symbolTable.get(_name, compile_context.scopeTracker.get());
    if (s != nullptr && s->scope == compile_context.scopeTracker.get()) {
        compile_context.errorRegistry.redeclaredSymbol(_name, _lineNumber);
        return {};
    }

    // Add function arguments declartion to the block
    for (auto argDecl: *_args) {
        _block->prependStatement(argDecl);
    }
    
    // Create a new entry in the symbol table
    FuncSymbol* funcSymbol = new FuncSymbol();
    funcSymbol->name = _name;
    funcSymbol->scope = compile_context.scopeTracker.get();
    funcSymbol->symbolType = SymbolType::FUNC;
    funcSymbol->returnType = _type;

    DataSymbol* returnSymbol = new DataSymbol();
    returnSymbol->name = "$RET_" + _name;
    returnSymbol->scope = compile_context.scopeTracker.get();
    returnSymbol->symbolType = SymbolType::DATA;
    returnSymbol->type = _type;
    returnSymbol->isVar = true;
    returnSymbol->isInitialized = true;

    compile_context.symbolTable.add(returnSymbol);
    funcSymbol->returnSymbol = returnSymbol;
    compile_context.symbolTable.add(funcSymbol);

    /*
    PROC F:
        B
    */
    compile_context.functionDefinitions.push(funcSymbol);

    compile_context.addQuadruple(Quadruple{
        opcode: Opcode::PROC, arg1: funcSymbol->toString()
    });
    
    auto blockScope = _block->compileAsInFunc(compile_context).scope;

    if(!blockScope.has_value()) {
        return {};
    }

    compile_context.functionDefinitions.pop();

    // Add function arguments to its FuncSymbol
    for (auto argDecl: *_args) {
        auto s = compile_context.symbolTable.get(argDecl->getSymbolName(), blockScope.value());
        assert(s != nullptr);
        DataSymbol* argSymbol = static_cast<DataSymbol*> (s);
        funcSymbol->args.push_back(argSymbol);
    }

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
    // error if symbol already exists in the same scope
    auto s = compile_context.symbolTable.get(_name, compile_context.scopeTracker.get());
    if (s != nullptr && s->scope == compile_context.scopeTracker.get()) {
        compile_context.errorRegistry.redeclaredSymbol(_name, _lineNumber);
        return {};
    }

    // add it
    TarqeemSymbol* ss = new TarqeemSymbol;
    ss->name = _name;
    ss->scope = compile_context.scopeTracker.get();
    ss->symbolType = SymbolType::TARQEEM;
    ss->list = _list;
    compile_context.symbolTable.add(ss);

    // add its enums
    for (int i = 0; i < _list.size(); i++) {
        auto key = _name + "::" + _list[i];
        auto value = std::to_string(i);
        compile_context.enumsMap.insert({key, value});
    }

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
    block->appendStatement(b3dKolLaffa);
    _talmaStmt = new TalmaStatement(condition, block);
}

CompileResult LefStatement::compile(CompileContext& compile_context) const {
    // Create a block to encapsulate the initialization & loop in a scope
    auto node = new ProgramNode();
    auto block = new BlockStatement(node);
    block->appendStatement(_init);
    block->appendStatement(_talmaStmt);
    // Compile the block
    block->compile(compile_context);
    return {};
}

string LefStatement::toString() const {
    return "LefStatement{init: " + _init->toString() + ", talma: " + _talmaStmt->toString() + "}";
}

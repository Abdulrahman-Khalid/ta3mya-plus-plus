#include "expressions.h"

CompileResult LiteralExpression::compile(CompileContext &compile_context) const
{
    return CompileResult{out : literal, type : type};
}

string LiteralExpression::toString() const
{
    return "LiteralExpression: (" + typeToString(type) + ") " + this->literal;
}

CompileResult SymbolExpression::compile(CompileContext &compile_context) const
{
    auto s = compile_context.symbolTable.get(symbol, compile_context.scopeTracker.get());

    // error if symbol doesn't exist
    if (s == nullptr)
    {
        compile_context.errorRegistry.undeclaredSymbol(symbol, _lineNumber);
        return {};
    }

    // error if symbol is not data symbol
    if (s->symbolType != SymbolType::DATA)
    {
        compile_context.errorRegistry.nonDataSymbol(symbol, symbolTypeToString(s->symbolType), _lineNumber);
        return {};
    }

    DataSymbol *ds = static_cast<DataSymbol *>(s);

    // error if symbol is not initialized
    if (!ds->isInitialized)
    {
        compile_context.errorRegistry.uninitializedVariable(symbol, _lineNumber);
        return {};
    }

    ds->isUsed = true;

    return CompileResult{out : ds->toString(), type : ds->type};
}

string SymbolExpression::toString() const
{
    return "Symbol: " + this->symbol;
}

CompileResult TarqeemInstanceExpression::compile(CompileContext &compile_context) const
{
    auto got = compile_context.enumsMap.find(_instance);

    // doesn't exist
    if (got == compile_context.enumsMap.end()) {
        compile_context.errorRegistry.undeclaredSymbol(_instance, _lineNumber);
        return {};
    }

    return LiteralExpression(got->second, Type::INT).compile(compile_context);
}

string TarqeemInstanceExpression::toString() const
{
    return "TarqeemInstance: " + _instance;
}

CompileResult BinaryExpression::compile(CompileContext &compile_context) const
{
    auto lhsResult = _lhs->compile(compile_context);
    if (!lhsResult.out.has_value() || !lhsResult.type.has_value())
        return {};

    auto rhsResult = _rhs->compile(compile_context);
    if (!rhsResult.out.has_value() || !rhsResult.type.has_value())
        return {};

    if (lhsResult.type.value() != rhsResult.type.value())
    {
        compile_context.errorRegistry.invalidExpressionType(
            lhsResult.type.value(), rhsResult.type.value(), _lineNumber);
        return {};
    }
    if (isBooleanType(lhsResult.type.value()) && isBooleanType(rhsResult.type.value()) &&
        (isNumericalOperator(_op) || isComparator(_op)))
    {
        compile_context.errorRegistry.invalidExpressionType(
            {Type::INT, Type::REAL}, Type::BOOLEAN, _lineNumber);
        return {};
    }

    auto tmpVar = compile_context.tempVarsRegistry.get();
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode : operatorToOpcode(_op),
        arg1 : lhsResult.out.value(),
        arg2 : rhsResult.out.value(),
        result : tmpVar
    });

    compile_context.tempVarsRegistry.put(lhsResult.out.value());
    compile_context.tempVarsRegistry.put(rhsResult.out.value());

    Type expressionType = isComparator(_op) || isCombiner(_op) ? Type::BOOLEAN : lhsResult.type.value();
    return CompileResult{out : tmpVar, type : expressionType};
}

string BinaryExpression::toString() const
{
    string out = "BinaryExpression{";
    out += _lhs->toString();
    out += " " + operatorToString(_op) + " ";
    out += _rhs->toString() + "}";
    return out;
}

CompileResult NegExpression::compile(CompileContext &compile_context) const
{   
    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if (!isNumericalType(expResult.type.value()))
    {
        compile_context.errorRegistry.invalidExpressionType(
            {Type::INT, Type::REAL} , expResult.type.value(), _lineNumber);
        return {};
    }

    auto tmpVar = compile_context.tempVarsRegistry.get();
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode : Opcode::NEG,
        arg1 : expResult.out.value(),
        arg2 : tmpVar
    });
    compile_context.tempVarsRegistry.put(expResult.out.value());

    return CompileResult{out : tmpVar, type : expResult.type.value()};
}

string NegExpression::toString() const
{
    return "NegExpression{" + _exp->toString() + "}";
}

CompileResult ToSa7e7Expression::compile(CompileContext &compile_context) const
{
    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if (!isNumericalType(expResult.type.value()))
    {
        compile_context.errorRegistry.invalidExpressionType(
            Type::INT, expResult.type.value(), _lineNumber);
        return {};
    }

    auto tmpVar = compile_context.tempVarsRegistry.get();
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode : Opcode::INT,
        arg1 : expResult.out.value(),
        arg2 : tmpVar
    });
    compile_context.tempVarsRegistry.put(expResult.out.value());

    return CompileResult{out : tmpVar, type : Type::INT};
}

string ToSa7e7Expression::toString() const
{
    return "ToSa7e7Expression{" + _exp->toString() + "}";
}

CompileResult To7a2i2iExpression::compile(CompileContext &compile_context) const
{
    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if (!isNumericalType(expResult.type.value()))
    {
        compile_context.errorRegistry.invalidExpressionType(
            Type::REAL, expResult.type.value(), _lineNumber);
        return {};
    }

    auto tmpVar = compile_context.tempVarsRegistry.get();
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode : Opcode::REAL,
        arg1 : expResult.out.value(),
        arg2 : tmpVar
    });
    compile_context.tempVarsRegistry.put(expResult.out.value());

    return CompileResult{out : tmpVar, type : Type::REAL};
}

string To7a2i2iExpression::toString() const
{
    return "To7a2i2iExpression{" + _exp->toString() + "}";
}

CompileResult MshExpression::compile(CompileContext &compile_context) const
{
    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    if (expResult.type.value() != Type::BOOLEAN)
    {
        compile_context.errorRegistry.invalidExpressionType(
            Type::BOOLEAN, expResult.type.value(), _lineNumber);
        return {};
    }

    auto tmpVar = compile_context.tempVarsRegistry.get();
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode : Opcode::NOT,
        arg1 : expResult.out.value(),
        arg2 : tmpVar
    });
    compile_context.tempVarsRegistry.put(expResult.out.value());

    return CompileResult{out : tmpVar, type : Type::BOOLEAN};
}

string MshExpression::toString() const
{
    return "MshExpression{" + _exp->toString() + "}";
}

CompileResult CallDallahExpression::compile(CompileContext &compile_context) const
{
    // error if symbol doesn't exist
    auto s = compile_context.symbolTable.get(_name, compile_context.scopeTracker.get());
    if (s == nullptr)
    {
        compile_context.errorRegistry.undeclaredSymbol(_name, _lineNumber);
        return {};
    }

    FuncSymbol *funcSymbol = static_cast<FuncSymbol *>(s);

    // Check arguments count equal to parameters count 
    if (_args.size() != funcSymbol->args.size())
    {
        compile_context.errorRegistry.incorrectArgsCount(
            funcSymbol->name, funcSymbol->args.size(), _args.size(), _lineNumber);
        return {};
    }

    // Compile all arguments expressions and copy them to arguments symbols
    for (auto i = 0; i < _args.size(); i++)
    {
        auto argSymbol = static_cast<DataSymbol*> (funcSymbol->args[i]);
        auto expResult = _args[i]->compile(compile_context);
        if (!expResult.out.has_value() || !expResult.type.has_value())
            return {};

        if (expResult.type.value() != argSymbol->type)
        {
            compile_context.errorRegistry.incorrectArgType(
                funcSymbol->name, argSymbol->name,
                argSymbol->type, expResult.type.value(), _lineNumber);
            return {};
        }

        compile_context.quadruplesTable.push_back(Quadruple{
            opcode : Opcode::CPY,
            arg1 : expResult.out.value(),
            arg2 : argSymbol->toString()
        });
        compile_context.tempVarsRegistry.put(expResult.out.value());
    }

    // Add CALL to jump to function body
    compile_context.quadruplesTable.push_back(Quadruple{
        opcode : Opcode::CALL,
        arg1 : funcSymbol->bodyLabel,
    });

    return CompileResult{out : funcSymbol->returnSymbol->toString(), type : funcSymbol->returnType};
}

string CallDallahExpression::toString() const
{
    string argsString;
    for (int i = 0; i < _args.size(); i++)
    {
        if (i + 1 == _args.size())
        {
            argsString += _args[i]->toString();
        }
        else
        {
            argsString += _args[i]->toString() + ",";
        }
    }

    return "CallDallahExpression{name: " + _name + ", args: [" + argsString + "]}";
}

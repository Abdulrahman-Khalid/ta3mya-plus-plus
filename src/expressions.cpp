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

    return CompileResult{out : symbol, type : ds->type};
}

string SymbolExpression::toString() const
{
    return "Symbol: " + this->symbol;
}

CompileResult TarqeemInstanceExpression::compile(CompileContext &compile_context) const
{
    // TODO
    return {};
}

string TarqeemInstanceExpression::toString() const
{
    return "TarqeemInstance: " + _instance;
}

CompileResult BinaryExpression::compile(CompileContext &compile_context) const
{
    // TODO
    return {};
}

string BinaryExpression::toString() const
{
    string out = "BinaryExpression{";
    out += lhs->toString();
    out += " " + operatorToString(op) + " ";
    out += rhs->toString() + "}";
    return out;
}

CompileResult NegExpression::compile(CompileContext &compile_context) const
{
    auto expResult = _exp->compile(compile_context);
    if (!expResult.out.has_value() || !expResult.type.has_value()) {
        return {};
    }

    // TODO: Expected Type ?
    if (!isNumerical(expResult.type.value()))
    {
        compile_context.errorRegistry.invalidExpressionType(
            Type::INT, expResult.type.value(), _lineNumber);
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

    if(!isNumerical(expResult.type.value())) {
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

    if(!isNumerical(expResult.type.value())) {
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

    return CompileResult{out : tmpVar, type : expResult.type.value()};
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

    return CompileResult{out : tmpVar, type : expResult.type.value()};
    return {};
}

string MshExpression::toString() const
{
    return "MshExpression{" + _exp->toString() + "}";
}

CompileResult CallDallahExpression::compile(CompileContext &compile_context) const
{
    // TODO
    return {};
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

#include <algorithm>

#include "symbols.h"

Symbol* SymbolTable::get(string name, Scope scope) const {
    std::unordered_map<string, vector<Symbol *>>::const_iterator got = Symbol_Table.find(name);
    if ( got == Symbol_Table.end() )
    {
      // std::cout << "not found\n";
      return nullptr;

    }
    else
    {
      // std::cout << got->first << " is " << got->second<<std::endl;
      Symbol* tmp = nullptr;
      for (auto s : got->second) {
        if (s->scope.includes(scope)) {
          if (tmp == nullptr || s->scope.depth() >= tmp->scope.depth()) {
            tmp = s;
          }
        }
      }
      return tmp;
    }

}

bool SymbolTable::add(Symbol* s ) {
  std::string name = (*s).name;

  // if name exists
  auto got = Symbol_Table.find(name);
  if (got != Symbol_Table.end()) {
    auto symbols = got->second;

    // if same symbol, don't add
    if (std::find(symbols.begin(), symbols.end(), s) != symbols.end()) {
      return false;
    }

    // append
    symbols.push_back(s);
    Symbol_Table[name] = symbols;
    return true;
  }

  // create new vector
  Symbol_Table.insert({name, vector<Symbol*>({s})});
}

std::vector<DataSymbol*> SymbolTable::_getAllDataSymbols() const {
  auto v = std::vector<DataSymbol*>();

  for (const auto& pair : Symbol_Table) {
    for (const auto& s : pair.second) {
      if (s->symbolType == SymbolType::DATA) {
        v.push_back(static_cast<DataSymbol*>(s));
      }
    }
  }

  return v;
}

std::vector<DataSymbol*> SymbolTable::_getNonDataSymbols() const {
  auto v = std::vector<DataSymbol*>();

  for (const auto& pair : Symbol_Table) {
    for (const auto& s : pair.second) {
      if (s->symbolType != SymbolType::DATA) {
        v.push_back(static_cast<DataSymbol*>(s));
      }
    }
  }

  return v;
}

std::string SymbolTable::getSections() const {
  std::string varSec;
  std::string constSec;

  for (const auto& ds : _getAllDataSymbols()) {
    std::string str = ds->toString();

    if (ds->isVar) {
      varSec += "%var " + str + '\n';
    } else {
      constSec += "%const " + str + '\n';
    }
  }

  if (varSec.size() > 0) {
    varSec = "; variables declarations\n" + varSec;
  }
  if (constSec.size() > 0) {
    constSec = "; constants declarations\n" + constSec;
  }

  return varSec + constSec;
}

void SymbolTable::checkUnusedDataSymbols(WarningRegistry& w) {
  for (const auto& ds : _getAllDataSymbols()) {
    // Check unused data symbols, ignore symbols starting with $ as they are generated by the compiler
    if(!ds->name.empty() && ds->name[0] != '$' && !ds->isUsed) {
      w.unusedSymbol(ds->name, ds->declarationLineNumber);
    }
  }
}
#include "heading.h"
ostream& operator<<(ostream& os, const Symbol& s) {
  os << "name: "<< s.name << ", scope: " << s.scope.toString() << ", symbolType: " << symbolTypeToString(s.symbolType);
  return os;
}

ostream& operator<<(ostream& os, const DataSymbol& s) {
  auto ss = static_cast<Symbol const*>(&s);
  os << std::boolalpha << "DataSymbol{"<< *ss<<", isVar: "<<s.isVar<<", isUsed: "<< s.isUsed << ", isInitialized: " << s.isInitialized << ", declarationLineNumber: "<<s.declarationLineNumber<<", type: "<<typeToString(s.type)<<"}";
  return os;
}

ostream& operator<<(ostream& os, const FuncSymbol& s) {
  auto ss = static_cast<Symbol const*>(&s);
  os << std::boolalpha << "FuncSymbol{"<<*ss<<", args: [";
  for (int i = 0; i < s.args.size(); i++) {
    if (i+1 < s.args.size()) {
      os << s.args[i] << ",";
    } else {
      os << s.args[i];
    }
  }
  os << "], returnType: "<<typeToString(s.returnType)<<", returnSymbol: "<<s.returnSymbol<<"}";
  return os;
}

ostream& operator<<(ostream& os, const TarqeemSymbol& s) {
  auto ss = static_cast<Symbol const*>(&s);

  os << "TarqeemSymbol{"<<*ss<<", list: [";
  for (int i = 0; i < s.list.size(); i++) {
    if (i+1 < s.list.size()) {
      os << s.list[i] << ",";
    } else {
      os << s.list[i];
    }
  }
  os << "]}";

  return os;
}

ostream& operator<<(ostream& os, const SymbolTable& st) {
  for (const auto& pair : st.Symbol_Table) {
    for (const auto& s : pair.second) {
      switch (s->symbolType) {
      case SymbolType::DATA:
        os << *static_cast<DataSymbol*>(s);
        break;
      case SymbolType::FUNC:
        os << *static_cast<FuncSymbol*>(s);
        break;
      case SymbolType::TARQEEM:
        os << *static_cast<TarqeemSymbol*>(s);
        break;
      }

      os << endl;
    }
  }

  return os;
}

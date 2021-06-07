#include "tmpvars.h"
#include <cassert>
#include "heading.h"

inline bool isRegister(const std::string& s) {
    return s.find('$') == 0;
}

inline bool isVar(const std::string& s) {
    return s.find("tmp") == 0;
}

std::string TempVarsRegistry::get() {
    for (int i = 0; i < _registers.size(); i++) {
        if (_registers[i] == RegisterState::NOT_USED) {
            _registers[i] = RegisterState::USED;
            return "$" + std::to_string(i);
        }
    }

    for (int i = 0;;i++) {
        if (_vars.find(i) == _vars.end()) {
            _vars.insert(i);
            return "tmp" + std::to_string(i);
        }
    }

    // unreachable
    return "";
}

void TempVarsRegistry::put(const std::string& s) {
    if (isRegister(s)) {
        auto i = stoi(s.substr(1));
        assert(_registers[i] == RegisterState::USED && "trying to put an already put reg");
        _registers[i] = RegisterState::NOT_USED;
    } else if (isVar(s)) {
        auto i = stoi(s.substr(3));
        assert(_vars.find(i) != _vars.end() && "trying to put an alread put variable");
        _vars.erase(i);
    } else {
        //assert(false && "invalid input:");
    }
}

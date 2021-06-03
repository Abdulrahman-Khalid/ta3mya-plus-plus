#include "scope.h"
#include <cassert>

bool Scope::operator==(Scope const& s2) const {
    return _levels == s2._levels;
}

bool Scope::operator!=(Scope const& s2) const {
    return _levels != s2._levels;
}

bool Scope::includes(Scope const& s2) const {
    return _levels.size() <= s2._levels.size() && 
        std::equal(_levels.begin(), _levels.end(), s2._levels.begin());
}

string Scope::toString() const {
    string s = ":";
    for (auto i : _levels) {
        s += std::to_string(i) + ":";
    }
    return s;
}

int Scope::depth() const {
    return _levels.size();
}

void Scope::push(Level l) {
    _levels.push_back(l);
}

Level Scope::pop() {
    assert(_levels.size() > 0 && "empty levels");

    auto l = _levels[_levels.size()-1];
    _levels.pop_back();
    return l;
}

void ScopeTracker::push() {
    auto i = _index[_index.size()-1];
    _scope.push(i);
    _index.push_back(0);
}

void ScopeTracker::pop() {
    auto l = _scope.pop();
    _index.pop_back();
    assert(l == _index[_index.size()-1]);
    _index[_index.size()-1]++;
}

Scope ScopeTracker::get() const {
    return _scope;
}

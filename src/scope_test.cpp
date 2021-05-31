#include "scope.h"
#include <cassert>

void testScope() {
    Scope s;
    s.push();
    assert(s.get() == ":");
    s.push();
    assert(s.get() == ":0:");
    s.push();
    assert(s.get() == ":0:0:");
    s.pop();
    assert(s.get() == ":0:");
    s.pop();
    assert(s.get() == ":");
    s.push();
    assert(s.get() == ":1:");
    s.push();
    assert(s.get() == ":1:0:");
}

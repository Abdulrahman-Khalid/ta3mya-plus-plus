#include "tmpvars.h"
#include <cassert>

#include "heading.h"

void testTempVarsRegistry() {
    TempVarsRegistry t;
    std::string v;

    assert(t.get() == "$0");
    assert(t.get() == "$1");
    assert(t.get() == "$2");
    assert(t.get() == "$3");
    assert(t.get() == "$4");
    assert(t.get() == "$5");
    assert(t.get() == "$6");
    assert(t.get() == "$7");

    assert(t.get() == "tmp0");
    assert(t.get() == "tmp1");
    assert(t.get() == "tmp2");
    t.put("tmp1");
    assert(t.get() == "tmp1");

    t.put("tmp0");
    t.put("$3");
    assert(t.get() == "$3");
    assert(t.get() == "tmp0");
}

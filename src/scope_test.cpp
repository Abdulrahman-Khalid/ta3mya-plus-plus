#include "scope.h"
#include <cassert>

void testScopeTracker() {
    ScopeTracker st;
    assert(st.get().toString() == ":");
    st.push();
    assert(st.get().toString() == ":0:");
    st.push();
    assert(st.get().toString() == ":0:0:");
    st.pop();
    assert(st.get().toString() == ":0:");
    st.pop();
    assert(st.get().toString() == ":");
    st.push();
    assert(st.get().toString() == ":1:");
    st.push();
    assert(st.get().toString() == ":1:0:");
}

void testScope() {
    Scope s(vector<int>({1,2,3}));
    Scope s2(vector<int>({1,2,3}));
    Scope s4(vector<int>({0,2,3}));
    Scope s5(vector<int>({}));
    
    assert(s == s2);
    assert(s != s4);
    assert(s.toString() == ":1:2:3:");
    assert(s5.toString() == ":");

    s.push(5);
    assert(s.toString() == ":1:2:3:5:");
    assert(s != s2);
    assert(s.pop() == 5);
    assert(s == s2);

    assert(s.includes(s2));
    assert(s.includes(Scope(vector<int>({1,2,3,4,5}))));
    assert(s.includes(Scope(vector<int>({1,2,3,4}))));
    assert(!s.includes(Scope(vector<int>({1}))));
}

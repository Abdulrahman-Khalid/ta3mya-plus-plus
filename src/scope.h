#include <vector>
#include <string>

using std::string;
using std::vector;

using Level = int;

class Scope {
    vector<Level> _levels;

public:
    inline Scope(vector<Level> levels):_levels(levels) {}
    inline Scope(): _levels({}) {}
    
    bool operator==(Scope const& s2) const;
    bool operator!=(Scope const& s2) const;

    // whether this includes s2 in scope
    // [0,1] includes [0,1,1,2] but no the other way around
    bool includes(Scope const& s2) const;

    string toString() const;
    int depth() const;

    void push(Level l);
    Level pop();
};

class ScopeTracker {
    Scope _scope;
    vector<int> _index = vector<int>({0});

public:
    void push();
    void pop();

    Scope get() const;
};

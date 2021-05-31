#include <string>

using std::string;

class Scope {
public:
    void push();
    void pop();

    string get() const;
};

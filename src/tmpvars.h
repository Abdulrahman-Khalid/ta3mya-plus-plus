#pragma once

#include <string>
#include <array>
#include <unordered_set>

class TempVarsRegistry {
    enum class RegisterState: bool {
        NOT_USED = 0, USED,
    };
    static constexpr auto EXPECTED_MAX_NUM_VARS = 100;

    std::array<RegisterState, 8> _registers;
    std::unordered_set<int> _vars;
public:
    inline TempVarsRegistry() {
        _registers.fill(RegisterState::NOT_USED);
        _vars.reserve(EXPECTED_MAX_NUM_VARS);
    }

    // get reserves a reg/var for you, returns its name
    std::string get();

    // put returns back the variable to be used by others
    // call it when you no longer use the temporary reg/var
    void put(const std::string& s);
};

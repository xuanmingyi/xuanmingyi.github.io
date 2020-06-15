#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"
#include "assert.hpp"

int main(int, char*[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    const auto& my_script = R"(
local a, b, c = ...
print(a, b, c)
    )";
    sol::load_result fx = lua.load(my_script);
    fx("your", "arguments", "here");
    return 0;
}

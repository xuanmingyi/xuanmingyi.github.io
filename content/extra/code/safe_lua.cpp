#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"
#include "assert.hpp"

int main(int, char*[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    auto bad_code_result = lua.script("123 herp.derp", [](lua_State*, sol::protected_function_result pfr) {
        return pfr;
    });
    c_assert(bad_code_result.valid());
    return 0;
}
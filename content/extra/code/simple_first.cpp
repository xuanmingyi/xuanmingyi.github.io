#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

int main(int, char*[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script("print('hello world!')");
    return 0;
}
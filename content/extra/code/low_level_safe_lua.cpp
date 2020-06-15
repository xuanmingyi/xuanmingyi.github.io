#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"
#include "assert.hpp"

int main(int, char*[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // 装载脚本
    sol::load_result script1 = lua.load_file("a_lua_script.lua");
    // 执行脚本
    script1();
    


    sol::load_result script2 = lua.load("a = 'test'");
    sol::protected_function_result script2result = script2();
    if(script2result.valid()) {
        // yay!
    }else{
        // aww
    }


    sol::load_result script3 = lua.load("return 24");
    // execute, get return value
    int value2 = script3();

    return 0;
}


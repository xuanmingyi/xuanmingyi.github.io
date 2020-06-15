Title: sol 使用文档
Date: 2020-05-25 09:37
Category: lua
Tags: c++, sol, lua
Slug: lua-sol-1
Authors: Xuan Mingyi

sol2是c++调用lua的库，这是一个封装，还需要配合lua5.1-5.3 或者luajit来使用。

下面参考官方的[tutorial: quick 'n' dirty](https://sol2.readthedocs.io/en/latest/tutorial/all-the-things.html)文档，做了如下记录。

#### 简单执行

执行[源代码文件](/extra/code/simple_first.cpp)， 同时下载[sol.hpp](https://raw.githubusercontent.com/ThePhD/sol2/develop/single/include/sol/sol.hpp)到相同目录


```c++
#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

int main(int, char*[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script("print('hello world!')");
    return 0;
}
```


编译方式
```shell
g++ simple_first.cpp `pkg-config --cflags --libs luajit` -std=c++17   # 使用c++17标准, 使用luajit
```



#### 运行lua代码

运行lua代码 或者 lua脚本
```c++
lua.script("a = 'test'");
lua.script_file("a_lua_script.lua");

int value = lua.script("return 54");
```

#### 错误回调

lua代码难免会有异常错误，如何安全得调用呢？

```c++
auto bad_code_result = lua.script("123 herp.derp", [](lua_State*, sol::protected_function_result pfr) {
    // 错误处理部分
    return pfr;
});

c_assert(bad_code_result.valid())
```

#### 运行代码(low-level)

```c++
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
```

代码你可以先load，再执行，还能对执行结果检查。

但是我们自己观察script2和script3的代码，都是 load_result类型，调用()运算，返回类型居然是不一样的？ 这是什么黑魔法？函数可以根据返回值结果重载了？

`#TODO`


#### c++传参数给lua脚本

```c++

const auto& my_script = R"(
local a, b, c = ...
print(a, b, c)
)";
sol::load_result fx = lua.load(my_script);
fx("your", "arguments", "here");
```

传递参数给lua


#### 设置和获得变量

```c++
// integer types
lua.set("number", 24);
// floating point numbers
lua["number2"] = 24.5;
// string types
lua["important_string"] = "woof woof";
// is callable, therefore gets stored as a function that can be called
lua["a_function"] = []() { return 100; };
// make a table
lua["some_table"] = lua.create_table_with("value", 24);
```

等于

```c++
// equivalent to this code
std::string equivalent_code = R"(
    t = {
        number = 24,
        number2 = 24.5,
        important_string = "woof woof",
        a_function = function () return 100 end,
        some_table = { value = 24 }
    }
)";

// check in Lua
lua.script(equivalent_code);
```


#### 
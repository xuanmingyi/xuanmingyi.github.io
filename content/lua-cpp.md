Title: lua接口
Date: 2020-05-25 09:37
Category: lua
Tags: c++, lua
Slug: lua-cpp-1
Authors: Xuan Mingyi


### 开始

在c++中调用lua脚本,我们使用的是lua5.1，不同版本之间API还是有差别的。 下面是一个简单的lua调用。


```cpp
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

lua_State* L = luaL_newstate();
if(L == nullptr) {
    return;
}

ret = luaL_loadstring(L, "a=123")
if(ret) {
    return;
}

ret = lua_pcall(L, 0, 0, 0);
if(ret) {
    return;
}

lua_close(L);
```

### 进度
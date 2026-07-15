#pragma once

#define LUAAPI_MASTER_NAMESPACE_NAME "hd"
#define LUAAPI_CATEGORY_RENDERER "rend"
#define LUAAPI_RENDERER_TYPENAME_SURFACE "_renderer_surface"
#define LUAAPI_RENDERER_TYPENAME_TEXTURE "_renderer_texture"
#define LUAAPI_RENDERER_FUNCNAME_CREATE_SURFACE "create_surface"
#define LUAAPI_RENDERER_FUNCNAME_CREATE_TEXTURE "create_texture"


#include <lua.h>
extern lua_State* L;

void Luaapi_executeFile(char* script_path);
void Luaapi_initLua();
void Luaapi_init();
void Luaapi_quit();

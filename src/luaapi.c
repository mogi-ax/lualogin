

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <renderer.h>
#include <luaapi.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <util.h>
#include <luaapi_renderer.h>

lua_State* L;

void Luaapi_executeFile(char* script_path)
{
  if (luaL_dofile(L, script_path) == LUA_OK)
  {
    logi("successfully executed file %s",script_path);
  }
  else {
    logi("error while executing %s:\n%s",script_path,lua_tostring(L,-1));
    die(1);
  }
}

void Luaapi_initLua()
{
  lua_newtable(L);

  Renderer_initLua();

  lua_setglobal(L,"hd");
}

void Luaapi_init()
{
  L = luaL_newstate();
  logi("L:%p",L);
  #if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM == 504
  luaL_requiref(L, "", luaopen_base, 1);
  luaL_requiref(L, "", luaopen_package, 1);
  luaL_requiref(L, "", luaopen_string, 1);
  luaL_requiref(L, "", luaopen_utf8, 1);
  luaL_requiref(L, "", luaopen_table, 1);
  luaL_requiref(L, "", luaopen_math, 1);
  #elif defined(LUA_VERSION_NUM) && LUA_VERSION_NUM == 505
  luaL_openselectedlibs(L,LUA_GLIBK|LUA_LOADLIBK|LUA_STRLIBK|LUA_UTF8LIBK|LUA_TABLIBK|LUA_MATHLIBK,0)
  #endif

  Luaapi_initLua();
}
void Luaapi_quit()
{
  lua_close(L);
}
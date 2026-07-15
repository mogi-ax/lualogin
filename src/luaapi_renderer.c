#include <luaapi_renderer.h>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <renderer.h>
#include <luaapi.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <util.h>

int _finalize_renderer_surface(lua_State* L)
{
  logi("L:%p",L);
  Renderer_Surface* rsurf =
    (Renderer_Surface*)luaL_checkudata(L, -1, LUAAPI_RENDERER_TYPENAME_SURFACE);
  //logi("released renderer surface %p",rsurf);
  Renderer_freeSurface(rsurf);
  return 0;
}

int _create_renderer_surface(lua_State* L)
{
  logi("L:%p",L);
  int w=luaL_checkinteger(L,-1),h=luaL_checkinteger(L, -2);
  
  Renderer_Surface* rsurf = 
   (Renderer_Surface*)lua_newuserdatauv(
    L, sizeof(Renderer_Surface),0);
  Renderer_createSurface(rsurf, w, h);
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_RENDERER_TYPENAME_SURFACE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_surface); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }
  logi("created renderer surface %p with size %d,%d",rsurf,w,h);
  lua_setmetatable(L, -2); // ?? rsurf
  
  return 1;
}

void _register_renderer_surface()
{
  lua_pushcfunction(L, _create_renderer_surface);
  lua_setfield(L, -2, LUAAPI_RENDERER_FUNCNAME_CREATE_SURFACE);
}

int _finalize_renderer_texture(lua_State* L)
{
  Renderer_Texture* rsurf =
    (Renderer_Texture*)luaL_checkudata(L, -1, LUAAPI_RENDERER_TYPENAME_TEXTURE);
  //logi("released renderer texture %p",rsurf->tex);
  Renderer_freeTexture(rsurf);
  return 0;
}

int _create_renderer_texture(lua_State* L)
{
  int w=luaL_checkinteger(L,-1),h=luaL_checkinteger(L, -2);
  Renderer_Texture* rsurf = 
   (Renderer_Texture*)lua_newuserdatauv(
    L, sizeof(Renderer_Texture),0);
  Renderer_createTexture(rsurf, w,h);
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_RENDERER_TYPENAME_TEXTURE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_texture); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }
  logi("created renderer texture %p with size %d,%d",rsurf,w,h);
  lua_setmetatable(L, -2); // ?? rsurf

  return 1;
}

void _register_renderer_texture()
{
  lua_pushcfunction(L, _create_renderer_texture);
  lua_setfield(L, -2, LUAAPI_RENDERER_FUNCNAME_CREATE_TEXTURE);
}



void Renderer_initLua()
{
  lua_newtable(L);

  _register_renderer_surface();
  _register_renderer_texture();

  lua_setfield(L, -2, "rend");
}
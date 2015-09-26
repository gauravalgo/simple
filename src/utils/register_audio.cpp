#include "register_audio.h"
#include "lua_lang_utils.h"

using namespace simple;
using namespace simple::lang;

core* m_core;

register_audio::register_audio()
{}

register_audio::~register_audio()
{}

void register_audio::setCore(simple::core *co)
{
  m_core = co;
}

core* register_audio::getCore()
{
  return m_core;
}

int register_audio::initAudio(lua_State *L)
{
  register_audio** f = (register_audio **) lua_newuserdata(L, sizeof(register_audio *));
  *f = new register_audio();

  luaL_getmetatable(L, "luaL_audio");
  lua_setmetatable(L, -2);
}

ogg_player* register_audio::checkOGG(lua_State *L, int n)
{
  return *(ogg_player**)luaL_checkudata(L, n, "luaL_audio");
}

int register_audio::loadSound(lua_State *L)
{
  ogg_player* ogg_p = checkOGG(L, 1);
  luaL_checkstring(L, 2);
  const char* path = lua_tostring(L, 2);
  ogg_p->create(path);
  return 1;
}

int register_audio::playSound(lua_State *L)
{
  ogg_player* ogg = checkOGG(L, 1);
  float volume = 1.0f;
  float pitch = 1.0f;
  if(lua_isnumber(L, 2)){
    luaL_checknumber(L, 2);
    volume = lua_tonumber(L, 2);
  }
  if(lua_isnumber(L, 3)){
    luaL_checknumber(L, 3);
    pitch = lua_tonumber(L, 3);
  }
  ogg->play(volume, pitch);
  return 1;
}

int register_audio::registerModule(lua_State *L)
{
  luaL_Reg reg[] = {
    {"new", initAudio },
    {"init", loadSound},
    {"play", playSound},
    {0, 0},
  };

  luaL_newmetatable(L, "luaL_audio");
  luaL_setfuncs(L, reg, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -1, "__index");
  lua_setglobal(L, "Audio");
  return 1;
}

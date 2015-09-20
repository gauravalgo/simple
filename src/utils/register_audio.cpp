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

int register_audio::loadSound(lua_State *L)
{
  ogg_player* ogg_p = new ogg_player();
  luaL_checkstring(L, 1);
  const char* path = lua_tostring(L, 1);
  ogg_p->create(path);

  pushPointer(L, ogg_p);
  return 1;
}

int register_audio::playSound(lua_State *L)
{
  ogg_player* ogg;
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tonumber(L, 1);
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
  ogg = getOGG(id);
  if(ogg == getOGG(id))
    ogg->play(volume, pitch);
  return 1;
}

int register_audio::registerModule(lua_State *L)
{

  luaL_Reg reg[] = {
    {"newSound", loadSound},
    {"play", playSound},
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}

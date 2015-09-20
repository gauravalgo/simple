#include "register_math.h"
#include "lua_lang_utils.h"

using namespace simple;
using namespace simple::lang;

static core* m_core;

register_math::register_math()
{}

register_math::~register_math()
{}

void register_math::setCore(simple::core *co)
{
  m_core = co;
}

core* register_math::getCore()
{
  return m_core;
}

int register_math::setOrthoView(lua_State *L)
{
  if(checkArguments(L, 9))
    LOG("Warning: setOrthoView takes : 1) left 2)right 3)bottom 4)top 5)near 6)far 7)shader");

  mat4  projection;
  projection.setToIdentity(); //TODO test this

  float left = lua_tonumber(L, 1);
  float right = lua_tonumber(L, 2);
  float bottom = lua_tonumber(L, 3);
  float top = lua_tonumber(L, 4);
  float near = lua_tonumber(L, 5);
  float far = lua_tonumber(L, 6);

  projection = projection.setOrtho(left, right, bottom, top, near, far);
  shader* s;
  int shid = lua_tointeger(L, 7);

  s = getShader(shid);
  if(s == getShader(shid)){
    s->sendUniformLocation("proj", projection);
  }
  return 1;
}

int register_math::registerModule(lua_State* L)
{
  luaL_Reg reg[] = {
    {"setOrtho",setOrthoView},
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}

int register_math::registerMetatable(lua_State* L)
{

  return 1;
}
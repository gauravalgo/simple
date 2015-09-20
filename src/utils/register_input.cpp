#include "register_input.h"
#include "lua_lang_utils.h"

using namespace simple;
using namespace simple::lang;
using namespace simple::input;

static keyboard* m_key;
static core* m_core;
static pointer* m_pointer;

register_input::register_input()
{}

register_input::~register_input()
{}

void register_input::setKeyboard(input::keyboard *key)
{
  m_key = key;
}

keyboard* register_input::getKeyboard()
{
  return m_key;
}

void register_input::setCore(simple::core *co)
{
  m_core = co;
}

core* register_input::getCore()
{
  return m_core;
}

void register_input::setPointer(simple::input::pointer* pointer)
{
  m_pointer = pointer;
}

pointer* register_input::getPointer()
{
  return m_pointer;
}

int register_input::isKeyDown(lua_State* L)
{
  luaL_checkstring(L, 1);
  const char* key = lua_tostring(L, 1);
  if(getKeyboard()->isKeyDown(key))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::isKeyUp(lua_State* L)
{
  luaL_checkstring(L, 1);
  const char* key = lua_tostring(L, 1);
  if(getKeyboard()->isKeyUp(key))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::getPointerX(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getPointerX takes no parameter");

  lua_pushnumber(L, getCore()->getWindow()->getPointX());

  return 1;
}

int register_input::getPointerY(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getPointerY takes no parameter");
  lua_pushnumber(L, getCore()->getWindow()->getPointY());
  return 1;
}

int register_input::getPointer(lua_State *L)
{
  float x = getCore()->getWindow()->getPointerPosition().x;
  float y = getCore()->getWindow()->getPointerPosition().y;

  lua_pushnumber(L, x);
  lua_pushnumber(L, y);

  return 2;
}


int register_input::isPointerPressed(lua_State *L)
{
  luaL_checkstring(L, 1);
  const char* button = lua_tostring(L, 1);
  if(getPointer()->isPressed(button))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::isPointerReleased(lua_State *L)
{
  luaL_checkstring(L, 1);
  const char* button = lua_tostring(L, 1);
  if(getPointer()->isReleased(button))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::registerModule(lua_State* L)
{
  luaL_Reg regInputFuncs[] =
    {
      {"getPointerX", getPointerX},
      {"getPointerY", getPointerY},
      {"getPointer", getPointer},
      {"isKeyDown", isKeyDown},
      {"isKeyUp", isKeyUp},
      {"pressed", isPointerPressed},
      {"released", isPointerReleased},
    };
  luaL_newlib(L, regInputFuncs);
  return 1;
}

int register_input::registerMetatable(lua_State* L)
{
  return 1;
}

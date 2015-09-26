/*******************************************************************************
 * Copyright 2015 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
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

register_input* register_input::checkInput(lua_State *L, int n)
{
  return *(register_input**)luaL_checkudata(L, n, "luaL_input");
}

int register_input::deleteInput(lua_State *L)
{
  register_input* input = checkInput(L, 1);
  if(input != NULL){
    SAFE_DELETE(input);
  }else{
    LOG("Could not delete input because it is null");
    return 0;
  }
  return 1;
}

int register_input::isKeyDown(lua_State* L)
{
  luaL_checkstring(L, 2);
  const char* key = lua_tostring(L, 2);
  if(getKeyboard()->isKeyDown(key))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::isKeyUp(lua_State* L)
{
  luaL_checkstring(L, 2);
  const char* key = lua_tostring(L, 2);
  if(getKeyboard()->isKeyUp(key))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::getPointerX(lua_State* L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function getPointerX takes no parameter");

  lua_pushnumber(L, getCore()->getWindow()->getPointX());

  return 1;
}

int register_input::getPointerY(lua_State* L)
{
  if(checkArguments(L, 2))
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
  luaL_checkstring(L, 2);
  const char* button = lua_tostring(L, 2);
  if(getPointer()->isPressed(button))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::isPointerReleased(lua_State *L)
{
  luaL_checkstring(L, 2);
  const char* button = lua_tostring(L, 2);
  if(getPointer()->isReleased(button))
    return 1;
  else
    return 0;
  return 0;
}

int register_input::initInput(lua_State *L)
{
  register_input ** f = (register_input**) lua_newuserdata(L, sizeof(register_input *));
  *f = new register_input();

  luaL_getmetatable(L, "luaL_input");
  lua_setmetatable(L, -2);

  return 1;
}

int register_input::registerModule(lua_State* L)
{
  luaL_Reg reg[] =
    {
      {"new", initInput },
      {"getPointerX", getPointerX },
      {"getPointerY", getPointerY },
      {"getPointer", getPointer },
      {"isKeyDown", isKeyDown },
      {"isKeyUp", isKeyUp },
      {"pressed", isPointerPressed },
      {"released", isPointerReleased },
      {"gc", deleteInput },
      {NULL,NULL}
    };
  luaL_newmetatable(L, "luaL_input");
  luaL_setfuncs(L, reg, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -1, "__index");
  lua_setglobal(L, "Input");

  return 1;
}

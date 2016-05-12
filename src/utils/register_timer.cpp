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
#include "register_timer.h"
#include "lua_lang_utils.h"

using namespace simple;
using namespace simple::lang;

static core* m_core;

register_timer::register_timer()
{}

register_timer::~register_timer()
{}

void register_timer::setCore(simple::core *co)
{
  m_core = co;
}

core* register_timer::getCore()
{
  return m_core;
}

int register_timer::initTimer(lua_State *L)
{
  register_timer ** timer = (register_timer**)lua_newuserdata(L, sizeof(register_timer*));
  *timer = new register_timer();

  luaL_getmetatable(L, "luaL_timer");
  lua_setmetatable(L, -2);
  return 1;
}
int register_timer::getDeltaTime(lua_State* L)
{
  lua_pushnumber(L, m_core->getWindow()->getDeltaTime());
  return 1;
}

int register_timer::getFPS(lua_State* L)
{
  float FPS = m_core->getWindow()->getFPS();
  lua_pushnumber(L, FPS);
  return 1;
}

int register_timer::registerModule(lua_State *L)
{
  luaL_Reg reg[] = {
    {"new", initTimer },
    {"getFPS", getFPS },
    {"delta", getDeltaTime },
    {NULL, NULL}
  };
  luaL_newmetatable(L, "luaL_timer");
  luaL_setfuncs(L, reg, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -1, "__index");
  lua_setglobal(L, "Timer");
  return 1;
}

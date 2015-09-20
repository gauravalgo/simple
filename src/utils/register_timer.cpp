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

int register_timer::getDeltaTime(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getDeltaTime takes no parameters");
  lua_pushnumber(L, m_core->getWindow()->getDeltaTime());
  return 1;
}

int register_timer::getFPS(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getFPS takes no parameters");
  float FPS = m_core->getWindow()->getFPS();
  lua_pushnumber(L, FPS);
  return 1;
}

int register_timer::registerModule(lua_State *L)
{
  luaL_Reg reg[] = {
    {"getFPS", getFPS },
    {"delta", getDeltaTime },
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}

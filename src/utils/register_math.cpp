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

int register_math::initMath(lua_State* L)
{
  register_math ** f = (register_math **) lua_newuserdata(L, sizeof(register_math *));
  *f = new register_math();

  luaL_getmetatable(L, "luaL_math");
  lua_setmetatable(L, -2);
  return 1;
}

shader* register_math::checkShader(lua_State* L, int n)
{
  return *(shader **)luaL_checkudata(L, n, "luaL_shader");
}

int register_math::setOrthoView(lua_State *L)
{
  mat4  projection;
  projection.setToIdentity(); //TODO test this more

  shader* s = checkShader(L, 2);
  if(!s->getLinked())
    LOG("Warning: Can't set orthoView because shader has not been linked yet!");
  float left = lua_tonumber(L, 3);
  float right = lua_tonumber(L, 4);
  float bottom = lua_tonumber(L, 5);
  float top = lua_tonumber(L, 6);
  float near = lua_tonumber(L, 7);
  float far = lua_tonumber(L, 8);

  projection = projection.setOrtho(left, right, bottom, top, near, far);
  s->sendUniformLocation("proj", projection);
  return 1;
}

int register_math::registerModule(lua_State* L)
{
  luaL_Reg reg[] = {
    {"new", initMath },
    {"setOrtho", setOrthoView },
    {NULL, NULL},
  };

  luaL_newmetatable(L, "luaL_math");
  luaL_setfuncs(L, reg, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -1, "__index");
  lua_setglobal(L, "Math");
  return 1;
}

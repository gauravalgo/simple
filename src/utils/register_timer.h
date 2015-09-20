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
#ifndef REGISTER_TIMER_H
#define REGISTER_TIMER_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "core.h"

namespace simple
{
  namespace lang
  {
    class register_timer
    {
    public:
      register_timer();
      ~register_timer();
      static int registerModule(lua_State* L);
      static void setCore(core* co);
      static core* getCore();
    private:
      static int getDeltaTime(lua_State* L);
      static int getFPS(lua_State* L);
    };
  }
}
#endif

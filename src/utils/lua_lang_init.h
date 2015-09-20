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

#ifndef LUA_LANG_INIT_H
#define LUA_LANG_INIT_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "../window/glfw_window.h"
#include "core.h"

#include <iostream>
#include <string>

namespace simple
{
      namespace lang
      {
            class lua_lang_init
            {
            public:
                  lua_lang_init();
                  ~lua_lang_init();
            private:
                  lua_State* m_L;
                  core* m_core;
            public:
                  lua_State* getState(){return m_L;}
                  void setMainScript(const char* name);
                  void create();
                  void registerFunctions();
                  void dumb();
                  void setCore(core* c){m_core = c;}
                  core* getCore(){return m_core;}
                  static int audio_register(lua_State* state);
                  static int input_register(lua_State* state);
                  static int math_register(lua_State* state);
                  static int timer_register(lua_State* state);
                  static int window_register(lua_State* state);
                  static int graphics_register(lua_State* state);
                  void makeDefaultWindow();
            private:
                  static int quit(lua_State* L);

                  //Init modules
                  static int initSimple(lua_State* L);

                  static int regTimerFuncs[];
                  static int regMathFuncs[];
                  static int regWindowFuncs[];
                  static luaL_Reg regAudioFuncs[];
                  static int regInputFuncs[];

                  static luaL_Reg GraphicsMetatableFuncs[];
                  static luaL_Reg regGraphicsFuncs[];

                  static int AudioMetatableFuncs[];
                  static int WindowMetatableFuncs[];

                  static int makeTypeMetatable(lua_State* state, luaL_Reg const* funcs);
                  static void registerModule(lua_State* state, char const* moduleName, luaL_Reg* funcs);
            };
      }
}
#endif

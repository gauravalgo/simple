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
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "../window/glfw_window.h"
#include "core.h"

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
    public:
      lua_State* getState(){return m_L;}
      glfw_window getWindow();
      void setMainScript(const char* name);
      void create();
      void registerFunctions();
      void dumb();
      bool callFunction(const char* name);
      core* simple_core;
    private:
      //WINDOW
      static int makeWindow(lua_State* L);
      static int setWindowPosition(lua_State* L);
      static int setWindowTitle(lua_State* L);
      static int getMonitorSize(lua_State* L);
      static int getWindowTicks(lua_State* L);
      static int getWindowFocus(lua_State* L);
      static int setWindowVSync(lua_State* L);
      //MOUSE
      static int getPointerX(lua_State* L);
      static int getPointerY(lua_State* L);
      static int getPointer(lua_State* L);
      //GL GRAPHICS
      static int clearScreen(lua_State* L);
      //UTILS
      static int getDeltaTime(lua_State* L);
      static int getFPS(lua_State* L);
    };
  }
}
#endif

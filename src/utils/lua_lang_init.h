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
                  bool callFunction(std::string name);
                  void setCore(core* c){m_core = c;}
                  core* getCore(){return m_core;}
                  void makeDefaultWindow();
            private:
                  //WINDOW
                  static int makeWindow(lua_State* L);
                  static int setWindowPosition(lua_State* L);
                  static int setWindowTitle(lua_State* L);
                  static int getMonitorSize(lua_State* L);
                  static int getWindowTicks(lua_State* L);
                  static int getWindowFocus(lua_State* L);
                  static int setWindowVSync(lua_State* L);
                  static int getWindowSize(lua_State* L);
                  static int getWindowWidth(lua_State* L);
                  static int getWindowHeight(lua_State* L);
                  //MOUSE
                  static int getPointerX(lua_State* L);
                  static int getPointerY(lua_State* L);
                  static int getPointer(lua_State* L);
                  static int isPointerPressed(lua_State* L);
                  static int isPointerReleased(lua_State* L);
                  //GL GRAPHICS
                  static int clearScreen(lua_State* L);
                  static int setViewport(lua_State* L);
                  //Maths
                  //-Texture
                  static int loadTexture(lua_State* L);
                  static int bindTexture(lua_State* L);
                  static int unBindTexture(lua_State* L);
                  //-Batch
                  static int createBatch(lua_State* L);
                  static int drawBatch(lua_State* L);
                  static int beginBatch(lua_State* L);
                  static int endBatch(lua_State* L);
                  static int renderMesh(lua_State* L);
                  //-Shader
                  static int createShader(lua_State* L);
                  static int createDefaultShader(lua_State* L);
                  static int bindShader(lua_State* L);
                  static int unBindShader(lua_State* L);
                  static int setOrthoView(lua_State* L);
                  static int sendShaderUniformLocation(lua_State* L);
                  //UTILS
                  static int getDeltaTime(lua_State* L);
                  static int getFPS(lua_State* L);
                  static int quit(lua_State* L);
                  static int isKeyDown(lua_State* L);
                  static int isKeyUp(lua_State* L);
                  //static int getVersion(lua_State* L);
                  static int dumbBatch(lua_State* L);
                  static int dumbTexture(lua_State* L);
                  static int dumbShader(lua_State* L);

                  //Init modules
                  static int initSimple(lua_State* L);

                  static int initWindow(lua_State* L);
                  static int initGraphics(lua_State* L);
                  static int initTime(lua_State* L);
                  static int initInput(lua_State* L);
                  static int initMath(lua_State* L);

            };
      }
}
#endif

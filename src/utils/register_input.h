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
#ifndef REGISTER_INPUT_H
#define REGISTER_INPUT_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "core.h"
#include "../input/keyboard.h"
#include "../input/pointer.h"

namespace simple
{
        using namespace simple::input;
        namespace lang
        {
                class register_input
                {
                public:
                        register_input();
                        ~register_input();
                public:
                        static int initInput(lua_State* L);

                        static void setKeyboard(keyboard* key);
                        static keyboard* getKeyboard();

                        static void setCore(core* co);
                        static core* getCore();

                        static void setPointer(pointer* pointer);
                        static pointer* getPointer();

                        static int registerModule(lua_State* L);
                private:
                        static register_input* checkInput(lua_State* L, int n);
                        static int deleteInput(lua_State* L);
                        static int isKeyDown(lua_State* L);
                        static int isKeyUp(lua_State* L);
                        static int getPointerX(lua_State* L);
                        static int getPointerY(lua_State* L);
                        static int getPointer(lua_State* L);
                        static int isPointerPressed(lua_State* L);
                        static int isPointerReleased(lua_State* L);
                };
        }
}
#endif

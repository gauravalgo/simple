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
#ifndef REGISTER_MATH_H
#define REGISTER_MATH_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "core.h"
#include "../input/keyboard.h"
#include "../input/pointer.h"
#include "../graphics/shader.h"

namespace simple
{
        namespace lang
        {
                class register_math
                {
                public:
                        register_math();
                        ~register_math();
                public:
                        static int registerModule(lua_State* L);
                        static void setCore(core* co);
                        static core* getCore();
                private:
                        static shader* checkShader(lua_State* L, int n);
                        static int initMath(lua_State* L);
                        static int setOrthoView(lua_State* L);
                };
        }
}
#endif

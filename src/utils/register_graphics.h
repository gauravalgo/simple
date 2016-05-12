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
#ifndef REGISTER_GRAPHICS_H
#define REGISTER_GRAPHICS_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "../graphics/shader.h"
#include "../graphics/font.h"
#include "../graphics/texture2D.h"
#include "../graphics/batch2d.h"

namespace simple
{
        namespace lang
        {
                using namespace simple::graphics;
                class register_graphics
                {
                public:
                        register_graphics();
                        ~register_graphics();
                        static int registerFont(lua_State* L);
                        static int registerShader(lua_State* L);
                        static int registerTexture(lua_State* L);
                        static int registerGraphics(lua_State* L);
                        static int registerBatch(lua_State* L);
                private:
                        static int deleteBatch(lua_State* L);
                        static int deleteShader(lua_State* L);
                        static int deleteFont(lua_State* L);
                        static int deleteTexture(lua_State* L);

                        static batch2d* checkBatch(lua_State* L, int n);
                        static shader* checkShader(lua_State* L, int n);
                        static font* checkFont(lua_State* L, int n);
                        static texture2D* checkTexture(lua_State* L, int n);

                        static int initBatch(lua_State* L);
                        static int initGraphics(lua_State* L);
                        static int initShader(lua_State* L);
                        static int initFont(lua_State* L);
                        static int initTexture(lua_State* L);

                        static int clear_(lua_State* L);
                        static int setBackgroundColor(lua_State* L);
                        static int setViewport(lua_State* L);
                        static int loadTexture(lua_State* L);
                        static int bindTexture(lua_State* L);
                        static int unBindTexture(lua_State* L);
                        static int createFont(lua_State* L);
                        static int drawFont(lua_State* L);
                        static int beginFont(lua_State* L);
                        static int endFont(lua_State* L);
                        static int createBatch(lua_State* L);
                        static int drawBatch(lua_State* L);
                        static int beginBatch(lua_State* L);
                        static int endBatch(lua_State* L);
                        static int renderMesh(lua_State* L);
                        static int createShader(lua_State* L);
                        static int createDefaultShader(lua_State* L);
                        static int bindShader(lua_State* L);
                        static int unBindShader(lua_State* L);
                        static int sendShaderUniformLocation(lua_State* L);
                };
        }
}
#endif

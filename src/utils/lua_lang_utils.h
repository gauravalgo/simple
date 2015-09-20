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
#ifndef LUA_LANG_UTILS_H
#define LUA_LANG_UTILS_H

#include "../utils/definitions.h"
#include "../window/glfw_window.h"
#include "../graphics/gl_graphics.h"
#include "../graphics/texture2D.h"
#include "../graphics/font.h"
#include "../graphics/batch2d.h"
#include "../graphics/shader.h"
#include "../graphics/default_shaders.h"
#include "../maths/mat4.h"
#include "../input/keyboard.h"
#include "../input/pointer.h"
#include "../sound/ogg_player.h"
#include "core.h"

using namespace simple;
using namespace simple::lang;
using namespace simple::graphics;
using namespace simple::maths;
using namespace simple::input;
using namespace simple::sound;

#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include <iostream>
#include <string>


static bool isObjectError(lua_State *L, int spot, const char* what)
{
        if(!lua_isnumber(L, spot)){
                LOG("Error: " << what << " from location " << spot << " must be an object");
                return false;
        }
        return true;
}

static bool checkArguments(lua_State* L, int number)
{
        if(lua_gettop(L) < number)
                return false;
        return true;
}

static bool isStringError(lua_State *L, int spot, const char* what)
{
        if(lua_isnumber(L, spot) || lua_isboolean(L, spot) || lua_isnil(L, spot)){
                LOG("Error: " << what << " from location " << spot << " must be a string");
                return false;
        }
        return true;
}

static float checkFloat(lua_State *L, int location)
{
        return luaL_checknumber(L,location);
}

static float checkInteger(lua_State *L, int location)
{
        return luaL_checkinteger(L,location);
}

static void pushPointer(lua_State* L, void* value)
{
        lua_pushinteger(L, (lua_Integer)value);
}

static texture2D* getTexture2D(LUA_INTEGER texture)
{
        if(texture == 0){
                LOG("texture: " << texture << " does not exist!");
                return NULL;
        }

        return (texture2D*)texture;
}

static batch2d* getBatch(LUA_INTEGER batch)
{
        if(batch == 0){
                LOG("batch: " << batch << " does not exist!");
                return NULL;
        }

        return (batch2d*)batch;
}

static font* getFont(LUA_INTEGER value)
{
        if(value == 0){
                LOG("Font: " << value << "does not exist");
                return NULL;
        }
        return (font*)value;
}

static shader* getShader(LUA_INTEGER value)
{
        if(value == 0){
                LOG("shader: " << value << " does not exist");
                return NULL;
        }

        return (shader*)value;
}

static ogg_player* getOGG(LUA_INTEGER value)
{
        if(value == 0){
                LOG("ogg: " << value << " does not exist!");
                return NULL;
        }

        return (ogg_player*)value;
}

#endif

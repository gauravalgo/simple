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

static const char* FONT_NAME = "luaL_font";
static const char* SHADER_NAME = "luaL_shader";
static const char* BATCH_NAME = "luaL_batch";
static const char* TEXTURE_NAME = "luaL_texture";

#endif

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
#include "lua_lang_init.h"
#include "register_graphics.h"
#include "register_window.h"
#include "register_input.h"
#include "register_math.h"
#include "register_timer.h"
#include "register_audio.h"

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

lua_lang_init::lua_lang_init(){}
lua_lang_init::~lua_lang_init(){}

static glfw_window m_window;

static core* c;
static keyboard* k;
static pointer* point;

static register_graphics* regGraphics;
static register_window* regWindow;
static register_input* regInput;
static register_math* regMath;
static register_timer* regTimer;
static register_audio* regAudio;

void lua_lang_init::create()
{
  m_L = luaL_newstate();

  luaL_openlibs(m_L);
  if(!m_L)
    LOG("Error: Could not load lua state!");

  k = new keyboard();
  point = new pointer();

  core* co = new core();
  co->create();
  regWindow = new register_window();
  regWindow->setDefaultWindow(true);

  regInput = new register_input();
  regTimer = new register_timer();
  regAudio = new register_audio();

  c = co;

  regWindow->setCore(c);

  regInput->setCore(c);
  regInput->setPointer(point);
  regInput->setKeyboard(k);

  regMath = new register_math();
  regMath->setCore(c);

  regTimer->setCore(c);
  regAudio->setCore(c);

  setCore(c);

  regGraphics = new register_graphics();
}

void lua_lang_init::makeDefaultWindow()
{
  //Did the user forgot to make his own window?
  if(regWindow->getDefaultWindow()){
    c->getWindow()->create("Simple - No Title!", 800, 600, false, false);
    c->getWindow()->setVSync(true); //don't melt the CPU
    c->getGLGraphics()->setViewport(0, 0, 800, 600);
  }
  c->getWindow()->initInput();
}

void lua_lang_init::setMainScript(const char* name)
{
  //Look for main.lua and execute it
  int error = luaL_dofile(m_L, name);
  if(error != 0)
    LOG("Error: Could not load main script " << name << " make sure your " << name << " is in the same folder with simple's executable.");

}

int lua_lang_init::quit(lua_State* L)
{
  c->getWindow()->setRunning(false);
  return 1;
}

static int getVersion(lua_State *L)
{
  LOG("simple - cracking bottles- version 0.2.3");
  return 1;
}

int lua_lang_init::initSimple(lua_State* L)
{
  int i;

  luaL_Reg reg[] = {
    { "getVersion",	getVersion },
    { "quit", quit },
    { 0, 0 },
  };

  luaL_newlib(L, reg);

  struct { char *name; int (*fn)(lua_State *L); } mods[] = {
    { "window", regWindow->registerModule  },
    { "timer", regTimer->registerModule },
    { "input", regInput->registerModule },
    { "audio", regAudio->registerModule },
    { 0, 0 },
  };

  for (i = 0; mods[i].name; i++) {
    mods[i].fn(L);
    lua_setfield(L, -2, mods[i].name);
  }
  return 1;
}

void lua_lang_init::registerFunctions()
{
  luaL_requiref(m_L, "simple", initSimple, 1);
  //math
  regMath->registerModule(m_L);
  //graphics
  regGraphics->registerShader(m_L);
  regGraphics->registerFont(m_L);
  regGraphics->registerTexture(m_L);
  regGraphics->registerBatch(m_L);
  regGraphics->registerGraphics(m_L);
}

void lua_lang_init::dumb()
{
  lua_close(m_L);

  SAFE_DELETE(k);
  SAFE_DELETE(point);
  SAFE_DELETE(c);
  SAFE_DELETE(regGraphics);
  SAFE_DELETE(regWindow);
  SAFE_DELETE(regInput);
  SAFE_DELETE(regMath);
  SAFE_DELETE(regTimer);
  SAFE_DELETE(regAudio);
}

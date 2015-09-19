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
static bool default_window;

static core* c;
static keyboard* k;
static pointer* point;

static register_graphics* regGraphics;

void lua_lang_init::create()
{
  m_L = luaL_newstate();

  luaL_openlibs(m_L);
  if(!m_L)
    LOG("Error: Could not load lua state!");

  default_window = true;
  core* co = new core();
  co->create();

  c = co;
  setCore(c);

  k = new keyboard();
  point = new pointer();

  regGraphics = new register_graphics();
}

void lua_lang_init::makeDefaultWindow()
{
  //Did the user forgot to make his own window?
  if(default_window){
    c->getWindow()->create("Simple - No Title!", 800, 600, false, false);
    c->getWindow()->setVSync(true); //don't melt the CPU
    c->getGLGraphics()->setViewport(0, 0, 800, 600);
  }
  c->getWindow()->initInput();
}

void lua_lang_init::setMainScript(const char* name)
{
  // //Look for main.lua and execute it
  int error = luaL_dofile(m_L, name);
  if(error != 0)
    LOG("Error: Could not load main script " << name << " make sure your " << name << " is in the same folder with simple's executable.");

}

bool lua_lang_init::callFunction(std::string name)
{
  return true;
}

static bool checkArguments(lua_State* L, int number)
{
  if(lua_gettop(L) < number)
    return false;
  return true;
}

//Errors handling
static bool isObjectError(lua_State *L, int spot, const char* what)
{
  if(!lua_isnumber(L, spot)){
    LOG("Error: " << what << " from location " << spot << " must be an object");
    return false;
  }
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

//Misc
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

static mat4* getMatrix4(LUA_INTEGER value)
{
  if(value == 0){
    LOG("mat4: " << value << " does not exist");
    return NULL;
  }

  return (mat4*)value;
}


int lua_lang_init::dumbTexture(lua_State *L)
{
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tointeger(L, 1);
  texture2D* tex;
  tex = getTexture2D(id);
  SAFE_DELETE(tex);
  return 1;
}

int lua_lang_init::dumbShader(lua_State *L)
{
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tointeger(L, 1);
  shader* s;
  s = getShader(id);
  if(s == getShader(id))
    SAFE_DELETE(s);
  return 1;
}

int lua_lang_init::dumbBatch(lua_State *L)
{
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tointeger(L, 1);
  batch2d* b;
  b = getBatch(id);
  SAFE_DELETE(b);
  return 1;
}


/*Short doc:

  lua_pushnumber = pushes a float to a destination
  lua_tonumber = recives a float form a destination
  lua_gettop = returns the number of parameters form a Lua function
  lua_isnumber(L,i),function = return is "i" is a number or not
  lua_type(L,i)
*/

/******* WINDOW ******/

int lua_lang_init::makeWindow(lua_State* L)
{

  default_window = false;
  luaL_checkstring(L, 1);
  const char* title = lua_tostring(L, 1);
  checkFloat(L, 2);
  checkFloat(L, 3);
  int width = lua_tonumber(L,2);
  int height = lua_tonumber(L, 3);
  bool fullscreen = false;
  bool resizable = false;
  int x = -1;
  int y = -1;
  //Optional
  if(lua_isnumber(L, 4))
    fullscreen = lua_tonumber(L, 4);
  if(lua_isnumber(L, 5))
    resizable = lua_tonumber(L, 5);

  if(lua_isnumber(L, 5) && lua_isnumber(L, 6)){
    x = lua_tonumber(L, 5);
    y = lua_tonumber(L, 6);
  }
  c->getWindow()->create(title, width, height, fullscreen, resizable);
  c->getWindow()->setPosition(x, y);
  return 1;
}

int lua_lang_init::getWindowSize(lua_State *L)
{
  float w = c->getWindow()->getWidth();
  float h = c->getWindow()->getHeight();

  lua_pushnumber(L, h);
  lua_pushnumber(L, w);

  return 2;
}

int lua_lang_init::getWindowWidth(lua_State *L)
{
  float w = c->getWindow()->getWidth();
  lua_pushnumber(L, w);
  return 1;
}

int lua_lang_init::getWindowHeight(lua_State *L)
{
  float h = c->getWindow()->getHeight();
  lua_pushnumber(L, h);
  return 1;
}

int lua_lang_init::setWindowVSync(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function makeWindow takes: 1)boolean");

  bool v = lua_toboolean(L, 1);
  c->getWindow()->setVSync(v);
  return 1;
}

int lua_lang_init::setWindowPosition(lua_State* L)
{
  checkFloat(L , 1);
  checkFloat(L , 2);
  int x = lua_tonumber(L, 1);
  int y = lua_tonumber(L, 2);
  c->getWindow()->setPosition(x, y);
  return 1;
}

int lua_lang_init::setWindowTitle(lua_State* L)
{
  luaL_checkstring(L, 1);
  const char* title = lua_tostring(L, 1);
  c->getWindow()->setTitle(title);
  return 1;
}

int lua_lang_init::getWindowFocus(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getWindowFocus takes no parameter");
  bool focused = c->getWindow()->isFocused();
  lua_pushboolean(L, focused);
  return 1;
}

int lua_lang_init::getWindowTicks(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getTicks takes no parameter");

  lua_pushnumber(L, c->getWindow()->getTicks());
  return 1;
}

int lua_lang_init::getMonitorSize(lua_State* L)
{
  lua_newtable(L);

  float x = c->getWindow()->getMonitorSize().x;
  float y = c->getWindow()->getMonitorSize().y;

  lua_pushnumber(L, y);
  lua_pushnumber(L, x);
  lua_settable(L, -3);
  return 1;
}


/*** END OF WINDOW *****/

/*** GL GRAPHICS *****/

int lua_lang_init::clearScreen(lua_State* L)
{
  checkFloat(L, 1);
  checkFloat(L, 2);
  checkFloat(L, 3);
  checkFloat(L, 4);
  float r = lua_tonumber(L, 1);
  float g = lua_tonumber(L, 2);
  float b = lua_tonumber(L, 3);
  float a = lua_tonumber(L, 4);
  float scale = 1.0f / 255.0f;
  c->getGLGraphics()->clearScreen(scale * r, scale * g, scale * b, scale * a);

  return 1;
}

int lua_lang_init::setViewport(lua_State *L)
{
  checkFloat(L, 1);
  checkFloat(L, 2);
  checkFloat(L, 3);
  checkFloat(L, 4);
  int x = lua_tonumber(L, 1);
  int y = lua_tonumber(L, 2);
  int w = lua_tonumber(L, 3);
  int h = lua_tonumber(L, 4);
  c->getGLGraphics()->setViewport(x, y, w, h);
  return 1;
}

/*** END OF GL GRAPHICS *****/

/*** MATHS *****/

/*** END OF MATHS *****/

/*** SOUND *****/

int lua_lang_init::loadSound(lua_State *L)
{
  ogg_player* ogg_p = new ogg_player();
  luaL_checkstring(L, 1);
  const char* path = lua_tostring(L, 1);
  ogg_p->create(path);

  pushPointer(L, ogg_p);
  return 1;
}

int lua_lang_init::playSound(lua_State *L)
{
  ogg_player* ogg;
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tonumber(L, 1);
  float volume = 1.0f;
  float pitch = 1.0f;
  if(lua_isnumber(L, 2)){
    luaL_checknumber(L, 2);
    volume = lua_tonumber(L, 2);
  }
  if(lua_isnumber(L, 3)){
    luaL_checknumber(L, 3);
    pitch = lua_tonumber(L, 3);
  }
  ogg = getOGG(id);
  if(ogg == getOGG(id))
    ogg->play(volume, pitch);
  return 1;
}

/*** END OF SOUND *****/

/*** MOUSE *****/
int lua_lang_init::getPointerX(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getPointerX takes no parameter");

  lua_pushnumber(L, c->getWindow()->getPointX());

  return 1;
}

int lua_lang_init::getPointerY(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getPointerY takes no parameter");
  lua_pushnumber(L, c->getWindow()->getPointY());
  return 1;
}

int lua_lang_init::getPointer(lua_State *L)
{
  float x = c->getWindow()->getPointerPosition().x;
  float y = c->getWindow()->getPointerPosition().y;

  lua_pushnumber(L, x);
  lua_pushnumber(L, y);

  return 2;
}

int lua_lang_init::isPointerPressed(lua_State *L)
{
  luaL_checkstring(L, 1);
  const char* button = lua_tostring(L, 1);
  if(point->isPressed(button))
    return 1;
  else
    return 0;
  return 0;
}

int lua_lang_init::isPointerReleased(lua_State *L)
{
  luaL_checkstring(L, 1);
  const char* button = lua_tostring(L, 1);
  if(point->isReleased(button))
    return 1;
  else
    return 0;
  return 0;
}


/*** END OF MOUSE *****/


/*** UTILS *****/
int lua_lang_init::getDeltaTime(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getDeltaTime takes no parameters");
  lua_pushnumber(L, c->getWindow()->getDeltaTime());
  return 1;
}

int lua_lang_init::getFPS(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getFPS takes no parameters");
  float FPS = c->getWindow()->getFPS();
  lua_pushnumber(L, FPS);
  return 1;
}

int lua_lang_init::quit(lua_State* L)
{
  c->getWindow()->setRunning(false);
  return 1;
}

int lua_lang_init::isKeyDown(lua_State* L)
{
  luaL_checkstring(L, 1);
  const char* key = lua_tostring(L, 1);
  if(k->isKeyDown(key))
    return 1;
  else
    return 0;
  return 0;
}

int lua_lang_init::isKeyUp(lua_State* L)
{
  luaL_checkstring(L, 1);
  const char* key = lua_tostring(L, 1);
  if(k->isKeyUp(key))
    return 1;
  else
    return 0;
  return 0;
}

/*** END OF UTILS *****/

static int getVersion(lua_State *L)
{
  LOG("simple - cracking bottles- version 0.2.2");
  return 1;
}

luaL_Reg lua_lang_init::regAudioFuncs[] =
{
  {"newSound", loadSound},
  {NULL, NULL}
};

int lua_lang_init::audio_register(lua_State* state)
{
  luaL_Reg AudioMetatableFuncs[] = {
    {"play", playSound},
    {NULL, NULL}
  };

  return 1;
}

int lua_lang_init::input_register(lua_State* state)
{
  luaL_Reg regInputFuncs[] =
    {
      {"getPointerX", getPointerX},
      {"getPointerY", getPointerY},
      {"getPointer", getPointer},
      {"isKeyDown", isKeyDown},
      {"isKeyUp", isKeyUp},
      {"pressed", isPointerPressed},
      {"released", isPointerReleased},
    };

  return 1;
}

int lua_lang_init::math_register(lua_State* state)
{
  luaL_Reg regMathFuncs[] =
    {
      {"setOrtho", setOrthoView},
      {NULL, NULL}
    };

  return 1;
}

int lua_lang_init::timer_register(lua_State* state)
{
  luaL_Reg regTimerFuncs[] =
    {
      {"getFPS", getFPS},
      {"delta", getDeltaTime},
      {"getTicks", getWindowTicks},
      {NULL, NULL}
    };
  return 1;
}

int lua_lang_init::window_register(lua_State* state)
{
  luaL_Reg regWindowFuncs[] =
    {
      {"create", makeWindow},
      {"setPosition", setWindowPosition},
      {"setTitle", setWindowTitle},
      {"getMonitorSize", getMonitorSize},
      {"getSize", getWindowSize },
      {"getWidth", getWindowWidth },
      {"getHeight", getWindowHeight },
      {"getFocus", getWindowFocus },
      {"setVSync", setWindowVSync },
      {NULL, NULL}
    };

  luaL_newlib(state, regWindowFuncs);
  luaL_Reg WindowMetatableFuncs[] = {
    {NULL, NULL}
  };
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
    { "window", window_register  },
    { "graphics", regGraphics->registerModule  },
    //{ "timer", timer_register },
    // { "input", input_register },
    // { "math", math_register },
    // { "audio", audio_register },
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
}

void lua_lang_init::dumb()
{
  lua_close(m_L);

  SAFE_DELETE(k);
  SAFE_DELETE(point);
  SAFE_DELETE(c);
  SAFE_DELETE(regGraphics);
}

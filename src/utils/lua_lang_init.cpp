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

#include "../utils/definitions.h"
#include "../window/glfw_window.h"
#include "../graphics/gl_graphics.h"
#include "core.h"

using namespace simple;
using namespace simple::lang;
using namespace simple::graphics;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

lua_lang_init::lua_lang_init(){}
lua_lang_init::~lua_lang_init(){}

static glfw_window m_window;
static bool default_window;

static core* c;

void lua_lang_init::create()
{
  m_L = luaL_newstate();
  luaL_openlibs(m_L);
  if(!m_L)
    LOG("Error: Could not load lua state!");
  //Create the main window 
  default_window = true;
  simple_core = new core();
  simple_core->create();

  c = simple_core;
}

void lua_lang_init::makeDefaultWindow()
{
  //Did the user forgot to make his own window?
  if(default_window){
    c->getWindow()->create("Simple - No Title!", 800, 600, false);
    c->getWindow()->setVSync(true); //don't melt the CPU
    c->getGLGraphics()->setViewport(0, 0, 800, 600);
  }
}

void lua_lang_init::setMainScript(const char* name)
{
  //Look for main.lua and execute it
  int error = luaL_dofile(m_L, name);
  if(error != 0)
    LOG("Error: Could not load main script " << name);
}

/*
  int lua_lang_init::test(float x, float y)
  {
  int z;
  lua_getglobal(m_L, "test");
  lua_pushnumber(m_L, x);
  lua_pushnumber(m_L, y);
  lua_call(m_L, 2, 1);
  z = (int)lua_tointeger(m_L, -1);
  lua_pop(m_L, 1);
  return z;
  }*/

bool lua_lang_init::callFunction(const char* name)
{
  lua_getglobal(m_L, name);
  if(!lua_isfunction(m_L, 1)){
    LOG("Error: function " << name << " should have been created in your main.lua file!");
  }
  lua_call(m_L, 0, 0);

  return true;
}

static bool checkArguments(lua_State* L, int number)
{
  if(lua_gettop(L) < number)
    return false;
  return true;
}

//Errors handling
static bool isIntError(lua_State *L, int spot, const char* what)
{
  if(!lua_isnumber(L, spot)){
    LOG("Error: " << what << " from location " << spot << " must be a number");
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

static bool isBooleanError(lua_State *L, int spot, const char* what)
{
  if(!lua_isboolean(L, spot) || lua_isnumber(L, spot)){
    LOG("Error: " << what << " from location " << spot << " must be a boolean");
    return false;
  }
  return true;
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
  if(lua_gettop(L) < 5)
    LOG("Warning: function makeWindow takes: 1)title 2)width 3)height 4) boolean fullscreen");

  const char* title = lua_tostring(L, 1);
  isStringError(L, 1, "makeWindow -> title");
  int width = lua_tonumber(L, 2);
  isIntError(L, 2, "makeWindow -> width");
  int height = lua_tonumber(L, 3);
  isIntError(L, 3, "makeWindow -> height");
  bool fullscreen = false;
  int x = -1; //set a default position for our window
  int y = -1;
  //Optional
  if(lua_tonumber(L, 4)){
    fullscreen = lua_tonumber(L, 4);
  }

  if(lua_tonumber(L, 5) && lua_tonumber(L, 6)){
    x = lua_tonumber(L, 5);
    y = lua_tonumber(L, 6);
  }
  isIntError(L, 6, "makeWindow ->(optional)positionY");
  isIntError(L, 5, "makeWindow ->(optional)positionX");

  if(isBooleanError(L, 4, "makeWindow ->(optional)fullscreen"))
    c->getWindow()->create(title, width, height, false);
  else
    c->getWindow()->create(title, width, height, true);

  c->getWindow()->setPosition(x, y);
  return 1;
}

int lua_lang_init::setWindowVSync(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function makeWindow takes: 1)boolean");

  bool v = lua_toboolean(L, 1);
  isBooleanError(L, 1, "setWindowVSync -> vsync");
  c->getWindow()->setVSync(v);
  return 1;
}

int lua_lang_init::setWindowPosition(lua_State* L)
{
  if(checkArguments(L, 3))
    LOG("Warning: function setWindowPosition takes: 1)x coord 2) y coord");

  int x = lua_tonumber(L, 1);
  isIntError(L, 1, "setWindowPosition -> x");
  int y = lua_tonumber(L, 2);
  isIntError(L, 2, "setWindowPosition -> y");
  c->getWindow()->setPosition(x, y);
  return 1;
}

int lua_lang_init::setWindowTitle(lua_State* L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function setTitle takes: 1) string");

  const char* title = lua_tostring(L, 1);
  isStringError(L, 1, "setWindowTitle -> title");
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

  //if(checkArguments(L, 3))
  //LOG("Warning: function clearScreen takes 3 parameters(RGB) and one optional alpha");
  float r = lua_tonumber(L, 1);
  isIntError(L, 1, "clearScreen -> red");
  float g = lua_tonumber(L, 2);
  isIntError(L, 2, "clearScreen -> green");
  float b = lua_tonumber(L, 3);
  isIntError(L, 3, "clearScreen -> blue");
  float a = lua_tonumber(L, 4); //TODO do more checks about this
  isIntError(L, 4, "clearScreen -> opacity");

  c->getGLGraphics()->clearScreen(r, g, b, a);

  return 1;
}

int lua_lang_init::setViewport(lua_State *L)
{
  if(checkArguments(L, 5))
    LOG("Warning: function setViewport takes: 1) x 2) y 3)width 4) height");

  int x = lua_tonumber(L, 1);
  isIntError(L, 1, "clearScreen -> x");
  int y = lua_tonumber(L, 2);
  isIntError(L, 2, "clearScreen -> y");
  int w = lua_tonumber(L, 3);
  isIntError(L, 3, "clearScreen -> width");
  int h = lua_tonumber(L, 4);
  isIntError(L, 4, "clearScreen -> height");

  c->getGLGraphics()->setViewport(x, y, w, h);

}

/*** END OF GL GRAPHICS *****/

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

/*** END OF UTILS *****/

void lua_lang_init::registerFunctions()
{
  //WINDOW
  lua_register(m_L, "simple_makeWindow", makeWindow);
  lua_register(m_L, "simple_setWindowPosition", setWindowPosition);
  lua_register(m_L, "simple_setWindowTitle", setWindowTitle);
  lua_register(m_L, "simple_getMonitorSize", getMonitorSize);
  lua_register(m_L, "simple_getWindowFocus", getWindowFocus);
  lua_register(m_L, "simple_getWindowTicks", getWindowTicks);
  lua_register(m_L, "simple_setWindowVSync", setWindowVSync);
  //MOUSE
  lua_register(m_L, "simple_getPointerX", getPointerX);
  lua_register(m_L, "simple_getPointerY", getPointerY);

  //GL Graphics
  lua_register(m_L, "simple_clearScreen", clearScreen);
  lua_register(m_L, "simple_setViewport", setViewport);
  //UTILS
  lua_register(m_L, "simple_getDeltaTime", getDeltaTime);
  lua_register(m_L, "simple_getFPS", getFPS);
}

//TODO
//ADD batch2d renderer and textures to lua
void lua_lang_init::dumb()
{
  lua_close(m_L);
}

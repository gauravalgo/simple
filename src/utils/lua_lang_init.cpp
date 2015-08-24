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

using namespace simple;
using namespace simple::lang;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

lua_lang_init::lua_lang_init(){}
lua_lang_init::~lua_lang_init(){}

static glfw_window* m_window;
static bool default_window;

void lua_lang_init::create()
{
   m_L = luaL_newstate();
  // load Lua libraries
  static const luaL_Reg lualibs[] ={
    { "base", luaopen_base },
    { NULL, NULL}
  };
  const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(m_L);
        lua_settop(m_L, 0);
    }
  if(!m_L)
    LOG("Error: Could not load lua state!");

  //Create the main window 
  default_window = true;
  m_window = new glfw_window();
}

void lua_lang_init::setMainScript(const char* name)
{
   //Look for main.lua and execute it
  luaL_dofile(m_L, name);

  //Get the init function if there's one
  lua_getglobal(m_L, "init");
}

static bool checkArguments(lua_State* L, int number)
{
  if(lua_gettop(L) < number || lua_gettop(L) > number)
    return false;
  return true;
}

glfw_window* lua_lang_init::getWindow()
{
  return m_window;
}

/******* WINDOW ******/

int lua_lang_init::makeWindow(lua_State* L)
{
  default_window = false;
 
  if(checkArguments(L, 4))
    LOG("Warning: function makeWindow takes: 1)title 2)width 3)height");

  const char* title = lua_tostring(L, 1);
  int width = lua_tonumber(L, 2);
  int height = lua_tonumber(L, 3);
  m_window->create(title, width, height);
  
  return 1;
}

int lua_lang_init::setWindowPosition(lua_State* L)
{
  if(checkArguments(L, 3))
    LOG("Warning: function setWindowPosition takes: 1)x coord 2) y coord");

  int x = lua_tonumber(L, 1);
  int y = lua_tonumber(L, 1);

  m_window->setPosition(x, y);
  
  return 1;
}

int lua_lang_init::setWindowTitle(lua_State* L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function setTitle takes: 1) string");

  const char* title = lua_tostring(L, 1);

  m_window->setTitle(title);
  
  return 1;
}

int lua_lang_init::getWindowFocus(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getWindowFocus takes no parameter");

  lua_pushboolean(L, m_window->isFocused());
  
  return 1;
}

int lua_lang_init::getWindowTicks(lua_State* L)
{
  if(checkArguments(L, 1))
    LOG("Warning: function getTicks takes no parameter");

  lua_pushnumber(L, m_window->getTicks());
  
  return 1;
}


//TODO
int lua_lang_init::getMonitorSize(lua_State* L)
{
  lua_newtable(L);
  
  if(checkArguments(L, 0))
    LOG("Warning: function getMonitorSize does not take any parameters !");

  int x = m_window->getMonitorSize().x;
  int y = m_window->getMonitorSize().y;
  
  lua_pushnumber(L, x); 
  lua_pushnumber(L, y);

  lua_settable(L, -3);
  lua_pcall(L,1,0,0);
  
  return 1;
}


/*** END OF WINDOW *****/

/*** MOUSE *****/
int lua_lang_init::getPointerX(lua_State* L)
{
  if(checkArguments(L, 1))
   LOG("Warning: function getPointerX takes no parameter");

  lua_pushnumber(L, m_window->getPointX());

  return 1;
}

int lua_lang_init::getPointerY(lua_State* L)
{
  if(checkArguments(L, 1))
   LOG("Warning: function getPointerY takes no parameter");

  lua_pushnumber(L, m_window->getPointY());

  return 1;
}

/*** END OF MOUSE *****/


/*** END OF UTILS *****/



/*** END OF UTILS *****/


void lua_lang_init::registerFunctions()
{
  //WINDOW
  lua_register(m_L, "makeWindow", makeWindow);
  lua_register(m_L, "setWindowPosition", setWindowPosition);
  lua_register(m_L, "setWindowTitle", setWindowTitle);
  lua_register(m_L, "getMonitorSize", getMonitorSize);
  lua_register(m_L, "getWindowFocus", getWindowFocus);
  lua_register(m_L, "getWindowTicks", getWindowTicks);
  

  //MOUSE
  lua_register(m_L, "getPointerX", getPointerX);
  lua_register(m_L, "getPointerY", getPointerY);

  //UTILS

   
}

//TODO
//LEARN how tables work in C
//ADD UPDATE/DRAW/INIT method
//default window

void lua_lang_init::dumb()
{
  lua_close(m_L);
}

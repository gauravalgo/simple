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
#include "../graphics/texture2D.h"
#include "../graphics/batch2d.h"
#include "../graphics/shader.h"
#include "../graphics/default_shaders.h"
#include "../maths/mat4.h"
#include "../input/keyboard.h"
#include "../input/pointer.h"
#include "core.h"

using namespace simple;
using namespace simple::lang;
using namespace simple::graphics;
using namespace simple::maths;
using namespace simple::input;

#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

lua_lang_init::lua_lang_init(){}
lua_lang_init::~lua_lang_init(){}

static glfw_window m_window;
static bool default_window;

static core* c;
static keyboard* k;
static pointer* point;

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
}

void lua_lang_init::makeDefaultWindow()
{
  //Did the user forgot to make his own window?
  if(default_window){
    c->getWindow()->create("Simple - No Title!", 800, 600, false);
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

bool lua_lang_init::callFunction(const char* name)
{
   lua_getglobal(m_L, name);
  //if(!lua_isfunction(m_L, 1)){
    //LOG("Error: function " << name << " should have been created in your main.lua file!");
  //}
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

static shader* getShader(LUA_INTEGER value)
{
  if(value == 0){
    LOG("shader: " << value << " does not exist");
    return NULL;
  }

  return (shader*)value;
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
  int x = -1; //set a default position for our window
  int y = -1;
  //Optional
  if(lua_isnumber(L, 4)){
    fullscreen = lua_tonumber(L, 4);
  }
  if(lua_isnumber(L, 5) && lua_isnumber(L, 6)){
    x = lua_tonumber(L, 5);
    y = lua_tonumber(L, 6);
  }
  c->getWindow()->create(title, width, height, fullscreen);
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

  c->getGLGraphics()->clearScreen(r, g, b, a);

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


/*** GRAPHICS *****/

int lua_lang_init::loadTexture(lua_State *L)
{
  texture2D* tex = new texture2D();

  const char* path = lua_tostring(L, 1);
  isStringError(L, 1, "loadTexture -> file path");
  tex->create(path);
  pushPointer(L, tex);
  return 1;
}

int lua_lang_init::bindTexture(lua_State *L)
{
  texture2D* tex;
  checkInteger(L, 1);
  float id = lua_tointeger(L, 1);
  tex = getTexture2D(id);
  if(tex == getTexture2D(id))
    getTexture2D(id)->bind();

  return 1;
}

int lua_lang_init::unBindTexture(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function bindTexture takes: 1) a texture");

  texture2D* tex;
  checkInteger(L, 1);
  int id = lua_tointeger(L, 1);
  tex = getTexture2D(id);
  if(tex == getTexture2D(id))
    tex->unbind();
  return 1;
}

int lua_lang_init::createShader(lua_State *L)
{
  shader* s = new shader();
  //custom shader
  luaL_checkstring(L, 1);
  luaL_checkstring(L, 2);
  isStringError(L, 1 , "createShader -> vertex shader expected");
  isStringError(L, 2 , "createShader -> fragment shader expected");
  const char* vertex = lua_tostring(L, 1);
  const char* fragment = lua_tostring(L, 2);
  s->create(vertex, fragment);

  pushPointer(L, s);
  return 1;
}

int lua_lang_init::createDefaultShader(lua_State* L)
{
  shader* s = new shader();

  default_shaders df;

#ifndef EMSCRIPTEN
     s->create(df.gl_texture_vertex.c_str(), df.gl_texture_fragment.c_str());
#endif
#ifdef EMSCRIPTEN
     s->create(df.gl_es_texture_vertex.c_str(), df.gl_es_texture_fragment.c_str());
#endif

  pushPointer(L, s);
  return 1;
}

int lua_lang_init::bindShader(lua_State *L)
{
  shader* s;
  checkInteger(L, 1);
  int id = lua_tointeger(L, 1);
  s = getShader(id);
  if(s == getShader(id))
    s->bind();
  return 1;
}


int lua_lang_init::unBindShader(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: unBindShader takes: 1) shader ");

  shader* s;
  checkInteger(L, 1);
  int id = lua_tointeger(L, 1);
  s = getShader(id);
  if(s == getShader(id))
    s->unbind();
  return 1;
}

int lua_lang_init::setOrthoView(lua_State *L)
{
  if(checkArguments(L, 9))
    LOG("Warning: setOrthoView takes : 1) left 2)right 3)bottom 4)top 5)near 6)far 7)shader");

  mat4  projection;
  projection.setToIdentity();

  float left = lua_tonumber(L, 1);
  float right = lua_tonumber(L, 2);
  float bottom = lua_tonumber(L, 3);
  float top = lua_tonumber(L, 4);
  float near = lua_tonumber(L, 5);
  float far = lua_tonumber(L, 6);

  //test this inside an update method and see what happens
  projection = projection.setOrtho(left, right, bottom, top, near, far);
  shader* s;
  int shid = lua_tointeger(L, 7);

  s = getShader(shid);
  if(s == getShader(shid))
    s->sendUniformLocation("proj", projection);
  return 1;
}

//TODO later
int lua_lang_init::sendShaderUniformLocation(lua_State *L)
{
  if(checkArguments(L, 4))
    LOG("Warning: sendShaderUniformLocation takes: 1) shader 2) location 3) matrix");

  shader* s;
  int id = lua_tointeger(L, 1);
  const char* location = lua_tostring(L, 2);
  isStringError(L, 2, "sendShaderUniformLocation -> location string expected");
  float data = lua_tonumber(L, 3);
  s = getShader(id);
  if(s == getShader(id)){
    s->sendUniformLocation(location, data);
  }

  return 1;
}

int lua_lang_init::createBatch(lua_State *L)
{
  shader* s;
  batch2d* batch;
  isObjectError(L, 1, "makeBatch -> shader");
  lua_Integer shID = lua_tointeger(L, 1);
  s = getShader(shID);
  if(s == getShader(shID)){
    batch = new batch2d(s, 9000);
    batch->create();
    pushPointer(L, batch);
  }
  return 1;
}

int lua_lang_init::renderMesh(lua_State *L)
{
  isObjectError(L, 1, "renderMesh -> batch");
  lua_Integer id = lua_tointeger(L, 1);
  batch2d* b;
  b = getBatch(id);
  b->renderMesh();
  return 1;
}

int lua_lang_init::beginBatch(lua_State *L)
{
  batch2d* batch;
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tointeger(L, 1);
  batch = getBatch(id);
  if(batch == getBatch(id))
    batch->begin();

  return 1;
}

int lua_lang_init::drawBatch(lua_State *L)
{
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tointeger(L, 1);
  batch2d* batch;
  batch = getBatch(id);
  if(batch == getBatch(id)){
    luaL_checknumber(L, 2);
    luaL_checknumber(L, 3);
    luaL_checknumber(L, 4);
    luaL_checknumber(L, 5);

    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 3);
    float w = lua_tonumber(L, 4);
    float h = lua_tonumber(L, 5);

    float rotation = 0;
    if(lua_isnumber(L, 6)){
      luaL_checknumber(L, 6);
      rotation = lua_tonumber(L, 6);
    }
    if(rotation == 0){
      batch->draw(x, y, w, h);
    }else{
      float originX = w * 0.5f;
      float originY = h * 0.5f;
      if(lua_isnumber(L, 7) && lua_isnumber(L, 8)){
        luaL_checknumber(L, 7);
        luaL_checknumber(L, 8);

        originX = lua_tonumber(L, 7);
        originY = lua_tonumber(L, 8);
      }
      float r = 1;
      float g = 1;
      float b = 1;
      float a = 1;
      if(lua_isnumber(L, 9) && lua_isnumber(L, 10) && lua_isnumber(L, 11)){
        luaL_checknumber(L, 9);
        luaL_checknumber(L, 10);
        luaL_checknumber(L, 11);
        if(lua_isnumber(L, 12)){
          luaL_checknumber(L, 12);
          a = lua_tonumber(L, 12);
        }

        r = lua_tonumber(L, 9);
        g = lua_tonumber(L, 10);
        b = lua_tonumber(L, 11);
      }
      batch->draw(x, y, w, h, rotation, originX, originY, r, g, b, a);
    }
  }

  return 1;
}

int lua_lang_init::endBatch(lua_State* L)
{
  batch2d* batch;
  luaL_checkinteger(L, 1);
  lua_Integer id = lua_tointeger(L, 1);
  batch = getBatch(id);
  if(batch == getBatch(id))
    batch->end();

  return 1;
}

/*** END OF GRAPHICS *****/

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
  LOG("Simple - cracking bottles- version 0.2.1");
  return 1;
}

int lua_lang_init::initWindow(lua_State *L)
{
  luaL_Reg reg[] = {
    {"create", makeWindow},
    {"setPosition", setWindowPosition},
    {"setTitle", setWindowTitle},
    {"getMonitorSize", getMonitorSize},
    {"getSize", getWindowSize },
    {"getWidth", getWindowWidth },
    {"getHeight", getWindowHeight },
    {"getFocus", getWindowFocus},
    {"setVSync", setWindowVSync},
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}

int lua_lang_init::initTime(lua_State *L)
{
  luaL_Reg reg[] = {
    {"getFPS", getFPS},
    {"delta", getDeltaTime},
    {"getTicks", getWindowTicks},
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}


int lua_lang_init::initInput(lua_State *L)
{
  luaL_Reg reg[] = {
    {"getPointerX",getPointerX},
    {"getPointerY",getPointerY},
    {"getPointer", getPointer},
    {"isKeyDown", isKeyDown},
    {"isKeyUp", isKeyUp},
    {"pressed", isPointerPressed},
    {"released", isPointerReleased},
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}

int lua_lang_init::initMath(lua_State *L)
{
  luaL_Reg reg[] = {
    {"setOrtho",setOrthoView},
    {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}


int lua_lang_init::initGraphics(lua_State *L)
{
  luaL_Reg reg[] = {
    {"loadTexture", loadTexture},
    {"bindTexture", bindTexture},
    {"unBindTexture", unBindTexture},
    {"newShader", createShader},
    {"newDefaultShader", createDefaultShader},
    {"bindShader", bindShader},
    {"unBindShader", unBindShader},
    {"sendShaderUniformLocation", sendShaderUniformLocation},
    {"newBatch", createBatch},
    {"renderMesh", renderMesh},
    {"beginBatch", beginBatch},
    {"endBatch", endBatch},
    {"drawBatch", drawBatch},
    {"clearScreen", clearScreen},
    {"setViewport", setViewport},
    {0, 0},
  };
  luaL_newlib(L, reg);
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
    { "window", initWindow  },
    { "graphics", initGraphics  },
    { "time", initTime },
    { "input", initInput },
    { "math", initMath },
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

  lua_register(m_L, "simple_dumpTexture", dumbTexture);
  lua_register(m_L, "simple_dumpShader", dumbShader);
  lua_register(m_L, "simple_dumpBatch", dumbBatch);
}

void lua_lang_init::dumb()
{
  lua_close(m_L);
  SAFE_DELETE(k);
  SAFE_DELETE(point);
  SAFE_DELETE(c);
}

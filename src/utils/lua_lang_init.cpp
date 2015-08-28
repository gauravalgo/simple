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
#include "core.h"

using namespace simple;
using namespace simple::lang;
using namespace simple::graphics;
using namespace simple::maths;

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
    LOG("Error: Could not load main script " << name << " make sure your " << name << " is in the same folder with simple exe.");
}

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

static bool isObjectError(lua_State *L, int spot, const char* what)
{
  if(!lua_isnumber(L, spot)){
    LOG("Error: " << what << " from location " << spot << " must be an object");
    return false;
  }
  return true;
}


static bool isFloatError(lua_State *L, int spot, const char* what)
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
  int width = checkFloat(L, 2);
  isIntError(L, 2, "makeWindow -> width");
  int height = checkFloat(L, 3);
  isIntError(L, 3, "makeWindow -> height");
  bool fullscreen = false;
  int x = -1; //set a default position for our window
  int y = -1;
  //Optional
  if(lua_tonumber(L, 4)){
    fullscreen = lua_tonumber(L, 4);
  }

  if(checkFloat(L, 5) && checkFloat(L, 6)){
    x = checkFloat(L, 5);
    y = checkFloat(L, 6);
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

  int x = checkFloat(L, 1);
  isIntError(L, 1, "setWindowPosition -> x");
  int y = checkFloat(L, 2);
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
  float r = checkFloat(L, 1);
  isIntError(L, 1, "clearScreen -> red");
  float g = checkFloat(L, 2);
  isIntError(L, 2, "clearScreen -> green");
  float b = checkFloat(L, 3);
  isIntError(L, 3, "clearScreen -> blue");
  float a = checkFloat(L, 4);
  isIntError(L, 4, "clearScreen -> opacity");

  c->getGLGraphics()->clearScreen(r, g, b, a);

  return 1;
}

int lua_lang_init::setViewport(lua_State *L)
{
  if(checkArguments(L, 5))
    LOG("Warning: function setViewport takes: 1) x 2) y 3)width 4) height");

  int x = checkFloat(L, 1);
  isIntError(L, 1, "clearScreen -> x");
  int y = checkFloat(L, 2);
  isIntError(L, 2, "clearScreen -> y");
  int w = checkFloat(L, 3);
  isIntError(L, 3, "clearScreen -> width");
  int h = checkFloat(L, 4);
  isIntError(L, 4, "clearScreen -> height");

  c->getGLGraphics()->setViewport(x, y, w, h);

}

/*** END OF GL GRAPHICS *****/

/*** MATHS *****/

/*** END OF MATHS *****/


/*** GRAPHICS *****/

int lua_lang_init::makeTexture(lua_State *L)
{
  texture2D tex;

  return 1;
}

int lua_lang_init::loadTexture(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function loadTexture takes: 1) string(file path)");

  texture2D* tex = new texture2D();

  const char* path = lua_tostring(L, 1);
  isStringError(L, 1, "loadTexture -> file path");
  tex->create(path);
  pushPointer(L, tex);
  return 1;
}

int lua_lang_init::bindTexture(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function bindTexture takes: 1) a texture");

  texture2D* tex = new texture2D();
  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "bindTexture -> texture to bind to");
  tex = getTexture2D(id);
  if(tex == getTexture2D(id))
    getTexture2D(id)->bind();
  return 1;
}

int lua_lang_init::unBindTexture(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: function bindTexture takes: 1) a texture");

  texture2D* tex = new texture2D();
  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "unBindTexture -> texture to unbind to");
  tex = getTexture2D(id);
  if(tex == getTexture2D(id))
    tex->unbind();
  return 1;
}

int lua_lang_init::createShader(lua_State *L)
{
  if(checkArguments(L, 3))
    LOG("Warning: createShader takes: 1) vertex string 2) fragment string");

  shader* s = new shader();
  if(!lua_tostring(L,1) && !lua_tostring(L, 2)){
    //Put a custom shader
    default_shaders df;
    s->create(df.texture_vertex.c_str(),df.texture_fragment.c_str());
  }else if(lua_tostring(L,1) && !lua_tostring(L,2)){
      LOG("Warning: (optional)parameters are: 1) vertex shader 2) fragment shader");
  }else{
    const char* vertex = lua_tostring(L, 1);
    isStringError(L, 1 , "createShader -> vertex shader expected");
    const char* fragment = lua_tostring(L, 2);
    isStringError(L, 2 , "createShader -> fragment shader expected");
    s->create(vertex, fragment);
  }

  pushPointer(L, s);
  return 1;
}

int lua_lang_init::bindShader(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: bindShader takes: 1) shader ");

  shader* s = new shader();
  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "bindshader -> shader to bind to expected");
  s = getShader(id);
  if(s == getShader(id))
    s->bind();
  return 1;
}


int lua_lang_init::unBindShader(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: unBindShader takes: 1) shader ");

  shader* s = new shader();
  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "unBindShader -> shader to unbind to expected");
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

  float left = checkFloat(L, 1);
  isFloatError(L, 1, "setOrthoview -> left");
  float right = checkFloat(L, 2);
  isFloatError(L, 2, "setOrthoview -> right");
  float bottom = checkFloat(L, 3);
  isFloatError(L, 3, "setOrthoview -> bottom");
  float top = checkFloat(L, 4);
  isFloatError(L, 4, "setOrthoview -> top");
  float near = checkFloat(L, 5);
  isFloatError(L, 5, "setOrthoview -> near");
  float far = checkFloat(L, 6);
  isFloatError(L, 6, "setOrthoview -> far");

  //test this inside an update method and see what happens
  projection = projection.setOrtho(left, right, bottom, top, near, far);
  shader* s = new shader();
  lua_Integer shid = lua_tointeger(L, 7);
  isIntError(L, 7, "setOrthoview -> shader");
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

  shader* s = new shader();
  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "sendShaderUniformLocation -> shader object expected");
  const char* location = lua_tostring(L, 2);
  isStringError(L, 2, "sendShaderUniformLocation -> location string expected");
  float data = lua_tonumber(L, 3);
  isFloatError(L, 3, "sendShaderUniformLocation -> matrix data expected");
  s = getShader(id);
  if(s == getShader(id)){
    s->sendUniformLocation(location, data);
  }

  return 1;
}

int lua_lang_init::createBatch(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: createBatch takes: 1) shader");

  shader* s = new shader();
  isObjectError(L, 1, "createBatch -> shader");
  lua_Integer shID = checkInteger(L, 1);
  s = getShader(shID);
  batch2d* batch;
  if(lua_tointeger(L, 2)){
    int size = checkInteger(L, 2);
    batch = new batch2d(s, size);
  }else
    batch = new batch2d(s, 4000);
  batch->create();
  pushPointer(L, batch);
  return 1;
}

int lua_lang_init::renderMesh(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: renderMesh takes: 1) batch");

  isObjectError(L, 1, "renderMesh -> batch");
  lua_Integer id = lua_tointeger(L, 1);
  batch2d* b = new batch2d();
  b = getBatch(id);
  b->renderMesh();
  return 1;
}

int lua_lang_init::beginBatch(lua_State *L)
{
  if(checkArguments(L, 2))
    LOG("Warning: beginBatch takes 1) batch");

  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "beginBatch takes 1) batch");
  batch2d* batch = new batch2d();
  batch = getBatch(id);
  if(batch == getBatch(id))
    batch->begin();

  return 1;
}

int lua_lang_init::drawBatch(lua_State *L)
{
  if(checkArguments(L, 6))
    LOG("Waring: drawBatch takes: 1) batch 2) x coord 3) y coord 4) width 5) height");
  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "drawBatch -> batch expected");
  batch2d* batch = new batch2d();
  batch = getBatch(id);
  if(batch == getBatch(id)){
    float x = checkFloat(L, 2);
    isIntError(L, 2, "drawBatch -> x coord expected");
    float y = checkFloat(L, 3);
    isIntError(L, 3, "drawBatch -> y coord expected");
    float w = checkFloat(L, 4);
    isIntError(L, 4, "drawBatch -> w size expected");
    float h = checkFloat(L, 5);
    isIntError(L, 5, "drawBatch -> h size expected");
    batch->draw(x, y, w, h);
  }
  return 1;
}

int lua_lang_init::endBatch(lua_State* L)
{
  if(checkArguments(L, 2))
    LOG("Warning: endBatch takes 1) batch");

  lua_Integer id = lua_tointeger(L, 1);
  isIntError(L, 1, "endBatch takes 1) batch");
  batch2d* batch = new batch2d();
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
  lua_newtable(L);
  float x = c->getWindow()->getPointerPosition().x;
  float y = c->getWindow()->getPointerPosition().y;
  lua_pushnumber(L, x);
  lua_pushnumber(L, y);
  lua_settable(L, -3);
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
//TODO make this damn thing work!
int lua_lang_init::initGraphics(lua_State* L)
{
  luaL_Reg reg[] = {
    { "makeTexture",	makeTexture	},
    { "bindTexture",	bindTexture	},
    { "loadTexture",	loadTexture	},
    { "unBindTexture",	unBindTexture},
    { 0, 0 },
  };
  luaL_newlib(L, reg);
  return 1;
}

int lua_lang_init::getVersion(lua_State *L)
{
  LOG("Simple - cracking bottles- version 0.2.0");
  return 1;
}

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
  lua_register(m_L, "simple_getPointer",  getPointer);
  //Graphics
  lua_register(m_L, "simple_makeTexture", makeTexture);
  lua_register(m_L, "simple_loadTexture", loadTexture);
  lua_register(m_L, "simple_bindTexture", bindTexture);
  lua_register(m_L, "simple_unBindTexture", unBindTexture);

  lua_register(m_L, "simple_makeShader", createShader);
  lua_register(m_L, "simple_bindShader", bindShader);
  lua_register(m_L, "simple_unBindShader", unBindShader);
  lua_register(m_L, "simple_sendShaderUniformLocation", sendShaderUniformLocation);

  lua_register(m_L, "simple_makeBatch", createBatch);
  lua_register(m_L, "simple_renderMesh", renderMesh);
  lua_register(m_L, "simple_beginBatch", beginBatch);
  lua_register(m_L, "simple_endBatch", endBatch);
  lua_register(m_L, "simple_drawBatch", drawBatch);

//GL Graphics
  lua_register(m_L, "simple_clearScreen", clearScreen);
  lua_register(m_L, "simple_setViewport", setViewport);
  //UTILS
  lua_register(m_L, "simple_getDeltaTime", getDeltaTime);
  lua_register(m_L, "simple_getFPS", getFPS);
  lua_register(m_L, "simple_getVersion", getVersion);
  //MATHS
  lua_register(m_L, "simple_makeOrthoView", setOrthoView);
}

//TODO make simple look more like Love *(evilface)

void lua_lang_init::dumb()
{
  lua_close(m_L);
}

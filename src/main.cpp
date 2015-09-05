
/*
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <SDL.h>
*/

#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

#include "utils/definitions.h"
#include "utils/lua_lang_init.h"
#include "utils/core.h"

using namespace simple;
using namespace simple::lang;

void update_em();

lua_lang_init* lua_init;

void update_simple()
{
  lua_init->getCore()->getWindow()->calculateDeltaTime();
  lua_init->callFunction("simple_update");
}

void render_simple()
{
  lua_init->callFunction("simple_draw");
}

int main()
{

  //Init Simple!
  lua_init = new lua_lang_init();
  lua_init->create();
  lua_init->registerFunctions();
  lua_init->setMainScript("res/main.lua");
  lua_init->callFunction("simple_init");
  lua_init->makeDefaultWindow();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifndef EMSCRIPTEN
  while(lua_init->getCore()->getWindow()->getRunning())
  {
    render_simple();
    update_simple();
    lua_init->getCore()->getWindow()->update();
  }
#endif
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(update_em, 0, 0);
#endif
  //lua_init->callFunction("simple_dumb");
  //lua_init->dumb();
  return 1;
}

void update_em()
{
  if(!lua_init->getCore()->getWindow()->getRunning())
    return;

  render_simple();
  lua_init->getCore()->getWindow()->calculateDeltaTime();
  update_simple();

//limit fps to 60
  if(lua_init->getCore()->getWindow()->getVSync())
    glfwSwapInterval(1);
  glfwGetCursorPos(lua_init->getCore()->getWindow()->getWindow(), &lua_init->getCore()->getWindow()->m_px, &lua_init->getCore()->getWindow()->m_py);

  glfwSwapBuffers(lua_init->getCore()->getWindow()->getWindow());
  glfwPollEvents();
}

#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

#include "utils/definitions.h"
#include "utils/lua_lang_init.h"
#include "utils/core.h"
#include "utils/file_system.h"
#include "sound/openal_context.h"
#include "sound/ogg_player.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../deps/stb_vorbis/stb_vorbis.h"

using namespace simple;
using namespace simple::lang;
using namespace simple::sound;

void update_em();

lua_lang_init* lua_init;

int main()
{
  //Init Simple!
  lua_init = new lua_lang_init();
  lua_init->create();
  lua_init->registerFunctions();
  lua_init->setMainScript("res/main.lua");
  lua_getglobal(lua_init->getState(), "simple");
  lua_pushstring(lua_init->getState(), "load");
  lua_rawget(lua_init->getState(), -2);
  lua_call(lua_init->getState(), 0, 0);

  lua_init->makeDefaultWindow();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifndef EMSCRIPTEN
  while(lua_init->getCore()->getWindow()->getRunning())
  {
    lua_init->getCore()->getWindow()->calculateDeltaTime();

    lua_pushstring(lua_init->getState(), "update");
    lua_rawget(lua_init->getState(), -2);
    lua_pushnumber(lua_init->getState(),lua_init->getCore()->getWindow()->getDeltaTime());
    lua_call(lua_init->getState(), 1, 0);

    lua_pushstring(lua_init->getState(), "draw");
    lua_rawget(lua_init->getState(), -2);
    lua_call(lua_init->getState(), 0, 0);

    lua_init->getCore()->getWindow()->update();
    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR){
      LOG("OpenGL error: " << err);
    }
  }
#endif
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(update_em, 0, 0);
#endif
  //lua_init->callFunction("simple_dumb");
  lua_init->dumb();
  return 1;
}

void update_em()
{
  if(!lua_init->getCore()->getWindow()->getRunning())
    return;

  //render_simple();
  lua_init->getCore()->getWindow()->calculateDeltaTime();
  //update_simple();

  GLenum err = GL_NO_ERROR;
  while((err = glGetError()) != GL_NO_ERROR){
    LOG("OpenGL error: " << err);
  }

//limit fps to 60
  if(lua_init->getCore()->getWindow()->getVSync())
    glfwSwapInterval(1);
  glfwGetCursorPos(lua_init->getCore()->getWindow()->getWindow(), &lua_init->getCore()->getWindow()->m_px, &lua_init->getCore()->getWindow()->m_py);

  glfwSwapBuffers(lua_init->getCore()->getWindow()->getWindow());
  glfwPollEvents();
}

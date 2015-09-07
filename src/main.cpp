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

void playsound()
{

}

void update_simple()
{
  lua_init->getCore()->getWindow()->calculateDeltaTime();
  lua_init->callFunction("simple_update");
}

void render_simple()
{
  lua_init->callFunction("simple_draw");
}

uint m_vbo;
uint m_ebo;

int main()
{
  playsound();
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
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  lua_init->dumb();
  return 1;
}

void update_em()
{
  if(!lua_init->getCore()->getWindow()->getRunning())
    return;

  render_simple();
  lua_init->getCore()->getWindow()->calculateDeltaTime();
  update_simple();

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

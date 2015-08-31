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

#include <iostream>

#include "graphics/shader.h"
#include "maths/mat4.h"
#include "maths/vec3.h"
#include "utils/definitions.h"
#include "graphics/mesh.h"
#include "graphics/texture2D.h"
#include "utils/file.h"
#include "graphics/font.h"
#include "graphics/batch2d.h"
#include "input/keyboard.h"
#include "utils/lua_lang_init.h"
#include "utils/core.h"

#include <stdlib.h>

#include <GLFW/glfw3.h>
#include "window/glfw_window.h"
#include "graphics/gl_graphics.h"

using std::string;

using namespace simple;
using namespace simple::graphics;
using namespace simple::maths;
using namespace simple::input;
using namespace simple::lang;

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;

lua_lang_init* lua_init;

void init()
{

  //Init Lua!
  lua_init = new lua_lang_init();
  lua_init->create();
  lua_init->registerFunctions();
  lua_init->setMainScript("main.lua");
  lua_init->callFunction("simple_init");
  lua_init->makeDefaultWindow();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //f = new font();
  // f->load(ft, m_font_shader, "res/font.ttf");
  //f->setFontSize(16);
  //f->setColor(m_shader,.2f,.8,.5,1);

}


void render ()
{
  //TODO check if it exists
  lua_init->callFunction("simple_draw");

  /*
  m_font_shader->bind();
  f->begin();
  f->setColor(m_shader, 0.2f, 0.4f, 0.3345f, 1);
  f->draw("Hello World", 100, 100, 1, 1);
  f->end();
  m_font_shader->unbind();
  m_shader->bind();
  */
 }

void update()
{
  lua_init->callFunction("simple_update");
  lua_init->simple_core->getWindow()->update();
}

int main()
{
  if(FT_Init_FreeType(&ft)){
    LOG("Error: Could not init freetype lib!");
    return 1;
  }

  init();

  while(lua_init->simple_core->getWindow()->getRunning()){
    render();
    update();

  }
  lua_init->callFunction("simple_dumb");
  return 0;
}

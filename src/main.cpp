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
#include "graphics/default_shaders.h"
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

mat4 proj;

batch2d* batch;
texture2D* texture;
shader* m_shader;
uint uniProj;

font* f;
shader* m_font_shader;

keyboard* key;
lua_lang_init* lua_init;

gl_graphics gl_g;

//NOTE: Don't forget to clean this class ;)

void init()
{

  //Init Lua!
  lua_init = new lua_lang_init();
  lua_init->create();
  lua_init->registerFunctions();
  lua_init->setMainScript("main.lua");
  lua_init->callFunction("simple_init");

  m_shader = new shader();
  m_shader->create(texture_vertex, texture_fragment);

  proj.setToIdentity();
  proj = proj.setOrtho(0, lua_init->simple_core->getWindow()->getWidth(), lua_init->simple_core->getWindow()->getHeight(), 0, 0, 100);

  texture = new texture2D();
  texture->create("res/test.png");

  m_shader->sendUniformLocation("proj", proj);
  
  m_font_shader = new shader();
  m_font_shader->create(font_vertex, font_fragment);

  m_font_shader->sendUniformLocation("proj", proj);
    
  f = new font();
  f->load(ft, m_font_shader, "res/font.ttf");
  f->setFontSize(16);
  f->setColor(m_shader,.2f,.8,.5,1);

  batch = new batch2d(m_shader);
  batch->create();

  key = new keyboard();

}

void render()
{

  //TODO check if it exists
  lua_init->callFunction("simple_draw");
  
  m_font_shader->bind();
  f->begin();
  f->setColor(m_shader, 0.2f, 0.4f, 0.3345f, 1);
  f->draw("Hello World", 100, 100, 1, 1);
  f->end();
  m_font_shader->unbind();
  
  m_shader->bind();
  texture->bind();
  batch->begin();
  batch->draw(100, 300, 16, 16, 1, 1, 1, .4f);
  batch->draw(200, 300, 16, 16);
  batch->renderMesh();
  batch->end();
  texture->unbind();
  m_shader->unbind();
}

float test;

void update()
{
  //TODO check if it exists
  lua_init->callFunction("simple_update");
  
  lua_init->simple_core->getWindow()->update();
}

int main()
{

  if(DEBBUG)
    LOG("Simple - version " << VERSION << " - Debbug messages are enabled!");
  if(!DEBBUG)
    LOG("Simple - version " << VERSION << " - Debbug messages are disabled!");

  if(FT_Init_FreeType(&ft)){
    LOG("Error: Could not init freetype lib!");
    return 1; 
  }
  
  //glEnable(GL_DEPTH); //3D

  init();

  while(lua_init->simple_core->getWindow()->getRunning()){
    glClear(GL_COLOR_BUFFER_BIT); //3D? Not yet. | GL_DEPTH_BUFFER_BIT);
    gl_g.clearScreen(0.55f, 0.556f, 0.5f, 1);
    glViewport(0,0,lua_init->simple_core->getWindow()->getWidth(), lua_init->simple_core->getWindow()->getHeight());

    render();
    update();

  }

  SAFE_DELETE(m_shader);
  SAFE_DELETE(f);
  SAFE_DELETE(key);
  //  SAFE_DELETE(lua_init);
  // SAFE_DELETE(window);
  //lua_init->dumb();
  //SAFE_DELETE(texture);
  return 0;
}


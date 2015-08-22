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
#include "maths/vec3.h"
#include "utils/definitions.h"
#include "graphics/mesh.h"
#include "graphics/texture2D.h"
#include "graphics/default_shaders.h"
#include "utils/file.h"
#include "graphics/font.h"
#include "graphics/batch2d.h"

#include <stdlib.h> 

#include <GLFW/glfw3.h>
#include "window/glfw_window.h"


using std::string;

#include "maths/mat4.h"

using namespace simple;
using namespace simple::graphics;
using namespace simple::maths;

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;

mat4 proj;

batch2d* batch;
texture2D* texture;
shader* m_shader;
uint uniProj;
glfw_window window;

//TODO Mouse and Keyboard input

void init()
{
  window.create("Batch rendering is really hard to make", 640, 480);
  window.setPosition(300,150); //TODO BUG FIXME automatically find the center of screen based on user's monitor

  m_shader = new shader();
  m_shader->create(texture_vertex,texture_fragment);

  proj.setToIdentity();
  proj = proj.setOrtho(0, window.getWidth(), window.getHeight(), 0, 0, 100);

  uniProj = glGetUniformLocation(m_shader->getProgram(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, proj.dataBlock());

  batch = new batch2d(m_shader);
  batch->create();

  texture = new texture2D();
  texture->create("res/test.png");
}

float angle;
float testx = 100;

float deltaTime;
double currentFrameTime = window.getTicks();
double lastFrameTime = currentFrameTime;

void update()
{
  //update stuff
  currentFrameTime = window.getTicks();
  deltaTime = currentFrameTime - lastFrameTime;
  lastFrameTime = currentFrameTime;

  window.setDeltaTime(deltaTime);

  angle += 33 * deltaTime;
  testx += 20 * deltaTime;

  window.printFPS();
  window.update();
}


void render()
{
  m_shader->bind();
  texture->bind();
  batch->begin();
  //batch->draw(100, 300, 16, 16);
  for(int i = 0; i < 33620;i++)
    batch->draw(rand()%620, rand()%480, 16, 16);
  //batch->draw(300,300,16,16, 1, 1, 1);
  batch->renderMesh();
  batch->end();

  texture->unbind();
  m_shader->unbind();
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
  
  glEnable(GL_DEPTH);

  init();

  currentFrameTime = window.getTicks();

  while(window.getRunning()){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.39f,0.37f,0.45f,1);
    glViewport(0,0,window.getWidth(),window.getHeight());

    render();
    update();

  }

  SAFE_DELETE(m_shader);
  //SAFE_DELETE(batch);
  //SAFE_DELETE(texture);
  return 0;
}


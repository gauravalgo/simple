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
mesh* m;
uint uniProj;
glfw_window window;

float deltaTime;
int lastFrameTime = 0, currentFrameTime = 0;
int fpsMill = 1000/60;
void update()
{
    //update stuff
    lastFrameTime = currentFrameTime;
    currentFrameTime = window.getTicks();

    deltaTime = (float) (currentFrameTime - lastFrameTime) ; // 1000.0f;

    window.setDeltaTime(deltaTime);

    window.printFPS();
    window.update();
}

void render()
{
    m_shader->bind();
    texture->bind();

    batch->begin();
    for(int i = 0; i < 100;i++)
      batch->draw(texture,rand()%window.getWidth(),rand()%window.getHeight());
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

  window.create("Replacing SDL with GLFW and Batches", 640, 480);

  if(FT_Init_FreeType(&ft)){
    LOG("Error: Could not init freetype lib!");
    return 1; 
  }
  
  glEnable(GL_DEPTH);

  m_shader = new shader();
  m_shader->create(texture_vertex,texture_fragment);
  m_shader->bind();

  m = new mesh();

  proj.setToIdentity();
  proj = proj.setOrtho(0, window.getWidth(), window.getHeight(), 0, 0, 100);

  uniProj = glGetUniformLocation(m_shader->getProgram(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, proj.dataBlock());

  batch = new batch2d();
  batch->setShader(m_shader);
  batch->create();
  texture = new texture2D();
  texture->create("res/test1.png");

  currentFrameTime = window.getTicks();

  while(window.getRunning()){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.39f,0.37f,0.45f,1);
    glViewport(0,0,window.getWidth(),window.getHeight());

    render(); //TODO check if render should be first
    update();

    //int currentSpeed = window.getTicks() - currentFrameTime;
     //if(fpsMill > currentSpeed) {
        //window.delay(fpsMill - currentSpeed);
     //}
  }

  SAFE_DELETE(m_shader);
  return 0;
}


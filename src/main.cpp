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

#include "window/sdl_window.h"
#include "graphics/shader.h"
#include "maths/vec3.h"
#include "graphics/definitions.h"
#include "graphics/mesh.h"
#include "graphics/texture2D.h"
#include "graphics/default_shaders.h"

#include <GL/glew.h>
#include <vector>

#include "maths/mat4.h"

using namespace simple;

int main()
{

  if(DEBBUG)
    LOG("Simple - version " << VERSION << " - Debbug messages are enabled!");
  if(!DEBBUG)
    LOG("Simple - version " << VERSION << " - Debbug messages are disabled!");

  sdl_window window;

  window.makeWindow("Simple", -1, -1, 800, 600);

  glEnable(GL_DEPTH);

  shader s;
  s.create(simple::texture_vertex,simple::texture_fragment);

  float v[] = {
    //  Position      Color             Texcoords
    -14,  14, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
    14,  14, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
    14, -14, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -14, -14, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
  };


  unsigned short elements[] =
    { 0, 1, 2,
      2, 3, 0
    };

  mesh* m_mesh = new mesh();
  m_mesh->create(s, v, sizeof(v), elements, sizeof(elements));


  texture2D* m_texture = new texture2D();

  //m_texture->create(2,2,pixels);
  m_texture->create("./res/test2.png");

  float deltaTime;
  int lastFrameTime = 0, currentFrameTime = 0;

  currentFrameTime = window.getTicks();

  int fpsMill = 1000/60;



  mat4 proj;
  proj.setToIdentity();
  proj = mat4::setOrtho(0, 800, 600, 0, 0, 100);

  uint uniProj = glGetUniformLocation(s.getProgram(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, proj.dataBlock());

  mat4 model;
  model.setToIdentity();
  model.scale(vec3(2,2,1));
  model.translate(vec3(100.0f,100.0f,0));
  model = mat4::rotationMatrix(model,vec3(0,0,-1), -180);
  
  uint uniModel = glGetUniformLocation(s.getProgram(), "model");
  glUniformMatrix4fv(uniModel, 1, GL_FALSE, model.dataBlock());

  while(window.getRunning()){

    lastFrameTime = currentFrameTime;
    currentFrameTime = window.getTicks();

    deltaTime = (float) (currentFrameTime - lastFrameTime) / 1000.0f;

    window.setDeltaTime(deltaTime);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f,0.2f,0.4f,1);
    glViewport(0,0,800,600);

    window.printFPS();

    m_texture->bind();

    s.bind();
    m_mesh->draw(6);
    s.unbind();

    m_texture->unbind();

    window.update();

    int currentSpeed = window.getTicks() - currentFrameTime;
    if(fpsMill > currentSpeed) {
      window.delay(fpsMill - currentSpeed);
    }
  }
  m_texture->destroy();

  window.quit();

  SAFE_DELETE(m_mesh);
  SAFE_DELETE(m_texture);
  return 0;
}


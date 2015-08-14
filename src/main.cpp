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
#include "graphics/object3D.h"
#include "maths/vector3.h"
#include "graphics/definitions.h"
#include "graphics/mesh.h"
#include "graphics/texture2D.h"
#include "graphics/default_shaders.h"
#include "graphics/camera.h"

#include <GL/glew.h>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace simple;

/*
 * I dont like using GLM.TODO make your own math functions to work!
 */

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
      -0.05f,  0.05f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
       0.05f,  0.05f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
       0.05f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
      -0.05f, -0.05f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
  };


  short elements[] =
    { 0, 1, 2,
      2, 3, 0
    };

  mesh* m_mesh = new mesh();
  m_mesh->create(s, v, sizeof(v), elements, sizeof(elements));

  texture2D* m_texture = new texture2D();
  float pixels[] = {
      0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
  };
  //m_texture->create(2,2,pixels);
  m_texture->create("./res/test.png");

  float deltaTime;
  int lastFrameTime = 0, currentFrameTime = 0;

  currentFrameTime = window.getTicks();

  int fpsMill = 1000/60;


  glm::mat4 view = glm::lookAt(
      glm::vec3(1.2f, 1.2f, 1.2f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 1.0f)
  );

  uint uniView = glGetUniformLocation(s.getProgram(), "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 trans;
  trans = glm::rotate(trans, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  glm::mat4 proj = glm::perspective(glm::radians(40.0f), 800.0f / 600.0f, 1.0f, 10.0f);

  uint uniProj = glGetUniformLocation(s.getProgram(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

  //trans = glm::translate(trans, glm::vec3(100.0f, 100.0f, 0.0f));

  trans = glm::translate(trans, glm::vec3(0.5f * 14, 0.5f * 14, 0.0f));
  trans = glm::rotate(trans, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
  trans = glm::translate(trans, glm::vec3(-0.5f * 14, -0.5f * 14, 0.0f));

  trans = glm::scale(trans, glm::vec3(1, 1, 1.0f));

  uint uniTrans = glGetUniformLocation(s.getProgram(), "model");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));


  while(window.getRunning()){

      lastFrameTime = currentFrameTime;
      currentFrameTime = window.getTicks();

      deltaTime = (float) (currentFrameTime - lastFrameTime) / 1000.0f;

      window.setDeltaTime(deltaTime);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.4f,0.2f,0.4f,1);

      window.printFPS();

    //  for(int i = 0; i < 10;i++)
      m_texture->bind();

      s.bind();
      m_mesh->draw(6);
      s.unbind();

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


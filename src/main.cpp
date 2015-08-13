#include <iostream>

#include "window/sdl_window.h"
#include "graphics/shader.h"
#include "graphics/object3D.h"
#include "maths/vector3.h"
#include "graphics/definitions.h"
#include "graphics/mesh.h"

#include <GL/glew.h>
#include <vector>

using namespace simple;

const char* frag =
  "#version 130\n"

  "in vec3 Color;"

  "void main(void) {"
  "gl_FragColor = vec4(Color, 1.0);"
  "}";

const char* vert =
  "#version 130\n"
  "in vec2 position;"
  "in vec3 color;"

  "out vec3 Color;"

  "void main(void) {"
  "Color = color;"
  "gl_Position = vec4(position,0.0f,1.0f);"
  "}";


int main()
{

  if(DEBBUG)
   LOG("Simple - version " << VERSION << " - Debbug messages are enabled!");
  if(!DEBBUG)
   LOG("Simple - version " << VERSION << " - Debbug messages are disabled!");

  sdl_window window;

  window.makeWindow("Simple", -1, -1, 800, 680);

  glEnable(GL_DEPTH);

  shader s;
  s.create(vert,frag);

  float v[] = {
    -0.05f,  0.05f, 1.0f, 0.33f, 0.4f, // Top-left
    0.05f,  0.05f, 0.0f, 0.44f, 0.5f, // Top-right
    0.05f, -0.05f, 0.0f, 1.33f, 1.0f, // Bottom-right
    -0.05f, -0.05f, 1.0f, 0.0f, 1.0f  // Bottom-left
  };

  short elements[] =
    { 0, 1, 2,
      2, 3, 0
    };

  mesh* m_mesh = new mesh();
  m_mesh->create(s, v, sizeof(v), elements, sizeof(elements));

  float deltaTime;
  int lastFrameTime = 0, currentFrameTime = 0;

  currentFrameTime = window.getTicks();

  int fpsMill = 1000/60;

  while(window.getRunning()){

      lastFrameTime = currentFrameTime;
      currentFrameTime = window.getTicks();

      deltaTime = (float) (currentFrameTime - lastFrameTime) / 1000.0f;

      window.setDeltaTime(deltaTime);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0,0,0,1);

      window.printFPS();

      for(int i = 0; i < 15000;i++)
        m_mesh->draw();

      window.update();

      int currentSpeed = window.getTicks() - currentFrameTime;
      if(fpsMill > currentSpeed) {
         window.delay(fpsMill - currentSpeed);
       }
    }
  m_mesh->unbind();

  window.quit();

  SAFE_DELETE(m_mesh);
  return 0;
}


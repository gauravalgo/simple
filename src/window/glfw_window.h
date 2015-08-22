#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../maths/vec2.h"

using namespace simple::maths;

namespace simple
{

    class glfw_window
    {
    public:
      glfw_window();
      ~glfw_window();
    public:
      GLFWwindow* window;
    public:
      void create(const char* title, int width, int height);
      void update();
      void setDeltaTime(float dt){m_delta = dt;}
      float getDeltaTime(){return m_delta;}
      double getTicks();
      void printFPS();
      void setPosition(int x, int y);
      void setTitle(const char* title);
      void setVisible(bool visible);
      float getPointX();
      float getPointY();
      vec2 getPointPosition();
      bool isFocused();
      void destory();
    private:
      double px; //point x
      double py; //point y
      bool m_running;
      int m_width,m_height;
      float m_delta;
    public:
      bool getRunning(){return m_running;}
      int getWidth(){return m_width;}
      int getHeight(){return m_height;}
    };

  }

#endif

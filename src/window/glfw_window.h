#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
      float getTicks();
      void printFPS();
      void destory();
    private:
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

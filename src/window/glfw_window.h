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
    void printFPS();
    //@parm x: -1 = find center @parm y: -1 = find center
    void setPosition(int x, int y);
    void setTitle(const char* title);
    void setVisible(bool visible);
    bool isFocused();
    void destory();
  private:
    //point x
    double m_px;
    //point y
    double m_py; 
    bool m_running;
    int m_width,m_height;
    float m_delta;
    const GLFWvidmode* m_mode;
  public:
    float getDeltaTime(){return m_delta;}
    GLFWwindow* getWindow(){return window;}
    double getTicks();
    float getPointX();
    float getPointY();
    vec2 getPointPosition();
    vec2 getMonitorSize();
    bool getRunning(){return m_running;}
    int getWidth(){return m_width;}
    int getHeight(){return m_height;}
  };

}

#endif

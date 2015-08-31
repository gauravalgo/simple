#include "glfw_window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "../utils/definitions.h"
#include "../utils/core.h"
#include "../maths/vec2.h"

using namespace simple;
using namespace simple::maths;

glfw_window::glfw_window():
  m_running(true),
  m_width(0),
  m_vsync(false),
  m_height(0)
{

}
glfw_window::~glfw_window(){}

void glfw_window::error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

void glfw_window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  //LOG(GLFW_KEY_ESCAPE); = 256
  core c;

  if (DEBBUG && key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if(key == GLFW_KEY_W && action == GLFW_PRESS)
    LOG("W has been pressed");
  if(key == GLFW_KEY_W && action == GLFW_RELEASE)
    LOG("W has been relased");

  //isKeyDown(key);

  LOG(GLFW_KEY_W);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  glfwGetCursorPos(window, &xpos, &ypos);
}

void glfw_window::create(const char *title, int width, int height, bool fullscreen)
{

  if (!glfwInit())
    LOG("Error: GLFW(window) could not be inited");

  m_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  if(fullscreen)
     window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
   else
      window = glfwCreateWindow(width, height, title, NULL, NULL);

  m_width = width;
  m_height = height;
  m_running = true;

  glfwSetErrorCallback(error_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);

  if (!window){
    LOG("Error: Could not create window");
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);

  GLenum res = glewInit();
  if(res != GLEW_OK){
    std::cerr << "Glew(opengl) failed to initialize! You're doomed ^.^" << std::endl;
  }

  if(DEBBUG)
    LOG("GLFW: Window & GLEW inited");
}

double currentTick, startTick = glfwGetTime();
unsigned int numFrame = 0;

float glfw_window::getFPS()
{
  return m_fps;
}

void glfw_window::calculateFPS()
{
  ++numFrame;
  currentTick = glfwGetTime() ;

  if (currentTick - startTick >= 1.0){
      startTick += 1.0;
      m_fps = numFrame;
      //std::cout << "fps: " << m_fps << ", ft: " << 1000.0f / m_fps << "ms" << std::endl;
      numFrame = 0;
    }
}

float deltaTime;
double currentFrameTime = glfwGetTime();
double lastFrameTime = currentFrameTime;
void glfw_window::calculateDeltaTime()
{
    //update stuff
    currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    setDeltaTime(deltaTime);
    calculateFPS();
}

void glfw_window::update()
{
  if(!m_running)
    return;

  calculateDeltaTime();

  //limit fps to 60
  if(m_vsync)
     glfwSwapInterval(1);

  glfwGetCursorPos(window, &m_px, &m_py); //keep track of the current position of the pointer
  if(glfwWindowShouldClose(window)){
    LOG("GLFW: closing");
    destroy();
  }
  glfwSwapBuffers(window);
  glfwPollEvents();
}

double glfw_window::getTicks()
{
  return glfwGetTime();
}

float glfw_window::getDeltaTime()
{
  return m_delta;
}

bool glfw_window::isFocused()
{
  return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

float glfw_window::getPointX()
{
  return (float) m_px;
}

float glfw_window::getPointY()
{
  return (float) m_py;
}

vec2 glfw_window::getPointerPosition()
{
  return vec2(m_px,m_py);
}

vec2 glfw_window::getMonitorSize()
{
  int ww = (m_mode->width);
  int wh = (m_mode->height);
  return vec2(ww, wh);
}

//This is more likely to be used when you have > 1 windows
void glfw_window::setVisible(bool visible)
{
  if(visible)
    glfwShowWindow(window);
  else
    glfwHideWindow(window);

}

void glfw_window::setTitle(const char *title)
{
  glfwSetWindowTitle(window, title);
}

void glfw_window::setPosition(int x, int y)
{
  if(x == -1 && y == -1) //find the center!
    glfwSetWindowPos(window, (getMonitorSize().x - m_width)*.5f, (getMonitorSize().y - m_height)*.5f);
  else if(x == -1) //find the x center
    glfwSetWindowPos(window, (getMonitorSize().x - m_width)*.5f, y);
  else if(y == -1) //find the y center
    glfwSetWindowPos(window, x, (getMonitorSize().y - m_height)*.5f);
  else //let it be :)
    glfwSetWindowPos(window, x, y);
}

void glfw_window::destroy()
{
  glfwSetWindowShouldClose(window, GL_TRUE);
  glfwDestroyWindow(window);
  glfwTerminate();
  m_running = false;
}

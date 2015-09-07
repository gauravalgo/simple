#include "glfw_window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "../utils/definitions.h"
#include "../utils/core.h"
#include "../maths/vec2.h"

#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

using namespace simple;
using namespace simple::maths;

#define MAX_KEYS 256
#define MAX_MOUSE 32

glfw_window::glfw_window():
  m_running(true),
  m_width(0),
  m_vsync(false),
  m_height(0)
{

}
glfw_window::~glfw_window(){}

void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  glfwGetCursorPos(window, &xpos, &ypos);
}

static bool m_DownKey[MAX_KEYS];
static bool m_UpKey[MAX_KEYS];
static bool m_mousePressed[MAX_MOUSE];
static bool m_mouseRelased[MAX_MOUSE];

void glfw_window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  m_DownKey[key] = action != GLFW_RELEASE;
  m_UpKey[key] = action != GLFW_PRESS;
}

void glfw_window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  m_mousePressed[button] = action != GLFW_RELEASE;
  m_mouseRelased[button] = action != GLFW_PRESS;
}

void glfw_window::initInput()
{
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
}


int glfw_window::getMousePressed(int v)
{
  if(v <= MAX_MOUSE)
    return m_mousePressed[v];
  else
    LOG("You're trying to get an unknow button");
  return -1;
}

int glfw_window::getMouseReleased(int v)
{
  if(v <= MAX_MOUSE)
    return m_mouseRelased[v];
  else
    LOG("You're trying to get an unknow button");
  return -1;
}

int glfw_window::getDownKey(int key)
{
  if(key <= MAX_KEYS)
    return m_DownKey[key];
  else
    LOG("You're trying to get an unknow key");
  return 0;
}

int glfw_window::getUpKey(int key)
{
  if(key <= MAX_KEYS)
    return m_UpKey[key];
  else
    LOG("You're trying to get an unknow key");
  return 0;
}

void glfw_window::create(const char *title, int width, int height, bool fullscreen, bool resizable)
{
  if (!glfwInit())
    LOG("Error: GLFW(window) could not be inited");

#ifndef EMSCRIPTEN
  if(resizable)
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  else
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  m_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
#endif

#ifndef EMSCRIPTEN
  if(fullscreen){
    window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
  }else{
    window = glfwCreateWindow(width,height,title,NULL,NULL);
  }
#endif

#ifdef EMSCRIPTEN
  window = glfwCreateWindow(width, height, "hey", NULL, NULL);
#endif

  m_width = width;
  m_height = height;
  m_running = true;

#ifndef EMSCRIPTEN
  glfwSetErrorCallback(error_callback);
#endif
  if (!window){
    LOG("Error: Could not create window");
    glfwTerminate();
  }
#ifndef EMSCRIPTEN
  glfwMakeContextCurrent(window);
#endif
  GLenum res = glewInit();
  if(res != GLEW_OK){
    std::cerr << "Glew(opengl) failed to initialize! You're doomed ^.^" << std::endl;
  }

  if(DEBBUG){
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    LOG("GLFW version: " << major << "." << minor << "." << rev << " inited.");
  }
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

  //limit fps to 60
  if(m_vsync)
    glfwSwapInterval(1);

  glfwGetCursorPos(window, &m_px, &m_py); //keep track of the current position of the pointer
#ifndef EMSCRIPTEN
  if(glfwWindowShouldClose(window)){
    LOG("GLFW: closing");
    destroy();
  }
#endif
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
#ifndef EMSCRIPTEN
  glfwSetWindowShouldClose(window, GL_TRUE);
  glfwDestroyWindow(window);
#endif
  glfwTerminate();
  m_running = false;
}

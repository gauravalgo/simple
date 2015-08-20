#include "glfw_window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "../utils/definitions.h"
#include "../maths/vec2.h"

using namespace simple;
using namespace simple::maths;

glfw_window::glfw_window():
    m_running(true),
    m_width(0),
    m_height(0)
{

}

glfw_window::~glfw_window(){

}
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //LOG(GLFW_KEY_ESCAPE); = 256
    if (DEBBUG && key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    int state = glfwGetKey(window, GLFW_KEY_E);
    if (state == GLFW_PRESS)
        LOG("E is being pressed");
    if (state == GLFW_RELEASE)
        LOG("E is not pressed anymore!");
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
    //LOG(xpos << " " << ypos);
}

void glfw_window::create(const char *title, int width, int height)
{

  if (!glfwInit())
    LOG("Error: GLFW(window) could not be inited");

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  m_width = width;
  m_height = height;
  m_running = true;

  glfwSetErrorCallback(error_callback);

  if (!window){
    LOG("Error: Could not create window");
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);

  GLenum res = glewInit();
   if(res != GLEW_OK){
     std::cerr << "Glew(opengl) failed to initialize! You're doomed ^.^" << std::endl;
   }

  if(DEBBUG)
    LOG("GLFW: Window & GLEW inited");
}

double currentTick, startTick = glfwGetTime(); //1000.0f;
unsigned int numFrame = 0;

void glfw_window::printFPS()
{
  ++numFrame;
  currentTick = glfwGetTime() ;//1000.0f;

  if (currentTick - startTick >= 1.0)
    {
      startTick += 1.0;
      std::cout << "fps: " << numFrame << ", ft: " << 1000.0f / numFrame << "ms" << std::endl;
      numFrame = 0;
    }
}

void glfw_window::update()
{
    if(!m_running)
        return;

    //limit fps to 60
    glfwSwapInterval(1);
    glfwGetCursorPos(window, &px, &py); //keep track of the current position of the point
    if(glfwWindowShouldClose(window)){
        LOG("GLFW: closing");
        destory();
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

float glfw_window::getTicks()
{
    return glfwGetTime();
}

bool glfw_window::isFocused()
{
    return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

float glfw_window::getPointX()
{
    return (float) px;
}

float glfw_window::getPointY()
{
    return (float) py;
}

vec2 glfw_window::getPointPosition()
{
    return vec2(px,py);
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
    glfwSetWindowPos(window, x, y);
}

void glfw_window::destory()
{
  glfwSetWindowShouldClose(window, GL_TRUE);
  glfwDestroyWindow(window);
  glfwTerminate();
  m_running = false;
}

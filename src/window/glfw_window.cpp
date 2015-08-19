#include "glfw_window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "../utils/definitions.h"

using namespace simple;

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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void glfw_window::create(const char *title, int width, int height)
{

  if (!glfwInit())
    LOG("Error: glfw could not be inited");

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  m_width = width;
  m_height = height;
  m_running = true;

  glfwSetErrorCallback(error_callback);

  if (!window){
    LOG("Error: could not create window");
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetKeyCallback(window, key_callback);

  GLenum res = glewInit();
   if(res != GLEW_OK){
     std::cerr << "Glew failed to initialize! You're doomed ^.^" << std::endl;
   }

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

void glfw_window::destory()
{

  glfwDestroyWindow(window);
  glfwTerminate();
  m_running = false;
}

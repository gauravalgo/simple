#include "sdl_window.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

using namespace std;
using namespace simple;

sdl_window::sdl_window():
running(true)
{

}

sdl_window::~sdl_window()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    running = false;
}

void sdl_window::makeWindow(const char *title, int x, int y, int width, int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    if(x == -1 && y == -1)
    {
        x = SDL_WINDOWPOS_CENTERED;
        y = SDL_WINDOWPOS_CENTERED;
    }
    if(x == -1)
      x = SDL_WINDOWPOS_CENTERED;
    if(y == -1)
      y = SDL_WINDOWPOS_CENTERED;


    m_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum res = glewInit();
    if(res != GLEW_OK){
         std::cerr << "Glew failed to initialize! You're doomed ^.^" << std::endl;
    }

}

void sdl_window::setPosition(int x, int y)
{
    SDL_SetWindowPosition(m_window,x,y);
}

void sdl_window::setWindowSize(int w, int h)
{
    SDL_SetWindowSize(m_window,w,h);
}

void sdl_window::setWindowTitle(const char *title)
{
    SDL_SetWindowTitle(m_window,title);
}

void sdl_window::update()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT)
            running = false;
    }
}

void sdl_window::quit()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    running = false;
}

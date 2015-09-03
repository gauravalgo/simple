#include "sdl_window.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL.h>
#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

#include "../utils/definitions.h"

using namespace simple;

sdl_window::sdl_window()
{

}

sdl_window::~sdl_window()
{

}

void sdl_window::create(const char* title, int width, int height, bool fullscreen)
{
        SDL_Init(SDL_INIT_VIDEO);
#ifndef EMSCRIPTEN
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#if EMSCRIPTEN
        char const * ti = emscripten_run_script_string("document.title");
#else
        char const * ti = "simple";
#endif

        window = SDL_CreateWindow(ti, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

        context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, context);

        surface = SDL_GetWindowSurface(window);
        glewExperimental = GL_TRUE;

        GLenum res = glewInit();
        if(res != GLEW_OK){
                std::cerr << "Glew(opengl) failed to initialize! You're doomed ^.^" << std::endl;
        }

#ifndef EMSCRIPTEN
        SDL_GL_SetSwapInterval(1);
#endif

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);

        glEnable(GL_BLEND);
}

void sdl_window::update()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, 600, 480);
        glClearColor(.4f,.3f,.7f,1);

        SDL_GL_SwapWindow(window);

        SDL_Event e;
        while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT)
                        m_close = true;

        }
}
void sdl_window::destroy()
{

}

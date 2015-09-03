#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

namespace simple
{
        class sdl_window
        {
        public:
                sdl_window();
                ~sdl_window();
                void create(const char* title, int width, int height, bool fullscreen);
                void update();
                void destroy();
        public:
                void setClose(bool value){m_close = value;}
                bool isClose(){return m_close;}
                SDL_Window* getWindow(){return window;}
        private:
                bool m_close;
                SDL_Window* window;
                SDL_GLContext context;
                SDL_Surface* surface;

        };
}
#endif

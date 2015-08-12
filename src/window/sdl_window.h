#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL.h>

namespace simple
{

class sdl_window
{
public:
    sdl_window();
    ~sdl_window();
private:
    bool running;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
public:
    void makeWindow(const char* title, int x,int y, int width, int height);
    void setPosition(int x, int y);
    void setWindowSize(int w, int h);
    void setWindowTitle(const char* title);
    void update();
    void quit();
public:
    void setRunning(bool value){running = value;}
    bool getRunning(){return running;}
};
}
#endif

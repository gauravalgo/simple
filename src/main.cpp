#include <iostream>

#include "window/sdl_window.h"

#include <GL/glew.h>

using namespace simple;

int main()
{
    sdl_window window;

    window.makeWindow("Simple", -1, -1, 600, 480);
    while(window.getRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.3f,.4f,.1f,255);
        window.update();
    }
    window.quit();
    return 0;
}

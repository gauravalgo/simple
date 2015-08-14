/*******************************************************************************
 * Copyright 2015 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

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
    bool m_running;
    float m_delta_time;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
public:
    void makeWindow(const char* title, int x,int y, int width, int height);
    void setPosition(int x, int y);
    void setWindowSize(int w, int h);
    void setWindowTitle(const char* title);
    void update();
    void quit();
    void printFPS();
    void delay(float value);
public:
    void setRunning(bool value){m_running = value;}
    bool getRunning(){return m_running;}
    double getTicks();
    void setDeltaTime(float value){m_delta_time = value;}
    float getDeltaTime(){return m_delta_time;}
};
}
#endif

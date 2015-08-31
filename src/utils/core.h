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

#ifndef CORE_H
#define CORE_H

#include "../window/glfw_window.h"
#include "../graphics/gl_graphics.h"
#include "../input/keyboard.h"
namespace simple
{
  using namespace simple::graphics;
  //using namespace simple::input;

  class core
  {
  public:
    core();
    ~core();
  private:
    glfw_window* m_window;
    gl_graphics* m_graphics;
    //keyboard* m_keyboard;
  public:
    void create();

    //keyboard* getKeyboard();
    glfw_window* getWindow();
    gl_graphics* getGLGraphics();
  };
}
#endif

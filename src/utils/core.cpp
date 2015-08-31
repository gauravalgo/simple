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

#include "core.h"

#include "../window/glfw_window.h"
#include "definitions.h"
#include "../input/keyboard.h"

using namespace simple;
using namespace simple::graphics;
using namespace simple::input;


/*
 *Global holder of important classes
 */

core::core()
{
  
}

core::~core()
{

}

void core::create()
{
  m_window = new glfw_window();
  m_graphics = new gl_graphics();
  // m_keyboard = new keyboard();
}

glfw_window* core::getWindow()
{
    return m_window;
}

gl_graphics* core::getGLGraphics()
{
    return m_graphics;
}
/*
keyboard* core::getKeyboard()
{
  return m_keyboard;
}*/

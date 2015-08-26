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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../utils/definitions.h"
#include "../utils/core.h"
#include "../window/glfw_window.h"

namespace simple
{
  namespace input
  {
    class keyboard
    {
    public:
      keyboard();
      ~keyboard();
    public:
      bool isKeyDown(const char* key);
      bool isKeyUp(const char* key);
    private:
      glfw_window* m_window;
    };
  }
}
#endif
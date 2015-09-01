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

#include "keyboard.h"

#include "../utils/definitions.h"
#include "../utils/core.h"
#include "../window/glfw_window.h"

using namespace simple;
using namespace simple::input;

#include <string>
#include <iostream>

keyboard::keyboard()
{

}

keyboard::~keyboard()
{

}

int keyboard::getKey(std::string key)
{

  if (key == "0")
    return GLFW_KEY_0;
  if(key ==  "1")
    return GLFW_KEY_1;
  if(key ==  "2")
    return GLFW_KEY_2;
  if(key ==  "3")
    return GLFW_KEY_3;
  if(key ==  "4")
    return GLFW_KEY_4;
  if(key ==  "5")
    return GLFW_KEY_5;
  if(key ==  "6")
    return GLFW_KEY_6;
  if(key ==  "7")
    return GLFW_KEY_7;
  if(key ==  "8")
    return GLFW_KEY_8;
  if(key ==  "9")
    return GLFW_KEY_9;

  if(key ==  "enter")
    return GLFW_KEY_ENTER;
  if(key ==  "esc")
    return GLFW_KEY_ESCAPE;
  if(key ==  "space")
    return GLFW_KEY_SPACE;

  if(key ==  "left")
    return GLFW_KEY_LEFT;
  if(key ==  "up")
    return GLFW_KEY_UP;
  if(key ==  "down")
    return GLFW_KEY_DOWN;
  if(key ==  "right")
    return GLFW_KEY_RIGHT;


  if(key ==  "a")
    return GLFW_KEY_A;
  if(key ==  "b")
    return GLFW_KEY_B;
  if(key ==  "c")
    return GLFW_KEY_C;
  if(key ==  "d")
    return GLFW_KEY_D;
  if(key ==  "e")
    return GLFW_KEY_E;
  if(key ==  "f")
    return GLFW_KEY_F;
  if(key ==  "g")
    return GLFW_KEY_G;
  if(key ==  "h")
    return GLFW_KEY_H;
  if(key ==  "i")
    return GLFW_KEY_I;
  if(key ==  "j")
    return GLFW_KEY_J;
  if(key ==  "k")
    return GLFW_KEY_K;
  if(key ==  "l")
    return GLFW_KEY_L;
  if(key ==  "m")
    return GLFW_KEY_M;
  if(key ==  "n")
    return GLFW_KEY_N;
  if(key ==  "q")
    return GLFW_KEY_O;
  if(key ==  "p")
    return GLFW_KEY_P;
  if(key ==  "q")
    return GLFW_KEY_Q;
  if(key ==  "r")
    return GLFW_KEY_R;
  if(key ==  "s")
    return GLFW_KEY_S;
  if(key ==  "t")
    return GLFW_KEY_T;
  if(key ==  "u")
    return GLFW_KEY_U;
  if(key ==  "v")
    return GLFW_KEY_V;
  if(key ==  "w")
    return GLFW_KEY_W;
  if(key ==  "x")
    return GLFW_KEY_X;
  if(key ==  "y")
    return GLFW_KEY_Y;
  if(key ==  "z")
    return GLFW_KEY_Z;


  return 0;
}

bool keyboard::isKeyDown(std::string key)
{
  if(c.getWindow()->getDownKey(getKey(key))) {
    return true;
  }
  return false;
}

bool keyboard::isKeyUp(std::string key)
{
  if(c.getWindow()->getUpKey(getKey(key))) {
    return true;
  }
  return false;
}

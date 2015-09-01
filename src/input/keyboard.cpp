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

std::string keyboard::getKey(int key)
{

  switch(key){
  case 48:
    return "0";
  case 49:
    return "1";
  case 50:
    return "2";
  case 51:
    return "3";
  case 52:
    return "4";
  case 53:
    return "5";
  case 54:
    return "6";
  case 55:
    return "7";
  case 56:
    return "8";
  case 57:
    return "9";

  case 13:
    return "enter";
  case 27:
    return "esc";
  case 32:
    return "space";

  case 37:
    return "left";
  case 38:
    return "up";
  case 40:
    return "down";
  case 39:
    return "right";


  case 65:
    return "a";
  case 66:
    return "b";
  case 67:
    return "c";
  case 68:
    return "d";
  case 69:
    return "e";
  case 70:
    return "f";
  case 71:
    return "g";
  case 72:
    return "h";
  case 73:
    return "i";
  case 74:
    return "j";
  case 75:
    return "k";
  case 76:
    return "l";
  case 77:
    return "m";
  case 78:
    return "n";
  case 79:
    return "o";
  case 80:
    return "p";
  case 81:
    return "q";
  case 82:
    return "r";
  case 83:
    return "s";
  case 84:
    return "t";
  case 85:
    return "u";
  case 86:
    return "v";
  case 87:
    return "w";
  case 89:
    return "x";
  case 90:
    return "y";
  case 91:
    return "z";
  default:
    return "";
  }
  return "";
}

bool keyboard::isKeyDown(std::string key)
{
  std::string k = getKey(c.getWindow()->getDownKey());
  if(key == k)
    return true;
  return false;
}

bool keyboard::isKeyUp(const char* key)
{
  std::string k = getKey(c.getWindow()->getUpKey());
  if(key == k)
    return true;
  return false;
}

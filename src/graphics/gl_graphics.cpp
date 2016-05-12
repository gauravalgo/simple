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

#include "gl_graphics.h"

#include "../../deps/glew/include/GL/glew.h"
#include "../../deps/glfw/include/GLFW/glfw3.h"

using namespace simple;
using namespace simple::graphics;

/*
 *Useful GL/ES 2.0 functions. 
 */

gl_graphics::gl_graphics()
{
  
}

gl_graphics::~gl_graphics()
{
  
}

void gl_graphics::clear_()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_graphics::setBackgroundColor(float r, float g, float b, float a)
{
  glClearColor(r,g,b,a);  
}

void gl_graphics::setViewport(int x, int y, int width, int height)
{
 glViewport(x, y, width, height);
}

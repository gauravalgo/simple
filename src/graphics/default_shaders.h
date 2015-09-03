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

#ifndef _DEFAULT_SHADERS_H
#define _DEFAULT_SHADERS_H

#include <iostream>
#include <string>
using namespace std;

namespace simple
{
      namespace graphics
      {

            class default_shaders
            {
            public:
                  //OPENGL 2.1
                  static string gl_font_fragment;
                  static string gl_font_vertex;
                  static string gl_texture_fragment;
                  static string gl_texture_vertex;
                  //OPENGL ES 2.0
                  static string gl_es_font_fragment;
                  static string gl_es_font_vertex;
                  static string gl_es_texture_fragment;
                  static string gl_es_texture_vertex;

            };
      }
}
#endif

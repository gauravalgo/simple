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

namespace simple
{

  const char* font_vertex =
    "#version 130\n"
    "attribute vec4 coord;"
    "varying vec2 texcoord;"

    "void main(void) {"
    " gl_Position = vec4(coord.xy, 0, 1);"
    "texcoord = coord.zw;"
    "}";

  const char* font_fragment =
    "#version 130\n"
    "varying vec2 texcoord;"
    "uniform sampler2D tex;"
    "uniform vec4 color;"

    "void main(void) {"
    "gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;"
    "}";
  
  const char* texture_fragment =
    "#version 130\n"

    "in vec3 Color;"
    "in vec2 Texcoords;"
    "uniform sampler2D tex;"
    "void main(void) {"
    "gl_FragColor = texture(tex,Texcoords) * vec4(Color, 1.0);"
    "}";

  const char* texture_vertex =
    "#version 130\n"
    "in vec2 position;"
    "in vec3 color;"
    "in vec2 texcoords;"

    "out vec3 Color;"
    "out vec2 Texcoords;"

    "uniform mat4 proj = mat4(1);"
    "uniform mat4 model = mat4(1);"

    "void main(void) {"
    "Color = color;"
    "Texcoords = texcoords;"
    "gl_Position = proj * model * vec4(position, 0, 1);"
    "}";

}
#endif

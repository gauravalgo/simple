#ifndef _DEFAULT_SHADERS_H
#define _DEFAULT_SHADERS_H

namespace simple
{

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

  "uniform mat4 model;"
  "uniform mat4 view;"
  "uniform mat4 proj;"

  "void main(void) {"
  "Color = color;"
  "Texcoords = texcoords;"
  "gl_Position = proj *  view * model * vec4(position.xy, 0.0f, 1.0f);"
  "}";

}
#endif

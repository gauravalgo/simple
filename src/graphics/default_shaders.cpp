#include "default_shaders.h"

using namespace simple;
using namespace simple::graphics;

#include <iostream>
#include <string>
using namespace std;

string default_shaders::font_fragment =
        "#version 130\n"
        "in vec4 Color;"
        "in vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "gl_FragColor = texture2D(tex,Texcoords).r * Color;"
        "}";

string default_shaders::font_vertex =
        "#version 130\n"
        "in vec2 position;"
        "in vec4 color;"
        "in vec2 texcoords;"

        "out vec4 Color;"
        "out vec2 Texcoords;"

        "uniform mat4 proj = mat4(1);"

        "void main(void) {"
        "Color = color;"
        "Texcoords = texcoords;"
        "gl_Position = proj *  vec4(position, 0.0f, 1.0f);"
        "}";

string default_shaders::texture_fragment =
        "#version 130\n"

        "in vec4 Color;"
        "in vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "gl_FragColor = texture2D(tex,Texcoords).r * Color * texture2D(tex, Texcoords);"
        "}";

string default_shaders::texture_vertex =
        "#version 130\n"
        "in vec2 position;"
        "in vec4 color;"
        "in vec2 texcoords;"

        "out vec4 Color;"
        "out vec2 Texcoords;"

        "uniform mat4 proj = mat4(1);"

        "void main(void) {"
        "Color = color;"
        "Texcoords = texcoords;"
        "gl_Position = proj *  vec4(position, 0.0f, 1.0f);"
        "}";

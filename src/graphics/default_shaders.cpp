#include "default_shaders.h"

using namespace simple;
using namespace simple::graphics;

#include <iostream>
#include <string>
using namespace std;

string default_shaders::gl_font_fragment =
        "#version 130\n"
        "uniform vec3 Color;"
        "in vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, Texcoords).r);"
        "gl_FragColor = vec4(Color, 1.0) * sampled;"
        "}";

string default_shaders::gl_font_vertex =
        "#version 130\n"
        "in vec4 position;"
        "in vec4 color;"
        "in vec2 texcoords;"

        "out vec4 Color;"
        "out vec2 Texcoords;"

        "uniform mat4 proj = mat4(1);"

        "void main(void) {"
        "Color = color;"
        "gl_Position = proj *  vec4(position.xy, 0.0f, 1.0f);"
        "Texcoords = position.zw;"
        "}";

string default_shaders::gl_es_texture_fragment =
        "precision mediump float;"
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        ""
        ""
        "gl_FragColor = Color * texture2D(tex, Texcoords);"
        ""
        ""
        "}";

string default_shaders::gl_texture_fragment =
        "#version 130\n"

        "in vec4 Color;"
        "in vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "gl_FragColor = Color * texture2D(tex, Texcoords);"
        "}";

string default_shaders::gl_texture_vertex =
        "#version 130\n"
        "in vec2 position;"
        "in vec4 color;"
        "in vec2 texcoords;"

        "out vec4 Color;"
        "out vec2 Texcoords;"

        "uniform mat4 proj;"

        "void main(void) {"
        "Color = color;"
        "Texcoords = texcoords;"
        "gl_Position = proj *  vec4(position, 0.0f, 1.0f);"
        "}";
string default_shaders::gl_es_texture_vertex =
        "attribute vec2 position;"
        "attribute vec4 color;"
        "attribute vec2 texcoords;"
        "uniform mat4 proj;"

        "varying vec4 Color;"
        "varying vec2 Texcoords;"

        "void main(void) {"
        "Color = color;"
        "Texcoords = texcoords;"
        "gl_Position = proj * vec4(position, 0.0, 1);"
        ""
        ""
        "}";

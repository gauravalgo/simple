#include "default_shaders.h"

using namespace simple;
using namespace simple::graphics;

#include <iostream>
#include <string>
using namespace std;

string default_shaders::gl_font_fragment =
        "#version 120\n"
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, Texcoords).r);"
        "gl_FragColor = Color * sampled;"
        "}";
string default_shaders::gl_font_vertex =
        "#version 120\n"
        "attribute vec2 position;"
        "attribute vec4 color;"
        "attribute vec2 texcoords;"
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform mat4 proj = mat4(1);"
        "void main(void) {"
        "Color = color;"
        "gl_Position = proj *  vec4(position, 0.0f, 1.0f);"
        "Texcoords = texcoords;"
        "}";
string default_shaders::gl_texture_fragment =
        "#version 120\n"      
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "gl_FragColor = Color * texture2D(tex, Texcoords);"
        "}";
string default_shaders::gl_texture_vertex =
        "#version 120\n" 
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
        "}";

string default_shaders::gl_es_texture_fragment =
        "precision mediump float;"
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        "gl_FragColor = Color * texture2D(tex, Texcoords);"
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
        "}";
string default_shaders::gl_es_font_vertex =
        "attribute vec2 position;"
        "attribute vec4 color;"
        "attribute vec2 texcoords;"
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform mat4 proj;"
        "void main(void) {"
        "Color = color;"
        "gl_Position = proj *  vec4(position, 0.0, 1.0);"
        "Texcoords = texcoords;"
        "}";
string default_shaders::gl_es_font_fragment =
        "precision mediump float;"
        "varying vec4 Color;"
        "varying vec2 Texcoords;"
        "uniform sampler2D tex;"
        "void main(void) {"
        ""
        "gl_FragColor = Color;"
        "}";

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

#include "font.h"
#include "../utils/definitions.h"

#include <GL/gl.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace simple;

#include "shader.h"

font::font()
{
  
}

font::~font()
{
  
}

void font::begin()
{
  glEnable(GL_BLEND);
}

void font::load(FT_Library ft,shader s,const char* fontPath)
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if(FT_New_Face(ft, fontPath, 0, &m_face)){
    LOG("Error: Could not load font");
    return;
  }

  m_glyph = m_face->glyph;

  //Set a default size for our font
  FT_Set_Pixel_Sizes(m_face, 0, 12);
  
  //Not: We are must use a font shader !
  //Take a look at graphics/default_shaders.h
  GLuint tex;
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  uint unitex = glGetUniformLocation(s.getProgram(), "tex");
  glUniform1i(unitex, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  uint co = glGetAttribLocation(s.getProgram(), "coord");
  glEnableVertexAttribArray(co);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(co, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void font::draw(const char* text, float x, float y, float sx, float sy)
{
  const char *p;

  for(p = text; *p; p++) {
    if(FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
      continue;
 
    glTexImage2D(
		 GL_TEXTURE_2D,
		 0,
		 GL_RED,
         m_glyph->bitmap.width,
         m_glyph->bitmap.rows,
		 0,
		 GL_RED,
		 GL_UNSIGNED_BYTE,
         m_glyph->bitmap.buffer
		 );
 
    float x2 = x + m_glyph->bitmap_left * sx;
    float y2 = -y - m_glyph->bitmap_top * sy;
    float w = m_glyph->bitmap.width * sx;
    float h = m_glyph->bitmap.rows * sy;
 
    GLfloat box[4][4] = {
      {x2,     -y2    , 0, 0},
      {x2 + w, -y2    , 1, 0},
      {x2,     -y2 - h, 0, 1},
      {x2 + w, -y2 - h, 1, 1},
    };
 
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 
    x += (m_glyph->advance.x >> 6) * sx;
    y += (m_glyph->advance.y >> 6) * sy;
  }
}

void font::setColor(shader s,float r, float g, float b, float a)
{
   GLfloat color[4] = {r,g,b,a};
   uint uniColor = glGetUniformLocation(s.getProgram(),"color");
    glUniform4fv(uniColor, 1, color);

}

void font::setFontSize(int size)
{
  FT_Set_Pixel_Sizes(m_face, 0, size);
}

void font::end()
{
  glDisable(GL_BLEND);
}

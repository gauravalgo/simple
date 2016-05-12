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
#include "../maths/vec2.h"
#include <iostream>
#include <map>
#include <string>

#include "../../deps/glew/include/GL/glew.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace simple;
using namespace simple::graphics;

#include "shader.h"

font::font():
  r(1),
  g(1),
  b(1),
  a(1)
{}

font::~font()
{
  // Destroy FreeType once we're finished
  FT_Done_Face(face);
  //FT_Done_FreeType(ft);
}

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
  GLuint TextureID;   // ID handle of the glyph texture
  vec2 Size;    // Size of glyph
  vec2 Bearing;  // Offset from baseline to left/top of glyph
  GLuint Advance;    // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;
GLuint vbo;

uint texture;
void font::load(FT_Library ft, shader* s, const char* fontPath, float size)
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if(FT_New_Face(ft, fontPath, 0, &face)){
    LOG("Error: Could not load font " << fontPath);
    return;
  }

  // Set size to load glyphs as
  FT_Set_Pixel_Sizes(face, 0, size);

  // Disable byte-alignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Load first 128 characters of ASCII set
  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    FT_GlyphSlot g = face->glyph;
    // Generate texture
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      g->bitmap.width,
      g->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      g->bitmap.buffer
      //face->glyph->bitmap.buffer
      );
    
    // Now store character for later use
    Character character = {
      texture,
      vec2(g->bitmap.width, g->bitmap.rows),
      vec2(g->bitmap_left, g->bitmap_top),
      g->advance.x
    };
    Characters.insert(std::pair<GLchar, Character>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  m_co = glGetAttribLocation(s->getProgram(), "position");
  glEnableVertexAttribArray(m_co);
  glVertexAttribPointer(m_co, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

  uint m_color_attribute = glGetAttribLocation(s->getProgram(), "color");
  glEnableVertexAttribArray(m_color_attribute);
  glVertexAttribPointer(m_color_attribute, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(2*sizeof(float)));

  uint m_tex_attribute = glGetAttribLocation(s->getProgram(), "texcoords");
  glEnableVertexAttribArray(m_tex_attribute);
  glVertexAttribPointer(m_tex_attribute, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
}

void font::draw(std::string text, shader* s, float x, float y, float sx, float sy, float r, float g, float b, float a)
{
  glUseProgram(s->getProgram());
  glActiveTexture(GL_TEXTURE0);

  // Iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];

    GLfloat xpos = x + ch.Bearing.x * sx;
    GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * sy;

    GLfloat w = ch.Size.x * sx;
    GLfloat h = ch.Size.y * sy;
    float scale = 1.0f / 255.0f;
    // Update VBO for each character
    GLfloat vertices[6][8] = {
      { xpos,     ypos - h,   scale * r, scale * g, scale * b, scale * a, 0.0, 0.0 },
      { xpos,     ypos,       scale * r, scale * g, scale * b, scale * a, 0.0, 1.0 },
      { xpos + w, ypos,       scale * r, scale * g, scale * b, scale * a, 1.0, 1.0 },

      { xpos,     ypos - h,   scale * r, scale * g, scale * b, scale * a, 0.0, 0.0 },
      { xpos + w, ypos,       scale * r, scale * g, scale * b, scale * a, 1.0, 1.0 },
      { xpos + w, ypos - h,   scale * r, scale * g, scale * b, scale * a, 1.0, 0.0 }
    };

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_DYNAMIC_DRAW);

    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    x += (ch.Advance >> 6) * sx;

  }
}

void font::setFontSize(int size)
{
  FT_Set_Pixel_Sizes(face, 0, size);
}

void font::begin()
{
  glEnable(GL_BLEND);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void font::end()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
}

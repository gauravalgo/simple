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

#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"
#include <iostream>
#include <string>

namespace simple
{
  namespace graphics
  {
    class font
    {
    public:
      font();
      ~font();
    private:
      FT_Face face;
      FT_GlyphSlot m_glyph;
      int m_coord;
      int m_tex;
      uint m_co;
      uint m_unitex;
      float r,g,b,a;
    public:
      void load(FT_Library ft, shader* s, const char* fontPath, float size);
      void draw(std::string text, shader* s, float x, float y, float sx, float sy, float r, float g, float b, float a);
      void setFontSize(int size);
      void begin();
      void end();
    };
  }
}

#endif

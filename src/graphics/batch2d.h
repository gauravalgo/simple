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

#ifndef BATCH2D_H
#define BATCH2D_H

#include "shader.h"
#include "../maths/vec3.h"
#include "../maths/mat4.h"
#include "../utils/definitions.h"
#include "mesh.h"
#include "texture2D.h"

using namespace simple::maths;

namespace simple
{
  namespace graphics
  {
    class batch2d
    {
    public:
      batch2d(shader* shader, int size);
      batch2d(shader* shader);
      batch2d();
      ~batch2d();

    private:
      float m_vertices[40000 * 5 * 7];

      unsigned int m_vbo;
      unsigned int m_ebo;

      unsigned int m_position_attribute;
      unsigned int m_color_attribute;
      unsigned int m_tex_attribute;
      int m_index;
      int m_numSprite;
      int m_SIZE;
      shader* m_shader;
      uint m_modelAttrib;
    public:
      void begin();
      void end();
      void renderMesh();
      void draw(float x, float y, float width, float height);
      void draw(float x, float y, float width, float height, float r, float g, float b, float a);
      void create();
    public:
      void setShader(shader* s){m_shader = s;}
    };
  }
}
#endif

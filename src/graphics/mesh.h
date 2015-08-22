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

#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "shader.h"
#include <vector>
#include <iostream>

#include "../utils/definitions.h"

namespace simple
{
  namespace graphics
  {
    class mesh
    {
    public:
      mesh();
      ~mesh();
    private:
      int m_position_attribute;
      int m_color_attribute;
      int m_tex_attribute;
      uint m_vbo;
      uint m_ebo;
      shader* m_shader;
      float* m_vertices;
      int m_sizeV;
      unsigned short* m_indices;
      unsigned short m_sizeI;
    public:
      void create(shader* a_shader, float vertices[], int sizeV,unsigned short indices[], short sizeI);
      void allowVerticesChanges(); //TODO find a better name?
       void allowIndicesChanges(); //TODO find a better name?
      void setVertices(float* v, int sV){m_vertices = v; m_sizeV = sV;}
      void setIndices(unsigned short* i, unsigned short sI){m_indices = i; m_sizeI = sI;}

      void begin();
      void end();
      void draw(int count);
    };
  }
}
#endif

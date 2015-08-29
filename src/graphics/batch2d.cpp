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

#include "batch2d.h"

#include "shader.h"
#include "../maths/vec3.h"
#include "../maths/mat4.h"
#include "../utils/definitions.h"
#include "mesh.h"
#include "texture2D.h"

#include <cmath>
#include <GL/gl.h>

using namespace simple;
using namespace simple::graphics;

batch2d::batch2d(shader* shader):
  m_SIZE(40000)
{
  m_shader = shader;
}

batch2d::batch2d(shader* shader, int size)
{
  m_shader = shader;
  m_SIZE = size;
}

batch2d::batch2d(){}

batch2d::~batch2d()
{
  SAFE_DELETE(m_shader);
  glDisableVertexAttribArray(m_tex_attribute);
  glDisableVertexAttribArray(m_position_attribute);
  glDisableVertexAttribArray(m_color_attribute);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}

void batch2d::create()
{
  glGenBuffers(2, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

  m_position_attribute = glGetAttribLocation(m_shader->getProgram(), "position");
  glEnableVertexAttribArray(m_position_attribute);
  glVertexAttribPointer(m_position_attribute, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

  m_color_attribute = glGetAttribLocation(m_shader->getProgram(), "color");
  glEnableVertexAttribArray(m_color_attribute);
  glVertexAttribPointer(m_color_attribute, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(2*sizeof(float)));

  m_tex_attribute = glGetAttribLocation(m_shader->getProgram(), "texcoords");
  glEnableVertexAttribArray(m_tex_attribute);
  glVertexAttribPointer(m_tex_attribute, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

  m_index = 0;
  m_numSprite = 0;

  int l = m_SIZE*6;
  unsigned short m_indices[l];
  short j = 0;
  for (int i = 0; i < l; i += 6, j += 4) {
    m_indices[i + 0] = (short)(j + 0);
    m_indices[i + 1] = (short)(j + 1);
    m_indices[i + 2] = (short)(j + 2);
    m_indices[i + 3] = (short)(j + 2);
    m_indices[i + 4] = (short)(j + 3);
    m_indices[i + 5] = (short)(j + 0);
  }

  glGenBuffers(2, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

}

void batch2d::draw( float x, float y, float width, float height)
{
  if(m_numSprite >= m_SIZE){
    LOG("Error: You're trying to draw more than " << m_SIZE << " sprites!");
    return;
  }

  // if(texture != m_texture)
  //  m_texture = texture;

  m_vertices[m_index++] = -width+x;
  m_vertices[m_index++] = -height+y;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = +width+x;
  m_vertices[m_index++] = -height+y;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = +width+x;
  m_vertices[m_index++] = +height+y;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = -width+x;
  m_vertices[m_index++] = +height+y;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 1;

  m_numSprite++;
}

void batch2d::draw(float x, float y, float width, float height, float r, float g, float b, float a)
{
  if(m_numSprite >= m_SIZE){
    LOG("Error: You're trying to draw more than " << m_SIZE << " sprites!");
    return;
  }

  m_vertices[m_index++] = -width+x;
  m_vertices[m_index++] = -height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = +width+x;
  m_vertices[m_index++] = -height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = +width+x;
  m_vertices[m_index++] = +height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = -width+x;
  m_vertices[m_index++] = +height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 1;

  m_numSprite++;
}


void batch2d::renderMesh()
{
  if(m_numSprite > 0){
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
    // m_texture->bind();
    glDrawElements(GL_TRIANGLES, m_numSprite * 6, GL_UNSIGNED_SHORT, 0);

  }
}

void batch2d::begin()
{
  glDepthMask(false);

  m_index = 0;
  m_numSprite = 0;

}

void batch2d::end()
{
  glDepthMask(true);
  m_index = 0;
  m_numSprite = 0;
}

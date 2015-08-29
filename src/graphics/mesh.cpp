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

#include "mesh.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../utils/definitions.h"
#include <vector>
#include <iostream>

using namespace simple;
using namespace simple::graphics;

mesh::mesh():
  m_position_attribute(0),
  m_color_attribute(0),
  m_vbo(0),
  m_tex_attribute(0)
{

}

mesh::~mesh()
{
  glDisableVertexAttribArray(m_tex_attribute);
  glDisableVertexAttribArray(m_position_attribute);
  glDisableVertexAttribArray(m_color_attribute);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}

void mesh::create(shader* a_shader,float vertices[], int sizeV, unsigned short indices[], short sizeI)
{
  m_vertices = vertices;
  m_sizeV = sizeV;

  m_indices = indices;
  m_sizeI = sizeI;

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_sizeV, m_vertices, GL_STATIC_DRAW);

  m_position_attribute = glGetAttribLocation(a_shader->getProgram(), "position");
  glEnableVertexAttribArray(m_position_attribute);
  glVertexAttribPointer(m_position_attribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);

  m_color_attribute = glGetAttribLocation(a_shader->getProgram(), "color");
  glEnableVertexAttribArray(m_color_attribute);
  glVertexAttribPointer(m_color_attribute, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));

  m_tex_attribute = glGetAttribLocation(a_shader->getProgram(), "texcoords");
  glEnableVertexAttribArray(m_tex_attribute);
  glVertexAttribPointer(m_tex_attribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));

  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeI, m_indices, GL_STATIC_DRAW);
}

void mesh::allowVerticesChanges()
{
  //this allows us to change the vertices size/attributes on fly
  glBufferData(GL_ARRAY_BUFFER, m_sizeV, m_vertices, GL_DYNAMIC_DRAW);
}

void mesh::allowIndicesChanges()
{
  //this allows us to change the indices size/attributes on fly
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeI, m_indices, GL_DYNAMIC_DRAW);
}

void mesh::draw(int count)
{
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, count);
}

void mesh::begin()
{
  glEnableVertexAttribArray(m_position_attribute);
  glEnableVertexAttribArray(m_color_attribute);
  glEnableVertexAttribArray(m_tex_attribute);
}

void mesh::end()
{
  glDisableVertexAttribArray(m_tex_attribute);
  glDisableVertexAttribArray(m_position_attribute);
  glDisableVertexAttribArray(m_color_attribute);
}




























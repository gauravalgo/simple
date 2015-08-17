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

mesh::mesh():
    m_position_attribute(0),
    m_color_attribute(0)
{

}

mesh::~mesh()
{
    glDisableVertexAttribArray(m_position_attribute);
    glDisableVertexAttribArray(m_color_attribute);
}

void mesh::create(shader& a_shader,float vertices[], int sizeV, unsigned short indices[], short sizeI)
{
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    m_position_attribute = glGetAttribLocation(a_shader.getProgram(), "position");
    glEnableVertexAttribArray(m_position_attribute);
    glVertexAttribPointer(m_position_attribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);

    m_color_attribute = glGetAttribLocation(a_shader.getProgram(), "color");
    glEnableVertexAttribArray(m_color_attribute);
    glVertexAttribPointer(m_color_attribute, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));

    m_tex_attribute = glGetAttribLocation(a_shader.getProgram(), "texcoords");
    glEnableVertexAttribArray(m_tex_attribute);
    glVertexAttribPointer(m_tex_attribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));
    m_vertices = vertices;

    glBufferData(GL_ARRAY_BUFFER, sizeV, vertices, GL_STATIC_DRAW);

    m_indices = indices;

    uint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeI, indices, GL_STATIC_DRAW);

}

void mesh::draw(int count)
{
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, count);
}






























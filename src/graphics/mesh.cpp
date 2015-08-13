#include "mesh.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../graphics/definitions.h"
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

void mesh::unbind()
{
    glDisableVertexAttribArray(m_position_attribute);
    glDisableVertexAttribArray(m_color_attribute);
}

void mesh::create(shader& a_shader,float vertices[], int sizeV, short indices[], short sizeI)
{
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    m_position_attribute = glGetAttribLocation(a_shader.getProgram(), "position");
    glEnableVertexAttribArray(m_position_attribute);
    glVertexAttribPointer(m_position_attribute, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    m_color_attribute = glGetAttribLocation(a_shader.getProgram(), "color");
    glEnableVertexAttribArray(m_color_attribute);
    glVertexAttribPointer(m_color_attribute, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    glBufferData(GL_ARRAY_BUFFER, sizeV, vertices, GL_STATIC_DRAW);

    uint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeI, indices, GL_STATIC_DRAW);
}

void mesh::draw()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    //glDrawArrays(GL_TRIANGLES,0,6);
}






























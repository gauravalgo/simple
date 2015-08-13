#include "mesh.h"

#include "../graphics/definitions.h"

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

/*
void mesh::bind(shader* a_shader)
{
    m_shader = a_shader;
}
*/

void mesh::unbind()
{
    glDisableVertexAttribArray(m_position_attribute);
    glDisableVertexAttribArray(m_color_attribute);
}

void mesh::create(shader& a_shader, float vertices[], short indices[])
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

    glBufferData(GL_ARRAY_BUFFER, (sizeof(&vertices) * (sizeof(vertices) * sizeof(float))), vertices, GL_STATIC_DRAW);

    uint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(&indices) * (sizeof(indices) * sizeof(short))), indices, GL_STATIC_DRAW);
}

void mesh::draw()
{
 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

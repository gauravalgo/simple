#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "shader.h"
#include <vector>
#include <iostream>


namespace simple
{
class mesh
{
public:
    mesh();
    ~mesh();
private:
int m_position_attribute;
int m_color_attribute;
shader* m_shader;
public:
float* m_vertices;
short* m_indices;
    void create(shader &a_shader, float vertices[], int sizeV, short indices[], short sizeI);
    void unbind();
    void draw();
};
}
#endif

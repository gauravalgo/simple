#ifndef MESH_H
#define MESH_H

#include "shader.h"

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
    void create(shader &a_shader, float vertices[], short indices[]);
    //void bind(shader *a_shader);
    void unbind();
    void draw();
};
}
#endif

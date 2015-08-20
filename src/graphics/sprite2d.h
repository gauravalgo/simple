#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "mesh.h"
#include "shader.h"

namespace simple
{
namespace graphics
{
class sprite2d
{
  public:
    sprite2d();
    ~sprite2d();
public:
    void create(shader* s, float x, float y);
    void draw(float x, float y, int count);
};
}
}

#endif

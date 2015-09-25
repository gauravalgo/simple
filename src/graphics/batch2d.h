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
    batch2d();
    ~batch2d();

  private:
    float m_vertices[40000 * 5 * 7];

    float _sin;
    float _cos;

    float px1;
    float py1;
    float px2;
    float py2;
    float px3;
    float py3;
    float px4;
    float py4;

    float p1x;
    float p1y;
    float p2x;
    float p2y;
    float p3x;
    float p3y;
    float p4x;
    float p4y;

    float fx;
    float fy;
    float fx2;
    float fy2;

    float u,v,u2,v2;
    float texWidth,texHeight;
    float r,g,b,a;

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
    texture2D* m_texture;
  public:
    void begin();
    void end();
    void setColor(float r, float g, float b, float a);
    void renderMesh();
    void draw(float x, float y, float width, float height,float rotation,float originX,float originY,int srcX, int srcY, int srcWidth,int srcHeight, bool flipX, bool flipY, float scaleX, float scaleY);
    void draw(float x, float y, float width, float height);
    void draw(float x, float y, float width, float height, float rotation, float originX, float originY);
    void draw(float x, float y, float width, float height, float rotation, float originX, float originY, float r, float g, float b, float a);
    void draw(float x, float y, float width, float height, float rotation, float originX, float originY, float r,
              float g, float b, float a, float* texturecoords);
    void draw(float x, float y, float width, float height, float r, float g, float b, float a);
    void draw(float x, float y, float width, float height, float* texturecoords, float r, float g, float b, float a);
    void create(shader* s, int limit);
  public:
    void setShader(shader* s){m_shader = s;}
};
}
}
#endif

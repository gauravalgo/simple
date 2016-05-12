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
#include "../../deps/glew/include/GL/glew.h"

using namespace simple;
using namespace simple::graphics;

batch2d::batch2d():
  m_SIZE(40000),
  r(1),
  g(r),
  b(1),
  a(1)
{}

batch2d::~batch2d()
{
  SAFE_DELETE(m_shader);
  glDisableVertexAttribArray(m_tex_attribute);
  glDisableVertexAttribArray(m_position_attribute);
  glDisableVertexAttribArray(m_color_attribute);
}

void batch2d::create(shader* s, int limit)
{
  m_shader = s;
  m_SIZE = limit;

  glGenBuffers(1, &m_vbo);
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

  px1 = width + x;
  py1 = height + y;

  px2 = -width + x;
  py2 = -height + y;

  m_vertices[m_index++] = px2;
  m_vertices[m_index++] = py2;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = px1;
  m_vertices[m_index++] = py2;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = px1;
  m_vertices[m_index++] = py1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = px2;
  m_vertices[m_index++] = py1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 1;

  m_numSprite++;
}

void batch2d::draw(float x, float y, float width, float height, float rotation, float originX, float originY)
{}

float ex1;
float ey1;
float ex2;
float ey2;
float ex3;
float ey3;
float ex4;
float ey4;

void batch2d::draw(float x, float y, float width, float height, float rotation, float originX, float originY, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY, float scaleX, float scaleY)
{
  if(m_numSprite >= m_SIZE){
    LOG("Error: You're trying to draw more than " << m_SIZE << " sprites!");
    return;
  }
  float ox = x + originX;
  float oy = y + originY;
  if(rotation != 0){
    _cos = cos(RADIANS(rotation));
    _sin = sin(RADIANS(rotation));
    //corners calculation
    fx = -srcWidth;
    fy = -srcHeight;
    fx2 = srcWidth;
    fy2 = srcHeight;

    // scale
    if (scaleX != 1 || scaleY != 1) {
      fx *= scaleX;
      fy *= scaleY;
      fx2 *= scaleX;
      fy2 *= scaleY;
    }
    //corners assigment
    p1x = fx;
    p1y = fy;
    p2x = fx2;
    p2y = fy;
    p3x = fx2;
    p3y = fy2;
    p4x = fx;
    p4y = fy2;

    //rotate each corner
    ex1 = _cos * p1x - _sin * p1y;
    ey1 = _sin * p1x + _cos * p1y;

    ex2 = _cos * p2x - _sin * p2y;
    ey2 = _sin * p2x + _cos * p2y;

    ex3 = _cos * p3x - _sin * p3y;
    ey3 = _sin * p3x + _cos * p3y;

    ex4 = ex1 + (ex3 - ex2);
    ey4 = ey3 - (ey2 - ey1);
    }
 else{
    ex1 = -srcWidth + x;
    ey1 = -srcHeight + y;

    ex2 = +srcWidth + x;
    ey2 = -srcHeight + y;

    ex3 = srcWidth + x;
    ey3 = srcHeight + y;

    ex4 = -srcWidth + x;
    ey4 = srcHeight + y;
  }

  ex1 += ox;
  ey1 += oy;
  ex2 += ox;
  ey2 += oy;
  ex3 += ox;
  ey3 += oy;
  ex4 += ox;
  ey4 += oy;

  //if(srcX >= 0 || srcY >= 0){
  //convert pixel's coordonates to shader's coordonates
  texWidth = 1.0f / width;
  texHeight = 1.0f / height;
  u = srcX * texWidth;
  v = (srcY + srcHeight) * texHeight;
  u2 = (srcX + srcWidth) * texWidth;
  v2 = srcY * texHeight;

  if (flipX) {
    float tmp = u;
    u = u2;
    u2 = tmp;
  }
  if (flipY) {
    float tmp = v;
    v = v2;
    v2 = tmp;
  }

  m_vertices[m_index++] = ex1;
  m_vertices[m_index++] = ey1;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = u;
  m_vertices[m_index++] = v;
  m_vertices[m_index++] = ex2;
  m_vertices[m_index++] = ey2;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = u;
  m_vertices[m_index++] = v2;
  m_vertices[m_index++] = ex3;
  m_vertices[m_index++] = ey3;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = u2;
  m_vertices[m_index++] = v2;
  m_vertices[m_index++] = ex4;
  m_vertices[m_index++] = ey4;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = u2;
  m_vertices[m_index++] = v;

  m_numSprite++;
}

void batch2d::setColor(float r, float g, float b, float a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

void batch2d::draw(float x, float y, float width, float height, float rotation, float originX, float originY,
                   float r, float g, float b, float a)
{
  if(m_numSprite >= m_SIZE){
    LOG("Error: You're trying to draw more than " << m_SIZE << " sprites!");
    return;
  }


  if(rotation != 0){
    _cos = cos(RADIANS(rotation));
    _sin = sin(RADIANS(rotation));

    fx = -originX;
    fy = -originY;
    fx2 = width - originX;
    fy2 = height - originY;

    p1x = fx;
    p1y = fy;
    p2x = fx;
    p2y = fy2;
    p3x = fx2;
    p3y = fy2;
    p4x = fx2;
    p4y = fy;

    px1 = p1x * _cos - p1y * _sin;
    py1 = p1x * _sin + p1y * _cos;

    px2 = p2x * _cos - p2y * _sin;
    py2 = p2x * _sin + p2y * _cos;

    px3 = p3x * _cos - p3y * _sin;
    py3 = p3x * _sin + p3y * _cos;

    px4 = px1 + (px3 - px2);
    py4 = py3 - (py2 - py1);

  }else{
    px1 = -width + x;
    py1 = -height + y;

    px2 = width + x;
    py2 = -height + y;

    px3 = width + x;
    py3 = height + y;

    px4 = -width + x;
    py4 = height + y;
  }

  px1 += (x + originX);
  py1 += (y + originY);
  px2 += (x + originX);
  py2 += (y + originY);
  px3 += (x + originX);
  py3 += (y + originY);
  px4 += (x + originX);
  py4 += (y + originY);

  m_vertices[m_index++] = px1;
  m_vertices[m_index++] = py1;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = px2;
  m_vertices[m_index++] = py2;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 0;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = px3;
  m_vertices[m_index++] = py3;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = px4;
  m_vertices[m_index++] = py4;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = 1;
  m_vertices[m_index++] = 0;

  m_numSprite++;
}


void batch2d::draw(float x, float y, float width, float height, float rotation, float originX, float originY, float r,
                   float g, float b, float a, float* texturecoords)
{
  if(m_numSprite >= m_SIZE){
    LOG("Error: You're trying to draw more than " << m_SIZE << " sprites!");
    return;
  }

  if(rotation != 0){
    _cos = cos(RADIANS(rotation));
    _sin = sin(RADIANS(rotation));

    fx = -originX;
    fy = -originY;
    fx2 = width - originX;
    fy2 = height - originY;

    p1x = fx;
    p1y = fy;
    p2x = fx;
    p2y = fy2;
    p3x = fx2;
    p3y = fy2;
    p4x = fx2;
    p4y = fy;

    px1 = p1x * _cos - p1y * _sin;
    py1 = p1x * _sin + p1y * _cos;

    px2 = p2x * _cos - p2y * _sin;
    py2 = p2x * _sin + p2y * _cos;

    px3 = p3x * _cos - p3y * _sin;
    py3 = p3x * _sin + p3y * _cos;

    px4 = px1 + (px3 - px2);
    py4 = py3 - (py2 - py1);

  }else{
    px1 = -width + x;
    py1 = -height + y;

    px2 = width + x;
    py2 = -height + y;

    px3 = width + x;
    py3 = height + y;

    px4 = -width + x;
    py4 = height + y;
  }

  px1 += x + originX;
  py1 += y + originY;
  px2 += x + originX;
  py2 += y + originY;
  px3 += x + originX;
  py3 += y + originY;
  px4 += x + originX;
  py4 += y + originY;


  m_vertices[m_index++] = px1;
  m_vertices[m_index++] = py1;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[0];
  m_vertices[m_index++] = texturecoords[1];
  m_vertices[m_index++] = px2;
  m_vertices[m_index++] = py2;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[2];
  m_vertices[m_index++] = texturecoords[3];
  m_vertices[m_index++] = px3;
  m_vertices[m_index++] = py3;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[4];
  m_vertices[m_index++] = texturecoords[5];
  m_vertices[m_index++] = px4;
  m_vertices[m_index++] = py4;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[6];
  m_vertices[m_index++] = texturecoords[7];

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

void batch2d::draw(float x, float y, float width, float height, float* texturecoords, float r, float g, float b, float a)
{
  if(m_numSprite >= m_SIZE){
    LOG("Error: You're trying to draw more than " << m_SIZE << " sprites!");
    return;
  }

  // if(texture != m_texture)
  //  m_texture = texture;

  m_vertices[m_index++] = -width+x;
  m_vertices[m_index++] = -height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[0];
  m_vertices[m_index++] = texturecoords[1];
  m_vertices[m_index++] = +width+x;
  m_vertices[m_index++] = -height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[2];
  m_vertices[m_index++] = texturecoords[3];
  m_vertices[m_index++] = +width+x;
  m_vertices[m_index++] = +height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[4];
  m_vertices[m_index++] = texturecoords[5];
  m_vertices[m_index++] = -width+x;
  m_vertices[m_index++] = +height+y;
  m_vertices[m_index++] = r;
  m_vertices[m_index++] = g;
  m_vertices[m_index++] = b;
  m_vertices[m_index++] = a;
  m_vertices[m_index++] = texturecoords[6];
  m_vertices[m_index++] = texturecoords[7];

  m_numSprite++;
}


void batch2d::renderMesh()
{
  if(m_numSprite > 0){
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
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

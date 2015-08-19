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

using namespace simple;
using namespace simple::graphics;

unsigned short elements[] =
  { 0, 1, 2,
    2, 3, 0
  };


batch2d::batch2d()
{
  m_texture = new texture2D();
  m_mesh = new mesh();

}

void batch2d::create()
{
    m_mesh->create(m_shader,m_vertices,sizeof(m_vertices),elements,sizeof(elements));
}

batch2d::~batch2d()
{
  SAFE_DELETE(m_mesh);
  SAFE_DELETE(m_texture);
}

void batch2d::begin()
{
    glDepthMask(false);
    index = 0;
}

void batch2d::end()
{
    glDepthMask(true);
    m_texture = NULL;
    index = 0;
}


//TODO optimisate this(how?) and exapand it

void batch2d::draw(texture2D* texture, float x, float y)
{

    if(texture != m_texture)
    {
        switchTexture(texture);
    }else if (index == 350) renderMesh();

  int width = texture->getWidth();
  int height = texture->getHeight();

  //p
  m_vertices[index++] = -width+x;
  m_vertices[index++] = -height+y;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 0;
  m_vertices[index++] = 0;


  m_vertices[index++] = +width+x;
  m_vertices[index++] = -height+y;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 0;


  m_vertices[index++] = +width+x;
  m_vertices[index++] = +height+y;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = -width+x;
  m_vertices[index++] = +height+y;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 1;
  m_vertices[index++] = 0;
  m_vertices[index++] = 1;

}

void batch2d::switchTexture(texture2D *texture){
 renderMesh();
 m_texture = texture;
}

void batch2d::renderMesh()
{
    if(index == 0) return;

    m_texture->bind();
    m_mesh->setVertices(m_vertices,sizeof(m_vertices));
    m_mesh->draw(6);

    index = 0;
}



/*
//p
m_vertices[0] = -width+x;
m_vertices[1] = -height+y;

//c
m_vertices[2] = 1;
m_vertices[3] = 1;
m_vertices[4] = 1;
//t
m_vertices[5] = 0;
m_vertices[6] = 0;

//p
m_vertices[7] = +width+x;
m_vertices[8] = -height+y;

//c
m_vertices[9] = 1;
m_vertices[10] = 1;
m_vertices[11] = 1;
//t
m_vertices[12] = 1;
m_vertices[13] = 0;

//p
m_vertices[14] = +width+x;
m_vertices[15] = +height+y;

//c
m_vertices[16] = 1;
m_vertices[17] = 1;
m_vertices[18] = 1;
//t
m_vertices[19] = 1;
m_vertices[20] = 1;

//p
m_vertices[21] = -width+x;
m_vertices[22] = +height+y;
//c

m_vertices[23] = 1;
m_vertices[24] = 1;
m_vertices[25] = 1;
//t
m_vertices[26] = 0;
m_vertices[27] = 1;
  */








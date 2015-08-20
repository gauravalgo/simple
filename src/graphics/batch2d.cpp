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

#include <vector>

using namespace simple;
using namespace simple::graphics;

using std::vector;

batch2d::batch2d(shader* shader)
{
  m_shader = shader;
}

batch2d::~batch2d()
{
  SAFE_DELETE(m_shader);
  SAFE_DELETE(m_mesh);
}

void batch2d::create(float x,float y)
{
  m_model.setToIdentity();
  m_modelAttrib = glGetUniformLocation(m_shader->getProgram(), "model");

  int width = 16;
  int height = 16;
   	
  m_vertices[0] = -width;
  m_vertices[1] = -height;

  //c
  m_vertices[2] = 1;
  m_vertices[3] = 1;
  m_vertices[4] = 1;
  //t
  m_vertices[5] = 0;
  m_vertices[6] = 0;

  //p
  m_vertices[7] = +width;
  m_vertices[8] = -height;

  //c
  m_vertices[9] = 1;
  m_vertices[10] = 1;
  m_vertices[11] = 1;
  //t
  m_vertices[12] = 1;
  m_vertices[13] = 0;

  //p
  m_vertices[14] = +width;
  m_vertices[15] = +height;

  //c
  m_vertices[16] = 1;
  m_vertices[17] = 1;
  m_vertices[18] = 1;
  //t
  m_vertices[19] = 1;
  m_vertices[20] = 1;

  //p
  m_vertices[21] = -width;
  m_vertices[22] = +height;
  //c

  m_vertices[23] = 1;
  m_vertices[24] = 1;
  m_vertices[25] = 1;
  //t
  m_vertices[26] = 0;
  m_vertices[27] = 1;
  unsigned short i[] =
    { 0, 1, 2,
      2, 3, 0
    };

  m_mesh = new mesh();
  m_mesh->create(m_shader, m_vertices, sizeof(m_vertices), i, sizeof(i));
}

void batch2d::draw(texture2D* texture, float x, float y)
{
  m_model.translate(vec3(x,y,0));
  glUniformMatrix4fv(m_modelAttrib, 1, GL_FALSE, m_model.dataBlock()); //this is very expensive . TODO find a better way (using vertices?)?

  texture->bind();
  m_mesh->draw(6);
  texture->unbind();

}

void batch2d::begin()
{
  glDepthMask(false);
}

void batch2d::end()
{
  glDepthMask(true);

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








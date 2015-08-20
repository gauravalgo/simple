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
#include "sprite2d.h"

using namespace simple::maths;

namespace simple
{
  namespace graphics
  {
    class batch2d
    {
    public:
      batch2d(shader* shader);
      ~batch2d();
    private:
      shader* m_shader;
      mesh* m_mesh;
      float m_vertices[28];
      mat4 m_model;
      uint m_modelAttrib;
    public:
      void begin();
      void end();
      void draw(texture2D* texture,float x, float y);
      void create(float x, float y);
    public:
      void setShader(shader* s){m_shader = s;}
    };
  }
}
#endif

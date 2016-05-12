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

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include "../../deps/glew/include/GL/glew.h"
#include "../utils/definitions.h"
#include "../maths/mat4.h"

namespace simple
{
  using namespace simple::maths;
  namespace graphics
  {
    class shader
    {
    public:
      shader();
      ~shader();
    private:
      uint m_vertexShaderID;
      uint m_fragmentShaderID;
      uint m_program;
      bool m_linked;
      std::string mFilenameVertexShader, mFilenameFragmentShader;
    public:
      void create(const char* vertexShaderFilename,
		  const char* fragmentShaderFilename);
      void sendUniformLocation(const char* name, mat4 data);
      void bind();
      void unbind();
    public:
      bool getLinked(){return m_linked;}
      uint getProgram(){return m_program;}
    };
  }
}
#endif

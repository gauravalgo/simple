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

#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "../utils/definitions.h"
#include "../maths/mat4.h"

using namespace simple;
using namespace simple::graphics;
using namespace simple::maths;

using namespace std;

shader::shader():
  m_linked(false)
{

}

shader::~shader()
{
  glDeleteProgram(m_program);
  glDeleteShader(m_vertexShaderID);
  glDeleteShader(m_fragmentShaderID);
  glUseProgram(0);
}

// Create the shader
void shader::create(const char* vertexShaderFilename,
                    const char* fragmentShaderFilename) {

  m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(m_vertexShaderID, 1, &vertexShaderFilename, 0);
  glShaderSource(m_fragmentShaderID, 1, &fragmentShaderFilename, 0);

  glCompileShader(m_vertexShaderID);
  glCompileShader(m_fragmentShaderID);

  GLint compileStatus;

  glGetShaderiv(m_vertexShaderID,GL_COMPILE_STATUS,&compileStatus);
  if(compileStatus != GL_TRUE)
    {
      GLint info;
      glGetShaderiv(m_vertexShaderID,GL_INFO_LOG_LENGTH,&info);
      GLchar* buffer = new GLchar[info];

      int bufferSize;
      glGetShaderInfoLog(m_vertexShaderID, info,&bufferSize,buffer);

      LOG("vertex shader compile error " << buffer);

      delete[] buffer;
      glDeleteShader(m_vertexShaderID);
      glDeleteShader(m_fragmentShaderID);
    }

  glGetShaderiv(m_fragmentShaderID,GL_COMPILE_STATUS,&compileStatus);
  if(compileStatus != GL_TRUE)
    {
      GLint info;
      glGetShaderiv(m_fragmentShaderID,GL_INFO_LOG_LENGTH,&info);
      GLchar* buffer = new GLchar[info];

      int bufferSize;
      glGetShaderInfoLog(m_fragmentShaderID, info,&bufferSize,buffer);

      LOG("fragment shader compile error " << buffer);

      delete[] buffer;
      glDeleteShader(m_vertexShaderID);
      glDeleteShader(m_fragmentShaderID);
    }

  m_program = glCreateProgram();
  glAttachShader(m_program, m_vertexShaderID);
  glAttachShader(m_program, m_fragmentShaderID);

  glLinkProgram(m_program);

  GLint isLinked = 0;
  glGetProgramiv(m_program, GL_LINK_STATUS, (int *)&isLinked);
  if(isLinked == GL_FALSE)
    {
      GLint info = 0;
      glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &info);
      GLchar* buffer=  new GLchar[info];

      int bufferSize;
      glGetProgramInfoLog(m_program, info, &bufferSize, buffer);

      glDeleteProgram(m_program);
      glDeleteShader(m_vertexShaderID);
      glDeleteShader(m_fragmentShaderID);
    }
  if (DEBBUG)
    LOG("Shader compiled and ready to be used!");
}

void shader::sendUniformLocation(const char* name, mat4 data)
{
  uint uni = glGetUniformLocation(m_program, name);
  glUniformMatrix4fv(uni, 1, GL_FALSE, data.dataBlock());
}

void shader::bind()
{
  if(m_program == 0)
    LOG("Error: shader, create method must be called first!");
  m_linked = true;
  glUseProgram(getProgram());
}

void shader::unbind()
{
  // glUseProgram(0); wrong
}




















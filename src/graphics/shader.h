#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <GL/glew.h>

#include "../maths/vector2.h"
#include "../maths/vector3.h"
#include "../maths/vector4.h"
#include "../maths/matrix4.h"

namespace simple
{
  class shader
  {
  public:
    shader();
    ~shader();
  private:
    unsigned int mProgramObjectID;
    std::string mFilenameVertexShader, mFilenameFragmentShader;
  public:
    void create(const char* vertexShaderFilename,
        const char* fragmentShaderFilename);
  public:
    unsigned int getProgram(){return mProgramObjectID;}
  };
}

#endif

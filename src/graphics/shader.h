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
    shader(std::string vertexShaderFilename,std::string fragmentShaderFilename);
    ~shader();
  private:
    unsigned int mProgramObjectID;
    std::string mFilenameVertexShader, mFilenameFragmentShader;
  public:

    // Create the shader
    bool create(const std::string vertexShaderFilename,
		const std::string fragmentShaderFilename);

    // Clear the shader
    void destroy();

    // Bind the shader
    void bind() const;

    // Unbind the shader
    void unbind() const;

    // Return the location of a uniform variable inside a shader program
    int getUniformLocation(const std::string& variableName) const;

    // Set a float uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setFloatUniform(const std::string& variableName, float value) const;

    // Set an int uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setIntUniform(const std::string& variableName, int value) const;

    // Set a vector 2 uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setVector2Uniform(const std::string& variableName, const vector2& v) const;

    // Set a vector 3 uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setVector3Uniform(const std::string& variableName, const vector3& v) const;

    // Set a vector 4 uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setVector4Uniform(const std::string& variableName, const vector4 &v) const;

    // Set a 3x3 matrix uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setMatrix3x3Uniform(const std::string& variableName, const float* matrix,
			     bool transpose = false) const;

    // Set a 4x4 matrix uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setMatrix4x4Uniform(const std::string& variableName, const float* matrix,
			     bool transpose = false) const;

    // Set a 4x4 matrix uniform value to this shader (be careful if the uniform is not
    // used in the shader, the compiler will remove it, then when you will try
    // to set it, an assert will occur)
    void setMatrix4x4Uniform(const std::string& variableName, const matrix4& matrix) const;

    // Return true if the needed OpenGL extensions are available
    static bool checkOpenGLExtensions();
  };

}

#endif

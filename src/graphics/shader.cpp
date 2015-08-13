#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "definitions.h"

using namespace simple;
using namespace std;

shader::shader():
  mProgramObjectID(0)
{

}

shader::~shader()
{

}

// Create the shader
void shader::create(const char* vertexShaderFilename,
                    const char* fragmentShaderFilename) {

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShaderID, 1, &vertexShaderFilename, 0);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderFilename, 0);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    GLint compileStatus;

    glGetShaderiv(vertexShaderID,GL_COMPILE_STATUS,&compileStatus);
    if(compileStatus != GL_TRUE)
    {
        GLint info;
        glGetShaderiv(vertexShaderID,GL_INFO_LOG_LENGTH,&info);
        GLchar* buffer = new GLchar[info];

        int bufferSize;
        glGetShaderInfoLog(vertexShaderID, info,&bufferSize,buffer);

        std::cout << buffer << std::endl;

        delete[] buffer;
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    glGetShaderiv(fragmentShaderID,GL_COMPILE_STATUS,&compileStatus);
    if(compileStatus != GL_TRUE)
    {
        GLint info;
        glGetShaderiv(fragmentShaderID,GL_INFO_LOG_LENGTH,&info);
        GLchar* buffer = new GLchar[info];

        int bufferSize;
        glGetShaderInfoLog(fragmentShaderID, info,&bufferSize,buffer);

        std::cout << buffer << std::endl;

        delete[] buffer;
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShaderID);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint info = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info);
        GLchar* buffer=  new GLchar[info];

        int bufferSize;
        glGetProgramInfoLog(program, info, &bufferSize, buffer);

        glDeleteProgram(program);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    glUseProgram(program);

    mProgramObjectID = program;

    std::cout<<"Shader compiled and ready to be used!" << std::endl;
}





















#include <iostream>

#include "window/sdl_window.h"
#include "graphics/shader.h"
#include "graphics/object3D.h"
#include "maths/vector3.h"
#include "graphics/definitions.h"

#include <GL/glew.h>

using namespace simple;

const char* frag =
"#version 130\n"
"uniform vec3 triangleColor;"
"out vec4 outColor;"
"void main(void) {"
"gl_FragColor = vec4(triangleColor, 1.0);"
"}";

const char* vert =
"#version 130\n"
"in vec2 position;"
"void main(void) {"
 "   gl_Position = vec4(position,0.0f,1.0f);"
"}";


int main()
{

    sdl_window window;

    window.makeWindow("Simple", -1, -1, 800, 680);

    glEnable(GL_DEPTH);

    shader* s = new shader();
    s->create(vert,frag);

    float data[] = {
         0.0f,  0.5f, // Vertex 1 (X, Y)
         0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };
    GLfloat points[]={-0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5};

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);


    GLint posAttrib = glGetAttribLocation(s->getProgram(), "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    //Get the color
    GLint color = glGetUniformLocation(s->getProgram(), "triangleColor");
    //Do stuff with it
    glUniform3f(color,0.0,1.0f,0.0f);

    //glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);

    while(window.getRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,1);

        //glDrawArrays(GL_TRIANGLE_FAN,0,5);

        glDrawArrays(GL_TRIANGLES,0,3);

        window.update();

    }
    glDisableVertexAttribArray(posAttrib);

    window.quit();
    SAFE_DELETE(s);
    return 0;
}


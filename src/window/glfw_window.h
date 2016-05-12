#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "../../deps/glew/include/GL/glew.h"
#include "../../deps/glfw/include/GLFW/glfw3.h"

#include "../maths/vec2.h"

using namespace simple::maths;

namespace simple
{

  class glfw_window
  {
  public:
    glfw_window();
    ~glfw_window();
  public:
    GLFWwindow* window;
  public:
    void create(const char* title, int width, int height, bool fullscreen, bool resizable);
    void update();
    void setDeltaTime(float dt){m_delta = dt;}
    //@parm x: -1 = find center @parm y: -1 = find center
    void setPosition(int x, int y);
    void setTitle(const char* title);
    void setVisible(bool visible);
    void setVSync(bool value){m_vsync = value;}
    bool isFocused();
    void destroy();
    void initInput();
    void calculateDeltaTime();
    void setResizable(bool value);
  private:
    void calculateFPS();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  private:
    bool m_running;
    int m_width,m_height;
    float m_delta;
    bool m_vsync;
    float m_fps;
    const GLFWvidmode* m_mode;
  public:
    double m_px;
    double m_py;

    int getDownKey(int key);
    int getUpKey(int key);

    int getMousePressed(int v);
    int getMouseReleased(int v);


    float getDeltaTime();
    float getFPS();
    GLFWwindow* getWindow(){return window;}
    double getTicks();
    float getPointX();
    float getPointY();
    vec2 getPointerPosition();
    vec2 getMonitorSize();
    bool getVSync(){return m_vsync;}
    bool getRunning(){return m_running;}
    void setRunning(bool value){m_running = value;}
    int getWidth(){return m_width;}
    int getHeight(){return m_height;}
  };

}

#endif

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../window/glfw_window.h"

namespace simple
{
  namespace input
  {
    class keyboard
    {
    public:
      keyboard();
      ~keyboard();
    public:
      bool isKeyDown(const char* key);
      bool isKeyUp(const char* key);
    private:
      glfw_window* m_window;
    };
  }
}
#endif

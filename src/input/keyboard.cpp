#include "keyboard.h"

#include "../utils/definitions.h"

using namespace simple;
using namespace simple::input;

keyboard::keyboard()
{
  m_window = new glfw_window();
}

keyboard::~keyboard()
{
  SAFE_DELETE(m_window);
}

bool keyboard::isKeyDown(const char* key)
{
  
  return false;
}

bool keyboard::isKeyUp(const char* key)
{
  
  return false;
}

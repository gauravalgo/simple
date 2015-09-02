#include "pointer.h"

using namespace simple;
using namespace simple::input;

#include <iostream>
#include <string>

pointer::pointer()
{

}

pointer::~pointer()
{

}

int pointer::getPoint(std::string p)
{
        if(p == "1")
                return GLFW_MOUSE_BUTTON_1;
        if(p == "2")
                return GLFW_MOUSE_BUTTON_2;
        if(p == "3")
                return GLFW_MOUSE_BUTTON_3;
        if(p == "4")
                return GLFW_MOUSE_BUTTON_4;
        if(p == "5")
                return GLFW_MOUSE_BUTTON_5;
        if(p == "6")
                return GLFW_MOUSE_BUTTON_6;
        if(p == "7")
                return GLFW_MOUSE_BUTTON_7;
        if(p == "8")
                return GLFW_MOUSE_BUTTON_8;
        if(p == "right")
                return 0;
        if(p == "left")
                return 1;
        if(p == "middle")
                return 2;
        return 0;
}

bool pointer::isPressed(std::string n)
{
        if(c.getWindow()->getMousePressed(getPoint(n))){
                return true;
        }
        return false;
}

bool pointer::isReleased(std::string n)
{
        if(c.getWindow()->getMouseReleased(getPoint(n))){
                return true;
        }
        return false;
}

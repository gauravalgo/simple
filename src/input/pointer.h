#ifndef POINTER_H
#define POINTER_H

#include <iostream>
#include <string>

#include "../utils/definitions.h"
#include "../utils/core.h"

namespace simple
{
        namespace input
        {
                class pointer
                {

                public:
                        pointer();
                        ~pointer();
                private:
                        core c;
                public:
                        bool isPressed(std::string n);
                        bool isReleased(std::string n);
                        int getPoint(std::string p);
                };
        }
}

#endif

#ifndef REGISTER_MATH_H
#define REGISTER_MATH_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "core.h"
#include "../input/keyboard.h"
#include "../input/pointer.h"

namespace simple
{
        namespace lang
        {
                class register_math
                {
                public:
                        register_math();
                        ~register_math();
                public:
                        static int registerModule(lua_State* L);
                        static int registerMetatable(lua_State* L);
                        static void setCore(core* co);
                        static core* getCore();
                private:
                        static int setOrthoView(lua_State* L);
                };
        }
}
#endif

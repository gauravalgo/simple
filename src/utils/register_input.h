#ifndef REGISTER_INPUT_H
#define REGISTER_INPUT_H

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
        using namespace simple::input;
        namespace lang
        {
                class register_input
                {
                public:
                        register_input();
                        ~register_input();
                public:
                        static void setKeyboard(keyboard* key);
                        static keyboard* getKeyboard();

                        static void setCore(core* co);
                        static core* getCore();

                        static void setPointer(pointer* pointer);
                        static pointer* getPointer();

                        static int registerModule(lua_State* L);
                        static int registerMetatable(lua_State* L);
                private:
                        static int isKeyDown(lua_State* L);
                        static int isKeyUp(lua_State* L);
                        static int getPointerX(lua_State* L);
                        static int getPointerY(lua_State* L);
                        static int getPointer(lua_State* L);
                        static int isPointerPressed(lua_State* L);
                        static int isPointerReleased(lua_State* L);
                };
        }
}
#endif

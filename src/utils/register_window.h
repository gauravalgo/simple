#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "core.h"

namespace simple
{
        namespace lang
        {
                class register_window
                {
                public:
                        register_window();
                        ~register_window();
                        static int registerModule(lua_State* L);
                        static int registerMetatable(lua_State* L);
                        static void setDefaultWindow(bool value);
                        static bool getDefaultWindow();
                        static void setCore(core* co);
                        static core* getCore();
                private:
                        static int makeWindow(lua_State* L);
                        static int getTicks(lua_State* L);
                        static int setWindowPosition(lua_State* L);
                        static int setWindowTitle(lua_State* L);
                        static int getMonitorSize(lua_State* L);
                        static int getWindowTicks(lua_State* L);
                        static int getWindowFocus(lua_State* L);
                        static int setWindowVSync(lua_State* L);
                        static int getWindowSize(lua_State* L);
                        static int getWindowWidth(lua_State* L);
                        static int getWindowHeight(lua_State* L);
                };
        }
}
#endif

#ifndef REGISTER_GRAPHICS_H
#define REGISTER_GRAPHICS_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

namespace simple
{
        namespace lang
        {
                class register_graphics
                {
                public:
                        register_graphics();
                        ~register_graphics();
                        static int registerMetatable(lua_State* L);
                        static int registerModule(lua_State* L);
                private:
                        static int clearScreen(lua_State* L);
                        static int setViewport(lua_State* L);
                        static int loadTexture(lua_State* L);
                        static int bindTexture(lua_State* L);
                        static int unBindTexture(lua_State* L);
                        static int createFont(lua_State* L);
                        static int drawFont(lua_State* L);
                        static int beginFont(lua_State* L);
                        static int endFont(lua_State* L);
                        static int createBatch(lua_State* L);
                        static int drawBatch(lua_State* L);
                        static int beginBatch(lua_State* L);
                        static int endBatch(lua_State* L);
                        static int renderMesh(lua_State* L);
                        static int createShader(lua_State* L);
                        static int createDefaultShader(lua_State* L);
                        static int bindShader(lua_State* L);
                        static int unBindShader(lua_State* L);
                        static int sendShaderUniformLocation(lua_State* L);
                };
        }
}
#endif

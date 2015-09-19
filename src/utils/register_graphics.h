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
                        int register(lua_State* L);
                private:
                        int loadTexture(lua_State* L);
                        int bindTexture(lua_State* L);
                        int unBindTexture(lua_State* L);
                        int createFont(lua_State* L);
                        int drawFont(lua_State* L);
                        int beginFont(lua_State* L);
                        int endFont(lua_State* L);
                        int createBatch(lua_State* L);
                        int drawBatch(lua_State* L);
                        int beginBatch(lua_State* L);
                        int endBatch(lua_State* L);
                        int renderMesh(lua_State* L);
                        int createShader(lua_State* L);
                        int createDefaultShader(lua_State* L);
                        int bindShader(lua_State* L);
                        int unBindShader(lua_State* L);
                        int sendShaderUniformLocation(lua_State* L);
                };
        }
}
#endif

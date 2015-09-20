/*******************************************************************************
 * Copyright 2015 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#include "register_graphics.h"
#include "lua_lang_utils.h"

core* c;

register_graphics::register_graphics()
{
        c = new core();
}

register_graphics::~register_graphics()
{
        SAFE_DELETE(c);
}

int register_graphics::loadTexture(lua_State *L)
{
        texture2D* tex = new texture2D();
        luaL_checkstring(L, 1);
        const char* path = lua_tostring(L, 1);
        isStringError(L, 1, "loadTexture -> file path");
        tex->create(path);
        pushPointer(L, tex);
        return 1;
}

int register_graphics::bindTexture(lua_State *L)
{
        texture2D* tex;
        checkInteger(L, 1);
        float id = lua_tointeger(L, 1);
        tex = getTexture2D(id);
        if(tex == getTexture2D(id))
                getTexture2D(id)->bind();

        return 1;
}

int register_graphics::unBindTexture(lua_State *L)
{
        if(checkArguments(L, 2))
                LOG("Warning: function bindTexture takes: 1) a texture");

        texture2D* tex;
        checkInteger(L, 1);
        int id = lua_tointeger(L, 1);
        tex = getTexture2D(id);
        if(tex == getTexture2D(id))
                tex->unbind();
        return 1;
}

shader* register_graphics::pushShader (lua_State *L, shader* sh)
{
        shader *pi = (shader *)lua_newuserdata(L, sizeof(shader));
        pi = sh;
        luaL_getmetatable(L, "simple.graphics");
        lua_setmetatable(L, -2);
        return pi;
}

int register_graphics::createShader(lua_State *L)
{
        shader* s = new shader();
//custom shader
        luaL_checkstring(L, 1);
        luaL_checkstring(L, 2);
        isStringError(L, 1 , "createShader -> vertex shader expected");
        isStringError(L, 2 , "createShader -> fragment shader expected");
        const char* vertex = lua_tostring(L, 1);
        const char* fragment = lua_tostring(L, 2);
        s->create(vertex, fragment);
        pushShader(L, s);
        pushPointer(L, s);
        return 1;
}

int register_graphics::createDefaultShader(lua_State* L)
{
        shader* s = new shader();

        default_shaders df;

        luaL_checkstring(L, 1);
        std::string type = luaL_checkstring(L, 1);

#ifndef EMSCRIPTEN
        if (type == "texture")
                s->create(df.gl_texture_vertex.c_str(), df.gl_texture_fragment.c_str());
        else if(type == "font")
                s->create(df.gl_font_vertex.c_str(), df.gl_font_fragment.c_str());
#endif
#ifdef EMSCRIPTEN
        if(type == "texture")
                s->create(df.gl_es_texture_vertex.c_str(), df.gl_es_texture_fragment.c_str());
        else if (type == "font")
                s->create(df.gl_es_font_vertex.c_str(), df.gl_es_font_fragment.c_str());
#endif

        pushPointer(L, s);
        return 1;
}

shader* register_graphics::checkShader (lua_State* L, int index)
{
        shader *pi, *im;
        luaL_checktype(L, index, LUA_TUSERDATA);
        pi = (shader*)luaL_checkudata(L, index, "simple.graphics");
        im = pi;
        return im;
}

int register_graphics::bindShader(lua_State *L)
{
        shader* s = checkShader(L, 1);
        s->bind();
        return 1;
}

int register_graphics::unBindShader(lua_State *L)
{
        if(checkArguments(L, 2))
                LOG("Warning: unBindShader takes: 1) shader ");

        shader* s;
        checkInteger(L, 1);
        int id = lua_tointeger(L, 1);
        s = getShader(id);
        if(s == getShader(id))
                s->unbind();
        return 1;
}

//TODO
int register_graphics::sendShaderUniformLocation(lua_State *L)
{
        if(checkArguments(L, 4))
                LOG("Warning: sendShaderUniformLocation takes: 1) shader 2) location 3) matrix");

        shader* s;
        int id = lua_tointeger(L, 1);
        const char* location = lua_tostring(L, 2);
        isStringError(L, 2, "sendShaderUniformLocation -> location string expected");
        float data = lua_tonumber(L, 3);
        s = getShader(id);
        if(s == getShader(id)){
                s->sendUniformLocation(location, data);
        }

        return 1;
}

int register_graphics::createFont(lua_State *L)
{
        font* f;
        shader* s;
        isObjectError(L, 1, "makeBatch -> shader");
        lua_Integer shID = lua_tointeger(L, 1);
        s = getShader(shID);
        luaL_checkstring(L, 2);
        const char* path = lua_tostring(L, 2);
        FT_Library freetype;
        if(FT_Init_FreeType(&freetype)){
                LOG("Error: Could not init freetype lib!");
                return 0;
        }
        float size = 16;
        if(lua_isnumber(L, 3)){
                size = lua_tonumber(L, 3);
        }

        if(s == getShader(shID)){
                f = new font();
                f->load(freetype, s, path, size);
                pushPointer(L, f);
        }
        return 1;
}

int register_graphics::drawFont(lua_State *L)
{
        font* f;
        shader* s;
        luaL_checkinteger(L, 1);
        luaL_checkinteger(L, 2);
        luaL_checkstring(L, 3);
        luaL_checknumber(L, 4);
        luaL_checknumber(L, 5);
        luaL_checknumber(L, 6);
        luaL_checknumber(L, 7);
        luaL_checknumber(L, 8);
        luaL_checknumber(L, 9);
        luaL_checknumber(L, 10);

        float a = 1;
        if(lua_isnumber(L, 11))
                a = lua_tonumber(L, 11);

        lua_Integer fID = lua_tointeger(L, 1);
        lua_Integer sID = lua_tointeger(L, 2);
        const char* text = lua_tostring(L, 3);
        float x = lua_tonumber(L, 4);
        float y = lua_tonumber(L, 5);
        float sx = lua_tonumber(L, 6);
        float sy = lua_tonumber(L, 7);
        float r = lua_tonumber(L, 8);
        float g = lua_tonumber(L, 9);
        float b = lua_tonumber(L, 10);

        f = getFont(fID);
        s = getShader(sID);

        if(f == getFont(fID) && s == getShader(sID))
                f->draw(text, s, x, y, sx, sy, r, g, b, a);
        return 1;
}

int register_graphics::beginFont(lua_State *L)
{
        font* f;
        luaL_checkinteger(L, 1);
        lua_Integer fID = lua_tointeger(L, 1);
        f = getFont(fID);
        if(f == getFont(fID))
                f->begin();
        return 1;
}

int register_graphics::endFont(lua_State *L)
{
        font* f;
        luaL_checkinteger(L, 1);
        lua_Integer fID = lua_tointeger(L, 1);
        f = getFont(fID);
        if(f == getFont(fID))
                f->end();
        return 1;
}

int register_graphics::createBatch(lua_State *L)
{
        shader* s;
        batch2d* batch;
        isObjectError(L, 1, "makeBatch -> shader");
        lua_Integer shID = lua_tointeger(L, 1);
        s = getShader(shID);
        int limit = 9000;
        if(lua_isinteger(L, 2))
                limit = lua_tointeger(L, 2);

        if(s == getShader(shID)){
                batch = new batch2d(s, limit);
                batch->create();
                pushPointer(L, batch);
        }
        return 1;
}

int register_graphics::renderMesh(lua_State *L)
{
        isObjectError(L, 1, "renderMesh -> batch");
        lua_Integer id = lua_tointeger(L, 1);
        batch2d* b;
        b = getBatch(id);
        b->renderMesh();
        return 1;
}

int register_graphics::beginBatch(lua_State *L)
{
        batch2d* batch;
        luaL_checkinteger(L, 1);
        lua_Integer id = lua_tointeger(L, 1);
        batch = getBatch(id);
        if(batch == getBatch(id))
                batch->begin();

        return 1;
}

int register_graphics::drawBatch(lua_State *L)
{
        luaL_checkinteger(L, 1);
        lua_Integer id = lua_tointeger(L, 1);
        batch2d* batch;
        batch = getBatch(id);
        if(batch == getBatch(id)){
                luaL_checknumber(L, 2);
                luaL_checknumber(L, 3);
                luaL_checknumber(L, 4);
                luaL_checknumber(L, 5);
                float x = lua_tonumber(L, 2);
                float y = lua_tonumber(L, 3);
                float w = lua_tonumber(L, 4);
                float h = lua_tonumber(L, 5);

                float rotation = 0;
                if(lua_isnumber(L, 6))
                        rotation = lua_tonumber(L, 6);
                float originX = w * 0.5f;
                if(lua_isnumber(L, 7))
                        originX = lua_tonumber(L, 7);
                float originY = h * 0.5f;
                if(lua_isnumber(L, 8))
                        originY = lua_tonumber(L, 8);
                float srcX = 0;
                if(lua_tonumber(L, 9))
                        srcX = lua_tonumber(L, 9);
                float srcY = 0;
                if(lua_tonumber(L, 10))
                        srcY = lua_tonumber(L, 10);
                float srcWidth = w;
                if(lua_tonumber(L,11))
                        srcWidth = lua_tonumber(L, 11);
                float srcHeight = h;
                if(lua_tonumber(L,12))
                        srcHeight = lua_tonumber(L, 12);
                bool flipX = false;
                if(lua_toboolean(L, 13))
                        flipX = lua_toboolean(L, 13);
                bool flipY = true;
                if(lua_toboolean(L, 14))
                        flipY = lua_toboolean(L, 14);
                float scaleX = 1;
                if(lua_tonumber(L,15))
                        scaleX = lua_tonumber(L, 15);
                float scaleY = 1;
                if(lua_tonumber(L, 16))
                        scaleY = lua_tonumber(L, 16);

                batch->draw(x, y, w, h, rotation, originX, originY, srcX, srcY, srcWidth, srcHeight, flipX, flipY, scaleX, scaleY);
        }

        return 1;
}

int register_graphics::endBatch(lua_State* L)
{
        batch2d* batch;
        luaL_checkinteger(L, 1);
        lua_Integer id = lua_tointeger(L, 1);
        batch = getBatch(id);
        if(batch == getBatch(id))
                batch->end();

        return 1;
}


int register_graphics::clearScreen(lua_State* L)
{
        checkFloat(L, 1);
        checkFloat(L, 2);
        checkFloat(L, 3);
        checkFloat(L, 4);
        float r = lua_tonumber(L, 1);
        float g = lua_tonumber(L, 2);
        float b = lua_tonumber(L, 3);
        float a = lua_tonumber(L, 4);
        float scale = 1.0f / 255.0f;
        c->getGLGraphics()->clearScreen(scale * r, scale * g, scale * b, scale * a);

        return 1;
}

int register_graphics::setViewport(lua_State *L)
{
        checkFloat(L, 1);
        checkFloat(L, 2);
        checkFloat(L, 3);
        checkFloat(L, 4);
        int x = lua_tonumber(L, 1);
        int y = lua_tonumber(L, 2);
        int w = lua_tonumber(L, 3);
        int h = lua_tonumber(L, 4);
        c->getGLGraphics()->setViewport(x, y, w, h);
        return 1;
}

int register_graphics::registerMetatable(lua_State *L)
{
        luaL_Reg meta[] = {
                {"bindTexture",   bindTexture},
                {"unBindTexture", unBindTexture},
                {"bindShader", bindShader},
                {"unBindShader", unBindShader},
                {"renderMesh", renderMesh},
                {"beginBatch", beginBatch},
                {"endBatch", endBatch},
                {"drawBatch", drawBatch},
                {"beginFont", beginFont},
                {"endFont", endFont},
                {NULL, NULL}
        };
        const luaL_Reg _meta[] = {
                {0, 0}
        };

        luaL_newmetatable(L, "simple.graphics");        /* create metatable for Image,
                                               add it to the Lua registry */
        luaL_openlibs(L);  /* fill metatable */
        lua_pushliteral(L, "__index");
        lua_pushvalue(L, -3);               /* dup methods table*/
        lua_rawset(L, -3);                  /* metatable.__index = methods */
        lua_pushliteral(L, "__metatable");
        lua_pushvalue(L, -3);               /* dup methods table*/
        lua_rawset(L, -3);                  /* hide metatable:
                                               metatable.__metatable = methods */
        lua_pop(L, 1);                      /* drop metatable */
        return 1;                           /* return methods on the stack */
}


int register_graphics::registerModule(lua_State* L)
{
        luaL_Reg regGraphicsFuncs[] = {
                {"newImage", loadTexture},
                {"newShader", createShader},
                {"newDefaultShader", createDefaultShader},
                {"newBatch", createBatch},
                {"clearScreen", clearScreen},
                {"setViewport", setViewport},
                {"drawFont", drawFont},
                {"newFont", createFont},
                {NULL, NULL}
        };

        luaL_newlib(L, regGraphicsFuncs);
        return 1;
}

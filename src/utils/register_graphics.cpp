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

font* register_graphics::checkFont(lua_State* L, int n)
{
        return *(font **)luaL_checkudata(L, n, "luaL_font");
}

shader* register_graphics::checkShader(lua_State* L, int n)
{
        return *(shader **)luaL_checkudata(L, n, "luaL_shader");
}

texture2D* register_graphics::checkTexture(lua_State *L, int n)
{
        return *(texture2D **)luaL_checkudata(L, n, "luaL_texture");
}

batch2d* register_graphics::checkBatch(lua_State *L, int n)
{
        return *(batch2d **)luaL_checkudata(L, n, "luaL_batch");
}

mesh* register_graphics::checkMesh(lua_State* L, int n)
{
	return *(mesh **)luaL_checkudata(L, n, "luaL_mesh");
}

int register_graphics::deleteMesh(lua_State *L)
{
        mesh* f = checkMesh(L, 1);
        if (f != NULL){
                SAFE_DELETE(f);
        }else{
                LOG("can not delete mesh because it is null!");
                return 0;
        }
        return 1;
}


int register_graphics::deleteFont(lua_State *L)
{
        font* f = checkFont(L, 1);
        if (f != NULL){
                SAFE_DELETE(f);
        }else{
                LOG("can not delete font because it is null!");
                return 0;
        }
        return 1;
}

//Delete
int register_graphics::deleteShader(lua_State *L)
{
        shader* f = checkShader(L, 1);
        if (f != NULL){
                SAFE_DELETE(f);
        }else{
                LOG("can not delete shader because it is null!");
                return 0;
        }
        return 1;
}

int register_graphics::deleteTexture(lua_State *L)
{
        texture2D* f = checkTexture(L, 1);
        if (f != NULL){
                SAFE_DELETE(f);
        }else{
                LOG("can not delete texture because it is null!");
                return 0;
        }
        return 1;
}

int register_graphics::deleteBatch(lua_State *L)
{
        batch2d* f = checkBatch(L, 1);
        if (f != NULL){
                SAFE_DELETE(f);
        }else{
                LOG("can not delete batch because it is null!");
                return 0;
        }
        return 1;
}

//Init

int register_graphics::initMesh(lua_State *L)
{
        mesh ** f = (mesh **) lua_newuserdata(L, sizeof(mesh *));
        *f = new mesh();

        luaL_getmetatable(L, MESH_NAME);
        lua_setmetatable(L, -2);
        return 1;
}

int register_graphics::createMesh(lua_State* L)
{
	mesh* m = checkMesh(L, 1);
	shader* s = checkShader(L, 2);
	//m->create(s, vertices, indices);
	return 1;
}

int register_graphics::drawMesh(lua_State* L)
{
	mesh* m = checkMesh(L, 1);
	int count = luaL_checknumber(L, 2);
	m->draw(count);
}

int register_graphics::initTexture(lua_State *L)
{
        texture2D ** f = (texture2D **) lua_newuserdata(L, sizeof(texture2D *));
        *f = new texture2D();

        luaL_getmetatable(L, TEXTURE_NAME);
        lua_setmetatable(L, -2);
        return 1;
}

int register_graphics::loadTexture(lua_State *L)
{
        texture2D* tex = checkTexture(L, 1);
        luaL_checkstring(L, 2);
        const char* path = lua_tostring(L, 2);

        tex->create(path);
        return 1;
}

int register_graphics::bindTexture(lua_State *L)
{
        texture2D* tex = checkTexture(L, 1);
        tex->bind();
        return 1;
}

int register_graphics::unBindTexture(lua_State *L)
{
        texture2D* tex = checkTexture(L, 1);
        tex->unbind();
        return 1;
}

int register_graphics::initShader(lua_State *L)
{
        shader ** f = (shader **) lua_newuserdata(L, sizeof(shader *));
        *f = new shader();

        luaL_getmetatable(L, SHADER_NAME);
        lua_setmetatable(L, -2);
        return 1;
}

int register_graphics::createShader(lua_State *L)
{
        shader* s = checkShader(L, 1);
        string type;
        if(lua_isstring(L, 2))
                type = lua_tostring(L, 2);

        if(lua_isstring(L, 2) && (type == "default"))
                createDefaultShader(L);
        else if(lua_isstring(L,2) && lua_isstring(L,3)){
                //custom shader
                luaL_checkstring(L, 2);
                luaL_checkstring(L, 3);
                const char* vertex = lua_tostring(L, 2);
                const char* fragment = lua_tostring(L, 3);
                s->create(vertex, fragment);
        }
        return 1;
}

int register_graphics::createDefaultShader(lua_State* L)
{
        shader* s = checkShader(L, 1);

        default_shaders df;

        std::string type = luaL_checkstring(L, 2);

#ifndef EMSCRIPTEN
        if (type == "default")
                s->create(df.gl_default_vertex.c_str(), df.gl_default_fragment.c_str());
#endif
#ifdef EMSCRIPTEN
        if(type == "default")
                s->create(df.gl_es_texture_vertex.c_str(), df.gl_es_texture_fragment.c_str());
#endif
        return 1;
}

int register_graphics::bindShader(lua_State *L)
{
        shader* s = checkShader(L, 1);
        s->bind();
        return 1;
}

int register_graphics::unBindShader(lua_State *L)
{
        shader* s = checkShader(L, 1);
        s->unbind();
        return 1;
}

//TODO
int register_graphics::sendShaderUniformLocation(lua_State *L)
{
        shader* s = checkShader(L, 1);
        const char* location = lua_tostring(L, 2);
        float data = lua_tonumber(L, 3);
        s->sendUniformLocation(location, data);
        return 1;
}

int register_graphics::initFont(lua_State* L)
{
        font** f = (font **) lua_newuserdata(L, sizeof(font *));
        *f = new font();

        luaL_getmetatable(L, FONT_NAME);
        lua_setmetatable(L, -2);
        return 1;
}

int register_graphics::createFont(lua_State *L)
{
        font* f = checkFont(L, 1);
        shader* s = checkShader(L, 2);

        luaL_checkstring(L, 3);
        const char* path = lua_tostring(L, 3);
        FT_Library freetype;
        if(FT_Init_FreeType(&freetype)){
                LOG("Error: Could not init freetype lib!");
                return 0;
        }
        float size = 16;
        if(lua_isnumber(L, 4))
                size = lua_tonumber(L, 4);

        f->load(freetype, s, path, size);
        return 1;
}

int register_graphics::drawFont(lua_State *L)
{
        font* f = checkFont(L, 1);
        shader* s = checkShader(L, 2);
        if(!s->getLinked() && s != NULL)
                LOG("WARNING: shader:bind must be called before drawFont!");
        
        const char* message = "";
        if(lua_isstring(L, 3))
                message = lua_tostring(L, 3);
        float x; float y;
        if(lua_isnumber(L,4))
            x = lua_tonumber(L, 4);
        if(lua_isnumber(L,5))
            y = lua_tonumber(L, 5);
        float sx = 1; float sy = 1;
        if(lua_isnumber(L,6))
            sx = lua_tonumber(L, 6);
        if(lua_isnumber(L,7))
            sy = lua_tonumber(L, 7);
        float r = 255; float g = 255; float b = 255;
         if(lua_isnumber(L, 8))
            r = lua_tonumber(L, 8);
        if(lua_isnumber(L, 9))
            g = lua_tonumber(L, 9);
         if(lua_isnumber(L, 10))
            b = lua_tonumber(L, 10);
        float a = 255;
        if(lua_isnumber(L, 11))
            a = lua_tonumber(L, 11);

        f->draw(message, s, x, y, sx, sy, r, g, b, a);
        return 1;
}

int register_graphics::beginFont(lua_State *L)
{
        font* f = checkFont(L, 1);
        f->begin();
        return 1;
}

int register_graphics::endFont(lua_State *L)
{
        font* f = checkFont(L, 1);
        f->end();
        return 1;
}

int register_graphics::initBatch(lua_State *L)
{
        batch2d ** f = (batch2d **) lua_newuserdata(L, sizeof(batch2d *));
        *f = new batch2d();

        luaL_getmetatable(L, BATCH_NAME);
        lua_setmetatable(L, -2);
        return 1;
}

int register_graphics::createBatch(lua_State *L)
{
        batch2d* batch = checkBatch(L, 1);
        shader* s = checkShader(L, 2);
        int limit = 9000;
        if(lua_isinteger(L, 3))
                limit = lua_tointeger(L, 3);

        batch->create(s, limit);
        return 1;
}

int register_graphics::renderMesh(lua_State *L)
{
        batch2d* b = checkBatch(L, 1);
        b->renderMesh();
        return 1;
}

int register_graphics::beginBatch(lua_State *L)
{
        batch2d* batch = checkBatch(L, 1);
        batch->begin();
        return 1;
}

int register_graphics::drawBatch(lua_State *L)
{
        batch2d* batch = checkBatch(L, 1);
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
        return 1;
}

int register_graphics::endBatch(lua_State* L)
{
        batch2d* batch = checkBatch(L, 1);
        batch->end();

        return 1;
}

int register_graphics::initGraphics(lua_State *L)
{
        register_graphics ** f = (register_graphics **) lua_newuserdata(L, sizeof(register_graphics *));
        *f = new register_graphics();

        luaL_getmetatable(L, "luaL_graphics");
        lua_setmetatable(L, -2);
        return 1;
}

int register_graphics::setBackgroundColor(lua_State* L)
{
        luaL_checknumber(L, 2);
        luaL_checknumber(L, 3);
        luaL_checknumber(L, 4);
        luaL_checknumber(L, 5);
        float r = lua_tonumber(L, 2);
        float g = lua_tonumber(L, 3);
        float b = lua_tonumber(L, 4);
        float a = lua_tonumber(L, 5);
        float scale = 1.0f / 255.0f;
        c->getGLGraphics()->setBackgroundColor(scale * r, scale * g, scale * b, scale * a);

        return 1;
}

int register_graphics::clear_(lua_State* L)
{
  c->getGLGraphics()->clear_();
  return 1;
}

int register_graphics::setViewport(lua_State *L)
{
        luaL_checknumber(L, 2);
        luaL_checknumber(L, 3);
        luaL_checknumber(L, 4);
        luaL_checknumber(L, 5);
        int x = lua_tonumber(L, 2);
        int y = lua_tonumber(L, 3);
        int w = lua_tonumber(L, 4);
        int h = lua_tonumber(L, 5);
        c->getGLGraphics()->setViewport(x, y, w, h);
        return 1;
}

int register_graphics::registerMesh(lua_State *L)
{
        luaL_Reg reg[] = {
                {"new", initMesh },
                {"init", createMesh},
                {"draw", drawMesh},
                {"gc", deleteMesh },
                {NULL, NULL}
        };
        luaL_newmetatable(L, MESH_NAME);
        luaL_setfuncs(L, reg, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Mesh");
        return 1;
}

int register_graphics::registerShader(lua_State *L)
{
        luaL_Reg regShader[] = {
                {"new", initShader },
                {"init", createShader},
                {"bind", bindShader},
                {"unbind", unBindShader},
                {"gc", deleteShader },
                {NULL, NULL }
        };
        luaL_newmetatable(L, SHADER_NAME);
        luaL_setfuncs(L, regShader, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Shader");
        return 1;
}

int register_graphics::registerBatch(lua_State *L)
{
        luaL_Reg reg[] = {
                {"new", initBatch },
                {"init", createBatch },
                {"draw", drawBatch },
                {"bind", beginBatch },
                {"unbind", endBatch },
                {"renderMesh", renderMesh },
                {"gc", deleteBatch },
                {NULL, NULL }
        };
        luaL_newmetatable(L, BATCH_NAME);
        luaL_setfuncs(L, reg, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Batch");
        return 1;
}

int register_graphics::registerGraphics(lua_State *L)
{
        luaL_Reg reg[] = {
                {"new", initGraphics },
                {"clear", clear_ },
                {"setBackgroundColor", setBackgroundColor },
                {"viewPort", setViewport},
                {NULL, NULL}
        };
        luaL_newmetatable(L, "luaL_graphics");
        luaL_setfuncs(L, reg, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Graphics");
        return 1;
}

int register_graphics::registerTexture(lua_State *L)
{
        luaL_Reg reg[] = {
                {"new", initTexture },
                {"init", loadTexture},
                {"bind", bindTexture},
                {"unbind", unBindTexture },
                {"gc", deleteTexture },
                {NULL, NULL}
        };
        luaL_newmetatable(L, TEXTURE_NAME);
        luaL_setfuncs(L, reg, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Texture");
        return 1;
}

int register_graphics::registerFont(lua_State* L)
{
        luaL_Reg regGraphicsFuncs[] = {
                 {"new", initFont },
                 {"init", createFont },
                 {"draw", drawFont},
                 {"bind", beginFont },
                 {"unbind", endFont },
                 {"gc", deleteFont },
                {NULL, NULL}
        };

        luaL_newmetatable(L, FONT_NAME);
        luaL_setfuncs(L, regGraphicsFuncs, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Font");

        return 1;
}

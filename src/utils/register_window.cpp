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
#include "register_window.h"
#include "lua_lang_utils.h"

using namespace simple;
using namespace simple::lang;

static bool default_window;

static core* c;

register_window::register_window()
{}
register_window::~register_window()
{}

void register_window::setCore(core* co){c = co;}
core* register_window::getCore(){return c; }

void register_window::setDefaultWindow(bool value)
{
        default_window = value;
}

bool register_window::getDefaultWindow()
{
        return default_window;
}

int register_window::initWindow(lua_State* L)
{
        register_window ** f = (register_window **) lua_newuserdata(L, sizeof(register_window *));
        *f = new register_window();

        luaL_getmetatable(L, "luaL_window");
        lua_setmetatable(L, -2);
        return 1;
}

register_window* register_window::checkWindow(lua_State *L, int n)
{
        return *(register_window**)luaL_checkudata(L, n, "luaL_window");
}

int register_window::deleteWindow(lua_State *L)
{
        register_window* window = checkWindow(L, 1);
        if(window != NULL){
                SAFE_DELETE(window);
        }else{
                LOG("Could not delete window because it is null");
                return 0;
        }
        return 1;
}

int register_window::makeWindow(lua_State* L)
{
        setDefaultWindow(false);
        luaL_checkstring(L, 2);
        const char* title = lua_tostring(L, 2);
        luaL_checknumber(L, 3);
        luaL_checknumber(L, 4);
        int width = lua_tonumber(L,3);
        int height = lua_tonumber(L, 4);
        bool fullscreen = false;
        bool resizable = false;
        int x = -1;
        int y = -1;
        //Optional
        if(lua_isnumber(L, 5))
                fullscreen = lua_tonumber(L, 5);
        if(lua_isnumber(L, 6))
                resizable = lua_tonumber(L, 6);

        if(lua_isnumber(L, 7) && lua_isnumber(L, 8)){
                x = lua_tonumber(L, 7);
                y = lua_tonumber(L, 8);
        }
        getCore()->getWindow()->create(title, width, height, fullscreen, resizable);
        getCore()->getWindow()->setPosition(x, y);
        return 1;
}

int register_window::getWindowSize(lua_State *L)
{
        float w = getCore()->getWindow()->getWidth();
        float h = getCore()->getWindow()->getHeight();

        lua_pushnumber(L, h);
        lua_pushnumber(L, w);

        return 2;
}

int register_window::getWindowWidth(lua_State *L)
{
        float w = getCore()->getWindow()->getWidth();
        lua_pushnumber(L, w);
        return 1;
}

int register_window::getWindowHeight(lua_State *L)
{
        float h = getCore()->getWindow()->getHeight();
        lua_pushnumber(L, h);
        return 1;
}

int register_window::setWindowVSync(lua_State *L)
{
        bool v = lua_toboolean(L, 2);
        getCore()->getWindow()->setVSync(v);
        return 1;
}

int register_window::setWindowPosition(lua_State* L)
{
        luaL_checknumber(L , 2);
        luaL_checknumber(L , 3);
        int x = lua_tonumber(L, 2);
        int y = lua_tonumber(L, 3);
        getCore()->getWindow()->setPosition(x, y);
        return 1;
}

int register_window::setWindowTitle(lua_State* L)
{
        luaL_checkstring(L, 2);
        const char* title = lua_tostring(L, 2);
        getCore()->getWindow()->setTitle(title);
        return 1;
}

int register_window::getWindowFocus(lua_State* L)
{
        bool focused = getCore()->getWindow()->isFocused();
        lua_pushboolean(L, focused);
        return 1;
}

int register_window::getWindowTicks(lua_State* L)
{
        lua_pushnumber(L, getCore()->getWindow()->getTicks());
        return 1;
}

int register_window::getMonitorSize(lua_State* L)
{
        lua_newtable(L);

        float x = getCore()->getWindow()->getMonitorSize().x;
        float y = getCore()->getWindow()->getMonitorSize().y;

        lua_pushnumber(L, y);
        lua_pushnumber(L, x);
        lua_settable(L, -3);
        return 1;
}

int register_window::getTicks(lua_State *L)
{
        lua_pushnumber(L, getCore()->getWindow()->getTicks());
        return 1;
}

int register_window::registerModule(lua_State *L)
{
        luaL_Reg reg[] = {
                {"new", initWindow },
                {"init", makeWindow },
                {"setPosition", setWindowPosition },
                {"setTitle", setWindowTitle },
                {"getMonitorSize", getMonitorSize },
                {"getSize", getWindowSize },
                {"getWidth", getWindowWidth },
                {"getHeight", getWindowHeight },
                {"getFocus", getWindowFocus },
                {"setVSync", setWindowVSync },
                {"getTicks", getTicks },
                {"gc", deleteWindow },
                {NULL, NULL}
        };
        luaL_newmetatable(L, "luaL_window");
        luaL_setfuncs(L, reg, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Window");
        return 1;
}

#include "register_window.h"
#include "lua_lang_utils.h"

using namespace simple;
using namespace simple::lang;

static bool default_window;

static core* co_;

register_window::register_window()
{}
register_window::~register_window()
{}

void register_window::setCore(core* co){co_ = co;}
core* register_window::getCore(){return co_; }

void register_window::setDefaultWindow(bool value)
{
        default_window = value;
}

bool register_window::getDefaultWindow()
{
        return default_window;
}

int register_window::makeWindow(lua_State* L)
{
        setDefaultWindow(false);
        luaL_checkstring(L, 1);
        const char* title = lua_tostring(L, 1);
        checkFloat(L, 2);
        checkFloat(L, 3);
        int width = lua_tonumber(L,2);
        int height = lua_tonumber(L, 3);
        bool fullscreen = false;
        bool resizable = false;
        int x = -1;
        int y = -1;
        //Optional
        if(lua_isnumber(L, 4))
                fullscreen = lua_tonumber(L, 4);
        if(lua_isnumber(L, 5))
                resizable = lua_tonumber(L, 5);

        if(lua_isnumber(L, 5) && lua_isnumber(L, 6)){
                x = lua_tonumber(L, 5);
                y = lua_tonumber(L, 6);
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
        if(checkArguments(L, 2))
                LOG("Warning: function makeWindow takes: 1)boolean");

        bool v = lua_toboolean(L, 1);
        getCore()->getWindow()->setVSync(v);
        return 1;
}

int register_window::setWindowPosition(lua_State* L)
{
        checkFloat(L , 1);
        checkFloat(L , 2);
        int x = lua_tonumber(L, 1);
        int y = lua_tonumber(L, 2);
        getCore()->getWindow()->setPosition(x, y);
        return 1;
}

int register_window::setWindowTitle(lua_State* L)
{
        luaL_checkstring(L, 1);
        const char* title = lua_tostring(L, 1);
        getCore()->getWindow()->setTitle(title);
        return 1;
}

int register_window::getWindowFocus(lua_State* L)
{
        if(checkArguments(L, 1))
                LOG("Warning: function getWindowFocus takes no parameter");
        bool focused = getCore()->getWindow()->isFocused();
        lua_pushboolean(L, focused);
        return 1;
}

int register_window::getWindowTicks(lua_State* L)
{
        if(checkArguments(L, 1))
                LOG("Warning: function getTicks takes no parameter");

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

int register_window::registerModule(lua_State *L)
{
        luaL_Reg reg[] = {
                {"create", makeWindow},
                {"setPosition", setWindowPosition},
                {"setTitle", setWindowTitle},
                {"getMonitorSize", getMonitorSize},
                {"getSize", getWindowSize },
                {"getWidth", getWindowWidth },
                {"getHeight", getWindowHeight },
                {"getFocus", getWindowFocus},
                {"setVSync", setWindowVSync},
                {0, 0},
        };
        luaL_newlib(L, reg);
        return 1;
}

int register_window::registerMetatable(lua_State *L)
{
        return 1;
}

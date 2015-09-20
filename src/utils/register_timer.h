#ifndef REGISTER_TIMER_H
#define REGISTER_TIMER_H

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
    class register_timer
    {
    public:
      register_timer();
      ~register_timer();
      static int registerModule(lua_State* L);
      static void setCore(core* co);
      static core* getCore();
    private:
      static int getDeltaTime(lua_State* L);
      static int getFPS(lua_State* L);
    };
  }
}
#endif

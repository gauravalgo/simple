#ifndef REGISTER_AUDIO_H
#define REGISTER_AUDIO_H

extern "C" {
#include "../../deps/lua/lua.h"
#include "../../deps/lua/lualib.h"
#include "../../deps/lua/lauxlib.h"
}

#include "core.h"
#include "../sound/ogg_player.h"

namespace simple
{
  namespace lang
  {
    class register_audio
    {
    public:
      register_audio();
      ~register_audio();
      static int registerModule(lua_State* L);
      static void setCore(core* co);
      static core* getCore();
    private:
      static ogg_player* checkOGG(lua_State* L, int n);
      static int initAudio(lua_State* L);
      static int loadSound(lua_State* L);
      static int playSound(lua_State* L);
    };
  }
}
#endif

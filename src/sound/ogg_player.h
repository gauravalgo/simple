#ifndef OGG_PLAYER_H
#define OGG_PLAYER_H

#include "../utils/definitions.h"
#include "openal_context.h"
#include "../utils/core.h"

namespace simple
{
        namespace sound
        {

                class ogg_player
                {
                public:
                        ogg_player();
                        ~ogg_player();
                public:
                        void create(const char* filename);
                        void play(float volume, float pitch);
                        void stop();
                        void pause();
                        void setLooping(bool value);
                private:
                        core* c;
                        uint buffer;
                        uint sID;
                };

        }
}
#endif

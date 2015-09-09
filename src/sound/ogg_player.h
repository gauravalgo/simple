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

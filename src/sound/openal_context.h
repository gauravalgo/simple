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
#ifndef OPENAL_CONTEXT_H
#define OPENAL_CONTEXT_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "../utils/definitions.h"

namespace simple
{
        namespace sound
        {
                class openal_context
                {
                private:
                        ALCdevice* m_device;
                        ALCcontext* m_context;
                public:
                        openal_context();
                        ~openal_context();
                        void create();

                        typedef enum {
                                audio_state_playing,
                                audio_state_stopped,
                                audio_state_paused
                        } audio_state;

                        audio_state state;

                        void makeBuffer(uint* id);
                        void deleteBuffer(uint* id);
                        float getDuration(uint id);
                        void makeSource(uint* sourceID, ALuint id);
                        void setSourceID(uint sourceID, ALuint id);
                        void deleteSourceID(uint* sourceID);
                        void setPitch(uint sourceID, float pitch);
                        void setVolume(uint sourceID, float volume);
                        void setLooping(uint sourceID, bool value);
                        void playSource(uint sourceID);
                        void pauseSource(uint sourceID);
                        void stopSource(uint sourceID);
                        void sendBuffer(uint id, ALenum format, void* data, ALsizei size, ALsizei freq);

                };
        }
}
#endif

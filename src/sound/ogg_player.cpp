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
#include "ogg_player.h"

using namespace simple;
using namespace simple::sound;

#include "../../deps/stb_vorbis/stb_vorbis.h"
#include "../utils/definitions.h"

ogg_player::ogg_player()
{}

ogg_player::~ogg_player()
{
        SAFE_DELETE(c);
}

void ogg_player::create(const char* filename)
{
        c = new core();
        c->create();
        short *data;
        int channels,samplingrate;

        int len = stb_vorbis_decode_filename(filename, &channels, &samplingrate, &data);
        if(len == -1)
                LOG("OGG_Player: Could not load file " << filename);
        c->getOpenAL()->makeBuffer(&buffer);
        c->getOpenAL()->sendBuffer(buffer, channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
                                   data, len * sizeof(short) * channels, samplingrate);
        c->getOpenAL()->makeSource(&sID, buffer);
        c->getOpenAL()->setSourceID(sID, buffer);
}

void ogg_player::pause()
{
        c->getOpenAL()->pauseSource(sID);
}

void ogg_player::stop()
{
        c->getOpenAL()->stopSource(sID);
}

void ogg_player::setLooping(bool value)
{
        if(value)
                c->getOpenAL()->setLooping(sID, true);
        else
                c->getOpenAL()->setLooping(sID, false);
}

void ogg_player::play(float volume, float pitch)
{
        if(volume != 1.0f)
                c->getOpenAL()->setVolume(sID, volume);
        if(pitch != 1.0f)
                c->getOpenAL()->setPitch(sID, pitch);

        c->getOpenAL()->playSource(sID);
}

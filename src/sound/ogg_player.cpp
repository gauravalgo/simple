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

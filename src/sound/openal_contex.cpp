#include "openal_context.h"

using namespace simple;
using namespace simple::sound;

#include "../utils/definitions.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

openal_context::openal_context()
{}

openal_context::~openal_context()
{}

void openal_context::create()
{
        m_device = alcOpenDevice(0);
        m_context = alcCreateContext(m_device, 0);
        if(!alcMakeContextCurrent(m_context)) {
                LOG("Failed to initialite audio context\n");
        }

}

void openal_context::audio_SourceCommon_init(audio_SourceCommon *source) {
  alGenSources(1, &source->source);

  alSourcef(source->source, AL_PITCH, 1);
  alSourcef(source->source, AL_GAIN, 1);
  alSource3f(source->source, AL_POSITION, 0, 0, 0);
  alSource3f(source->source, AL_VELOCITY, 0, 0, 0);
  alSourcei(source->source, AL_LOOPING, AL_FALSE);

  source->state = audio_SourceState_stopped;
}


void openal_context::audio_SourceCommon_play(audio_SourceCommon *source) {
  alSourcePlay(source->source);
  source->state = audio_SourceState_playing;
}


void openal_context::audio_SourceCommon_stop(audio_SourceCommon *source) {
  alSourceStop(source->source);
  source->state = audio_SourceState_stopped;
}

ALint audio_SourceCommon_getState(openal_context::audio_SourceCommon const *source) {
  ALint state;
  alGetSourcei(source->source, AL_SOURCE_STATE, &state);
  return state;
}


void openal_context::audio_SourceCommon_pause(audio_SourceCommon *source) {
  if(source->state == audio_SourceState_playing) {
    alSourcePause(source->source);
    source->state = audio_SourceState_paused;
  }
}


void audio_SourceCommon_resume(openal_context::audio_SourceCommon *source) {
        if(source->state == openal_context::audio_SourceState_paused) {
    alSourcePlay(source->source);
    source->state = openal_context::audio_SourceState_playing;
  }
}


bool audio_SourceCommon_isPlaying(openal_context::audio_SourceCommon const* source) {
        return source->state == openal_context::audio_SourceState_playing;
}


bool audio_SourceCommon_isStopped(openal_context::audio_SourceCommon const* source) {
        return source->state == openal_context::audio_SourceState_stopped;
}


bool audio_SourceCommon_isPaused(openal_context::audio_SourceCommon const* source) {
        return source->state == openal_context::audio_SourceState_paused;
}

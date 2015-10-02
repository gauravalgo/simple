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
#include "openal_context.h"

using namespace simple;
using namespace simple::sound;

#include "../utils/definitions.h"

#include <AL/al.h>
#include <AL/alc.h>

openal_context::openal_context()
{}

openal_context::~openal_context()
{
  alcMakeContextCurrent(NULL);
}

ALuint buffer;
void openal_context::create()
{
  m_device = alcOpenDevice(NULL);
  if (m_device == NULL)
    LOG("Failed to init OpenAL device.");
  m_context = alcCreateContext(m_device, NULL);
  if(!m_context)
    LOG("OpenAL : Unable to create context!");
  if(!alcMakeContextCurrent(m_context))
    LOG("Failed to initialite audio context\n");

  ALenum error = alGetError();
  if(error != AL_NO_ERROR){
    LOG("OpenAL : " << error << " error!");
    return;
  }
  LOG("OpenAL inited");
}

//piata caius iacob nr 9 - 11 bloul T scara A ap 16


void openal_context::makeBuffer(uint* id)
{
  alGenBuffers(1, id);
}

void openal_context::deleteBuffer(uint* id)
{
  alDeleteBuffers(1, id);
}

void openal_context::sendBuffer(uint id, ALenum format, void* data, ALsizei size, ALsizei freq)
{
  alBufferData(id, format, data, size, freq);
  ALenum error = alGetError();
  if(error != AL_NO_ERROR){
    LOG("OpenAL Error: " << error << ", unable to send sound data!");
    return;
  }
}

float openal_context::getDuration(uint id)
{
  int size,bits,freq;
  alGetBufferi(id, AL_SIZE, &size);
  alGetBufferi(id, AL_BITS, &bits);
  alGetBufferi(id, AL_FREQUENCY, &freq);

  float duration = size / (float)((bits/8.0f) * freq);
  return duration;
}

void openal_context::makeSource(uint* sourceID, ALuint id)
{
  alGenSources(1, sourceID);
  setSourceID(*sourceID, id);

  ALfloat sourceVel[] = {0.0, 0.0, 0.0};
  alSourcefv(*sourceID, AL_VELOCITY, sourceVel);
  ALenum error = alGetError();;
  if(error != AL_NO_ERROR){
    LOG("OpenAL : Unable to make source!");
    return;
  }
}

void openal_context::deleteSourceID(uint* sourceID)
{
  alDeleteSources(1, sourceID);
}

void openal_context::setSourceID(uint sourceID, ALuint id)
{
  alSourcei(sourceID, AL_BUFFER, id);
  ALenum error = alGetError();;
  if(error != AL_NO_ERROR){
    LOG("OpenAL : Unable to set source!");
    return;
  }
}

void openal_context::setLooping(uint sourceID, bool value)
{
  if(value)
    alSourcei(sourceID, AL_LOOPING, 1);
  else
    alSourcei(sourceID, AL_LOOPING, 0);
}

void openal_context::setVolume(uint sourceID, float volume)
{
  alSourcef(sourceID, AL_GAIN, volume);
}

void openal_context::setPitch(uint sourceID, float pitch)
{
  alSourcef(sourceID, AL_PITCH, pitch);
}

void openal_context::playSource(uint sourceID)
{
  alSourcePlay(sourceID);
  state = audio_state_playing;
}

void openal_context::pauseSource(uint sourceID)
{
  alSourcePause(sourceID);
  state = audio_state_stopped;
}

void openal_context::stopSource(uint sourceID)
{
  alSourceStop(sourceID);
  state = audio_state_stopped;
}

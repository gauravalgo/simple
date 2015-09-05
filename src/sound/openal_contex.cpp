#include "openal_context.h"

using namespace simple;
using namespace simple::sound;

#include "../utils/definitions.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

openal_context::openal_context()
{

}

openal_context::~openal_context()
{
        ALCcontext * context = alcGetCurrentContext();
        ALCdevice * device = alcGetContextsDevice(context);

        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);
}

void openal_context::create()
{

        m_device = alcOpenDevice(NULL);
        if(m_device == NULL)
                LOG("OpenAL: Could not create device");
        m_context = alcCreateContext(m_device, NULL);
        if(m_context == NULL)
                LOG("OpenAL: Could not create context");

}

ALboolean loop;
bool openal_context::test()
{
        return true;
}

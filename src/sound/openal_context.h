#ifndef OPENAL_CONTEXT_H
#define OPENAL_CONTEXT_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

namespace simple
{
        namespace sound
        {
                class openal_context
                {
                public:
                        openal_context();
                        ~openal_context();
                public:
                        void create();
                        bool test();
                private:
                        ALCdevice* m_device;
                        ALCcontext* m_context;
                };
        }
}
#endif

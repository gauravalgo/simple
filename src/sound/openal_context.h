#ifndef OPENAL_CONTEXT_H
#define OPENAL_CONTEXT_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "../utils/definitions.h"
//http://www.pasteall.org/60992
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
                                audio_SourceState_playing,
                                audio_SourceState_stopped,
                                audio_SourceState_paused
                        } audio_SourceState;

                        typedef struct {
                                ALuint source;
                                audio_SourceState state;
                        } audio_SourceCommon;


                        void audio_SourceCommon_init(audio_SourceCommon *source);
                        void audio_SourceCommon_play(audio_SourceCommon *source);
                        void audio_SourceCommon_stop(audio_SourceCommon *source);
                        void audio_SourceCommon_pause(audio_SourceCommon *source);
                        void audio_SourceCommon_resume(audio_SourceCommon *source);
                        ALint audio_SourceCommon_getState(audio_SourceCommon const *source);
                        bool audio_SourceCommon_isPlaying(audio_SourceCommon const* source);
                        bool audio_SourceCommon_isStopped(audio_SourceCommon const* source);
                        bool audio_SourceCommon_isPaused(audio_SourceCommon const* source);

                };
        }
}
#endif

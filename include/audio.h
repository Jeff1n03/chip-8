#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_audio.h>
#include <stddef.h>

typedef struct {
        SDL_AudioDeviceID dev;
        Sint16 *buf;
        size_t bufSize;
} Audio;

Audio *createAudio(unsigned int freq, Sint16 amp);

void destroyAudio(Audio *a);

#endif

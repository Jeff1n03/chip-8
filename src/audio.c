#include "../include/audio.h"
#include <stdlib.h>

Audio *createAudio(unsigned int freq, Sint16 amp) {
    Audio *a = malloc(sizeof(Audio));
    SDL_AudioSpec des = {
        .freq = 44100, .format = AUDIO_S16SYS, .channels = 1, .samples = 1024};
    a->dev = SDL_OpenAudioDevice(NULL, 0, &des, NULL, 0);
    size_t samples = des.freq / 60;
    a->bufSize = samples * sizeof(Sint16);
    a->buf = malloc(a->bufSize);
    for (int p = des.freq / freq / 2, i = 0; i < samples; i++) {
        if ((i / p) % 2 == 0) {
            a->buf[i] = amp;
        } else {
            a->buf[i] = -amp;
        }
    }
    return a;
}

void destroyAudio(Audio *a) {
    if (a != NULL) {
        if (a->buf != NULL) {
            free(a->buf);
        }
        free(a);
    }
}

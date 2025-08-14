#ifndef VIDEO_H
#define VIDEO_H

#include <SDL2/SDL_render.h>
#include <stdint.h>

#define Y 32
#define X 64

void video(uint8_t disp[Y][X], SDL_Renderer *rend);

#endif

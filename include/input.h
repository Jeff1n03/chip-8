#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL_keyboard.h>

void keyUp(uint8_t input[16], SDL_Scancode key);

void keyDown(uint8_t input[16], SDL_Scancode key);

#endif

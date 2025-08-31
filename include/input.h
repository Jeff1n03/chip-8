#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL_keyboard.h>

#define INPUT_SIZE 16

void keyUp(uint8_t input[INPUT_SIZE], SDL_Scancode key);

void keyDown(uint8_t input[INPUT_SIZE], SDL_Scancode key);

#endif

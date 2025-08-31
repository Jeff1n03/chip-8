#include "../include/input.h"

static const SDL_Scancode map[INPUT_SIZE] = {
    SDL_SCANCODE_COMMA, SDL_SCANCODE_7, SDL_SCANCODE_8,
    SDL_SCANCODE_9,     SDL_SCANCODE_U, SDL_SCANCODE_I,
    SDL_SCANCODE_O,     SDL_SCANCODE_J, SDL_SCANCODE_K,
    SDL_SCANCODE_L,     SDL_SCANCODE_M, SDL_SCANCODE_PERIOD,
    SDL_SCANCODE_0,     SDL_SCANCODE_P, SDL_SCANCODE_SEMICOLON,
    SDL_SCANCODE_SLASH};

void keyUp(uint8_t input[INPUT_SIZE], SDL_Scancode key) {
    for (int i = 0; i < INPUT_SIZE; i++) {
        if (key == map[i]) {
            input[i] = 0;
            break;
        }
    }
}

void keyDown(uint8_t input[INPUT_SIZE], SDL_Scancode key) {
    for (int i = 0; i < INPUT_SIZE; i++) {
        if (key == map[i]) {
            input[i] = 1;
            break;
        }
    }
}

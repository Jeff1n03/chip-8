#include "../include/input.h"

static const SDL_Scancode map[] = {
    SDL_SCANCODE_COMMA, SDL_SCANCODE_7, SDL_SCANCODE_8,
    SDL_SCANCODE_9,     SDL_SCANCODE_U, SDL_SCANCODE_I,
    SDL_SCANCODE_O,     SDL_SCANCODE_J, SDL_SCANCODE_K,
    SDL_SCANCODE_L,     SDL_SCANCODE_M, SDL_SCANCODE_PERIOD,
    SDL_SCANCODE_0,     SDL_SCANCODE_P, SDL_SCANCODE_SEMICOLON,
    SDL_SCANCODE_SLASH};

void keyUp(uint8_t input[16], SDL_Scancode key) {
    switch (key) {
        case map[0x0]:
            input[0x0] = 0;
            break;
        case map[0x1]:
            input[0x1] = 0;
            break;
        case map[0x2]:
            input[0x2] = 0;
            break;
        case map[0x3]:
            input[0x3] = 0;
            break;
        case map[0x4]:
            input[0x4] = 0;
            break;
        case map[0x5]:
            input[0x5] = 0;
            break;
        case map[0x6]:
            input[0x6] = 0;
            break;
        case map[0x7]:
            input[0x7] = 0;
            break;
        case map[0x8]:
            input[0x8] = 0;
            break;
        case map[0x9]:
            input[0x9] = 0;
            break;
        case map[0xA]:
            input[0xA] = 0;
            break;
        case map[0xB]:
            input[0xB] = 0;
            break;
        case map[0xC]:
            input[0xC] = 0;
            break;
        case map[0xD]:
            input[0xD] = 0;
            break;
        case map[0xE]:
            input[0xE] = 0;
            break;
        case map[0xF]:
            input[0xF] = 0;
            break;
        default:
            break;
    }
}

void keyDown(uint8_t input[16], SDL_Scancode key) {
    switch (key) {
        case map[0x0]:
            input[0x0] = 1;
            break;
        case map[0x1]:
            input[0x1] = 1;
            break;
        case map[0x2]:
            input[0x2] = 1;
            break;
        case map[0x3]:
            input[0x3] = 1;
            break;
        case map[0x4]:
            input[0x4] = 1;
            break;
        case map[0x5]:
            input[0x5] = 1;
            break;
        case map[0x6]:
            input[0x6] = 1;
            break;
        case map[0x7]:
            input[0x7] = 1;
            break;
        case map[0x8]:
            input[0x8] = 1;
            break;
        case map[0x9]:
            input[0x9] = 1;
            break;
        case map[0xA]:
            input[0xA] = 1;
            break;
        case map[0xB]:
            input[0xB] = 1;
            break;
        case map[0xC]:
            input[0xC] = 1;
            break;
        case map[0xD]:
            input[0xD] = 1;
            break;
        case map[0xE]:
            input[0xE] = 1;
            break;
        case map[0xF]:
            input[0xF] = 1;
            break;
        default:
            break;
    }
}

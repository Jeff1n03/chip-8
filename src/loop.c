#include "../include/loop.h"
#include "../include/cycle.h"
#include "../include/input.h"
#include "../include/video.h"
#include <SDL2/SDL_events.h>

bool loop(Parser *pars, SDL_Renderer *rend) {
    Chip8 *cpu = createChip8(pars->instr, pars->len);
    bool quit = false, ret = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
                } else if (e.key.keysym.scancode == SDL_SCANCODE_R) {
                    quit = true;
                    ret = true;
                } else {
                    keyDown(cpu->Input, e.key.keysym.scancode);
                }
            } else if (e.type == SDL_KEYUP) {
                keyUp(cpu->Input, e.key.keysym.scancode);
            }
        }
        cycle(cpu);
        video(cpu->Disp, rend);
    }
    destroyChip8(cpu);
    return ret;
}

#include "../include/loop.h"
#include "../include/cycle.h"
#include "../include/input.h"
#include "../include/video.h"
#include <SDL2/SDL_events.h>

void loop(Chip8 *cpu, SDL_Renderer *rend) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
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
}

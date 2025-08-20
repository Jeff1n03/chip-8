#include "../include/loop.h"
#include "../include/cycle.h"
#include "../include/input.h"
#include "../include/video.h"
#include <SDL2/SDL_events.h>
#include <time.h>

static inline double getTime(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static void input(bool *quit, bool *ret, SDL_Event *e, uint8_t input[16]) {
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.scancode == SDL_SCANCODE_Q) {
            *quit = true;
        } else if (e->key.keysym.scancode == SDL_SCANCODE_R) {
            *quit = true;
            *ret = true;
        } else {
            keyDown(input, e->key.keysym.scancode);
        }
    } else if (e->type == SDL_KEYUP) {
        keyUp(input, e->key.keysym.scancode);
    }
}

static void timers(Chip8 *cpu, Audio *a, bool *queue) {
    if (cpu->DT > 0) {
        cpu->DT--;
    }
    if (cpu->ST > 0) {
        *queue = true;
        SDL_QueueAudio(a->dev, a->buf, a->bufSize);
        cpu->ST--;
    } else if (queue) {
        *queue = false;
        SDL_ClearQueuedAudio(a->dev);
    }
}

bool loop(Parser *pars, SDL_Renderer *rend, Audio *a) {
    Chip8 *cpu = createChip8(pars->instr, pars->len);
    bool quit = false, ret = false, queue = true;
    SDL_Event e;
    clock_t clk = clock(), tmr = clock();
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            input(&quit, &ret, &e, cpu->Input);
        }
        clock_t tmpClk = clock();
        if (getTime(clk, tmpClk) >= 0.002) {
            cycle(cpu);
            clk = tmpClk;
        }
        clock_t tmpTmr = clock();
        if (getTime(tmr, tmpTmr) >= 1.0 / 60.0) {
            timers(cpu, a, &queue);
            tmr = tmpTmr;
            video(cpu->Disp, rend);
        }
    }
    if (queue) {
        SDL_ClearQueuedAudio(a->dev);
    }
    destroyChip8(cpu);
    return ret;
}

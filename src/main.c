#include "../include/loop.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define X 64
#define Y 32
#define FREQUENCY 300
#define AMPLITUDE 500

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: invalid no. of arguments\n");
        return 1;
    }
    Parser *pars = parse(argv[1]);
    if (pars == NULL) {
        fprintf(stderr, "Error: cannot read input file\n");
        return 1;
    }
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Window *win = SDL_CreateWindow(
        "CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderSetLogicalSize(rend, X, Y);
    Audio *a = createAudio(FREQUENCY, AMPLITUDE);
    SDL_PauseAudioDevice(a->dev, 0);
    while (loop(pars, rend, a))
        ;
    destroyAudio(a);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    freeParser(pars);
    return 0;
}

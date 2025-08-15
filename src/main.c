#include "../include/loop.h"
#include <SDL2/SDL.h>

#define X 64
#define Y 32

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    Parser *pars = parse(argv[1]);
    if (pars == NULL) {
        return 1;
    }
    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Window *win = SDL_CreateWindow(
        "CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderSetLogicalSize(rend, X, Y);
    while (loop(pars, rend))
        ;
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    freeParser(pars);
    return 0;
}

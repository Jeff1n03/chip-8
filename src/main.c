#include "../include/loop.h"
#include "../include/parser.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    Parser *p = parse(argv[1]);
    if (p == NULL) {
        return 1;
    }
    Chip8 *cpu = createChip8(p->instr, p->len);
    freeParser(p);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Window *win = SDL_CreateWindow(
        "CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderSetLogicalSize(rend, X, Y);
    loop(cpu, rend);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    destroyChip8(cpu);
    return 0;
}

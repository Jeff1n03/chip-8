#include "../include/cycle.h"
#include "../include/parser.h"
#include "../include/video.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    /* TODO */
    Parser *p = parse("/Users/jeffinjacob/Downloads/test_opcode.ch8");
    Chip8 *ch = createChip8(p->instr, p->len);
    freeParser(p);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Window *win = SDL_CreateWindow(
        "CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderSetLogicalSize(ren, X, Y);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                quit = true;
            }
        }
        cycle(ch);
        video(ch->Disp, ren);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    destroyChip8(ch);
    return 0;
}

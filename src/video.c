#include "../include/video.h"
#include <stdbool.h>

static bool isValid(SDL_Renderer *rend) {
    int x, y;
    SDL_RenderGetLogicalSize(rend, &x, &y);
    return x == X && y == Y;
}

void video(uint8_t disp[Y][X], SDL_Renderer *rend) {
    if (isValid(rend)) {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (disp[y][x]) {
                    SDL_RenderDrawPoint(rend, x, y);
                }
            }
        }
        SDL_RenderPresent(rend);
    }
}

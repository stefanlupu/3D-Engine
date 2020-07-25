#include <SDL2/SDL.h>
#include "data-structures.h"

void drawTriangle(triangle t, SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, t.verteces[0].x, t.verteces[0].y, t.verteces[1].x, t.verteces[1].y);
    SDL_RenderDrawLine(renderer, t.verteces[1].x, t.verteces[1].y, t.verteces[2].x, t.verteces[2].y);
    SDL_RenderDrawLine(renderer, t.verteces[2].x, t.verteces[2].y, t.verteces[0].x, t.verteces[0].y);
}

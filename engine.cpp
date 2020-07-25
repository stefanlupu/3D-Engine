#include <SDL2/SDL.h>
#include <stdio.h>
#include "data-structures.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    // initialize objects
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // raise an error if SDL fails to load
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // raise error if window/renderer creation fails
        if (window == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        } else if (renderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        } else {
            // rendering triangle test
            triangle triangle = {
                {{100, 100},{200, 200},{150, 300}}
            };

            // set backgroud to white
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawTriangle(triangle, renderer);

            SDL_RenderPresent(renderer);

            SDL_Delay(2000);
        }
    }
}

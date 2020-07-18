#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    // initialize objects
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    // raise an error if SDL fails to load
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            // raise another error if window creation fails
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        } else {
            // simple boiler plate to test if everything is set up correctly 
            surface = SDL_GetWindowSurface(window);

            SDL_FillRect(surface, NULL, SDL_MapRGB(surface -> format, 255, 255, 255));

            SDL_UpdateWindowSurface(window);

            SDL_Delay(2000);
        }
    }
}

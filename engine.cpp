#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "data-structures.h"

// screen properties
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// perspective projection properties
const float aspectRatio = 720.0f / 1280.0f;
const float fovRadians = 1.0f / (tanf(90.0f * 0.5f  * 3.14159f / 180.0f));

int main(int argc, char* args[]) {
    // initialize objects
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    bool isRunning = false;

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
            triangle triangleTest = {
                {100, 100, 0,   200, 200, 0,   150, 300, 0}
            };

            // unit lenght cube to test project funtion
            mesh unitCube = {
                {
                    // S
                    triangle{{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}}},
                    triangle{{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}},

                    // N
                    triangle{{{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}},
                    triangle{{{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}},

                    // E
                    triangle{{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}},
                    triangle{{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}},

                    // W
                    triangle{{{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}},
                    triangle{{{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}},

                    // Top
                    triangle{{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}},
                    triangle{{{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}},

                    // Bottom
                    triangle{{{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}}},
                    triangle{{{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}},
                }
            };

            // initialize perspective matrix responsible for projecting 3D coordinates to 2D
            matrix_4D perspectiveMatrix = {
                {
                    { aspectRatio * fovRadians, 0.0f, 0.0f, 0.0f},
                    { 0.0f, fovRadians, 0.0f, 0.0f},
                    { 0.0f, 0.0f, 1000.0f / (1000.0f - 0.1f), 1.0f},
                    { 0.0f, 0.0f, -1000.0f * 0.1 / (1000.0f - 0.1f), 0.0f},
                }
            };

            // initialize rotation matrix which will rotate the x and z planes
            float theta = 0.0f;
            matrix_4D rotationXZMatrix = {
                {
                    {cosf(theta), sinf(theta) * cosf(theta * 0.5f), sinf(theta) * sinf(theta * 0.5f), 0.0f},
                    {-sinf(theta), cosf(theta) * cosf(theta * 0.5f), cosf(theta) * sinf(theta * 0.5), 0.0f},
                    {0.0f, -sinf(theta * 0.5), cosf(theta * 0.5), 0.0f},
                    {0.0f, 0.0f, 0.0f, 1.0f},
                }
            };

            Uint64 currentTime = SDL_GetPerformanceCounter();
            Uint64 lastTime = 0;
            double dt = 0;

            // engine loop
            isRunning = true;
            while (isRunning) {
                // update delta time
                lastTime = currentTime;
                currentTime = SDL_GetPerformanceCounter();

                dt = (double)(currentTime - lastTime) / SDL_GetPerformanceFrequency();

                // poll for events
                while (SDL_PollEvent(&event) != 0) {
                    // exit engine loop if window x button is pressed
                    if (event.type == SDL_QUIT) {
                        isRunning = false;
                    }
                }

                // key presses
                const Uint8* keyStates = SDL_GetKeyboardState(NULL);
                // exit engine loop if escape key is pressed
                if (keyStates[SDL_SCANCODE_ESCAPE]) {
                    isRunning = false;
                }

                // update rotation matrix
                rotationXZMatrix = {
                    {
                        {cosf(theta), sinf(theta) * cosf(theta * 0.5f), sinf(theta) * sinf(theta * 0.5f), 0.0f},
                        {-sinf(theta), cosf(theta) * cosf(theta * 0.5f), cosf(theta) * sinf(theta * 0.5), 0.0f},
                        {0.0f, -sinf(theta * 0.5), cosf(theta * 0.5), 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f},
                    }
                };

                // update angle of rotation in relation to delta time
                theta += 1 * dt;

                // set backgroud to white
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                //drawTriangle(triangleTest, renderer);
                for (int i = 0; i < unitCube.poligons.size(); i++) {

                    // make a copy of the current poligon
                    triangle poligonCopy = unitCube.poligons[i];
                    // initialise empty triangle used for vertex processing
                    triangle rotatedPoligon = {0};
                    triangle projectedPoligon = {0};

                    rotatedPoligon.verteces[0] = projectVector(poligonCopy.verteces[0], rotationXZMatrix);
                    rotatedPoligon.verteces[1] = projectVector(poligonCopy.verteces[1], rotationXZMatrix);
                    rotatedPoligon.verteces[2] = projectVector(poligonCopy.verteces[2], rotationXZMatrix);


                    // offset current poligon in order to position it in front of the camera
                    rotatedPoligon.verteces[0].z += 3.0f;
                    rotatedPoligon.verteces[1].z += 3.0f;
                    rotatedPoligon.verteces[2].z += 3.0f;

                    // project current poligons verteces using the projection matrix
                    projectedPoligon.verteces[0] = projectVector(rotatedPoligon.verteces[0], perspectiveMatrix);
                    projectedPoligon.verteces[1] = projectVector(rotatedPoligon.verteces[1], perspectiveMatrix);
                    projectedPoligon.verteces[2] = projectVector(rotatedPoligon.verteces[2], perspectiveMatrix);

                    // scale points back into screen space
                    projectedPoligon.verteces[0].x += 1.0f;
                    projectedPoligon.verteces[1].x += 1.0f;
                    projectedPoligon.verteces[2].x += 1.0f;

                    projectedPoligon.verteces[0].y += 1.0f;
                    projectedPoligon.verteces[1].y += 1.0f;
                    projectedPoligon.verteces[2].y += 1.0f;

                    projectedPoligon.verteces[0].x *= 0.5f * (float)SCREEN_WIDTH;
                    projectedPoligon.verteces[1].x *= 0.5f * (float)SCREEN_WIDTH;
                    projectedPoligon.verteces[2].x *= 0.5f * (float)SCREEN_WIDTH;

                    projectedPoligon.verteces[0].y *= 0.5f * (float)SCREEN_HEIGHT;
                    projectedPoligon.verteces[1].y *= 0.5f * (float)SCREEN_HEIGHT;
                    projectedPoligon.verteces[2].y *= 0.5f * (float)SCREEN_HEIGHT;

                    // render current poligon
                    drawTriangle(projectedPoligon, renderer);
                }

                // update
                SDL_RenderPresent(renderer);
            }

            // free resources
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
        }
    }
}

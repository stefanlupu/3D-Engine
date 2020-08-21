#pragma once
#include <vector>
#include <math.h>

struct vector_3D {
        float x, y, z;
};

struct triangle {
        vector_3D verteces[3];
};

void drawTriangle(triangle t, SDL_Renderer* renderer);

struct mesh {
        std::vector<triangle> poligons;
};

// perspective projection matrix
const float aspectRatio = 720.0f / 1280.0f;
const float fovRadians = 1.0f / (tanf(90.0f * 0.5f  * 3.14159f / 180.0f));

struct perspectiveProjection {
        float cells[4][4] = {
            { aspectRatio * fovRadians, 0.0f, 0.0f, 0.0f},
            { 0.0f, fovRadians, 0.0f, 0.0f},
            { 0.0f, 0.0f, 1000.0f / (1000.0f - 0.1f), 1.0f},
            { 0.0f, 0.0f, -1000.0f * 0.1 / (1000.0f - 0.1f), 0.0f}
        };
};

vector_3D projectVector(vector_3D v, perspectiveProjection m);

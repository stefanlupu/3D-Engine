#pragma once
#include <vector>

struct vector_3D {
        float x, y, z;
};

//vector_3D project(vector_3D v, int);

struct triangle {
        vector_3D verteces[3];
};

void drawTriangle(triangle t, SDL_Renderer* renderer);

struct mesh {
        std::vector<triangle> poligons;
};

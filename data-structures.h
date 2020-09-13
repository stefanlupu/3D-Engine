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
vector_3D calculateTriangleNormal(triangle t);

struct mesh {
        std::vector<triangle> poligons;
};

struct matrix_4D {
        float cells[4][4] = {0};
};

vector_3D projectVector(vector_3D v, matrix_4D m);

#include <SDL2/SDL.h>
#include <math.h>
#include "data-structures.h"

// render given triangle onto specified renderer
void drawTriangle(triangle t, SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, t.verteces[0].x, t.verteces[0].y, t.verteces[1].x, t.verteces[1].y);
    SDL_RenderDrawLine(renderer, t.verteces[1].x, t.verteces[1].y, t.verteces[2].x, t.verteces[2].y);
    SDL_RenderDrawLine(renderer, t.verteces[2].x, t.verteces[2].y, t.verteces[0].x, t.verteces[0].y);
}

// return the normal of a given triangle in normalized form
vector_3D calculateTriangleNormal(triangle t) {
    vector_3D normal;
    vector_3D lineA;
    vector_3D lineB;

    lineA.x = t.verteces[1].x - t.verteces[0].x;
    lineA.y = t.verteces[1].y - t.verteces[0].y;
    lineA.z = t.verteces[1].z - t.verteces[0].z;

    lineB.x = t.verteces[2].x - t.verteces[0].x;
    lineB.y = t.verteces[2].y - t.verteces[0].y;
    lineB.z = t.verteces[2].z - t.verteces[0].z;

    normal.x = lineA.y * lineB.z - lineA.z * lineB.y;
    normal.y = lineA.x * lineB.z - lineA.z * lineB.x;
    normal.z = lineA.x * lineB.y - lineA.y * lineB.x;

    float length = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

    normal.x /= length;
    normal.y /= length;
    normal.z /= length;

    return normal;
}

// return a perspective projected version of a given 3D vector
vector_3D projectVector(vector_3D v, matrix_4D m) {
    vector_3D pv;

    pv.x = v.x * m.cells[0][0] + v.y * m.cells[1][0] + v.z * m.cells[2][0] + m.cells[3][0];
    pv.y = v.x * m.cells[0][1] + v.y * m.cells[1][1] + v.z * m.cells[2][1] + m.cells[3][1];
    pv.z = v.x * m.cells[0][2] + v.y * m.cells[1][2] + v.z * m.cells[2][2] + m.cells[3][2];

    float w = v.x * m.cells[0][3] + v.y * m.cells[1][3] + v.z * m.cells[2][3] + m.cells[3][3];

    if (w != 0.0f) {
        pv.x /= w;
        pv.y /= w;
        pv.z /= w;
    }

    return pv;
}

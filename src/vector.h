#include <SDL3/SDL.h>
#include <math.h>

#ifndef VECTOR_H
#define VECTOR_H

// typedef struct Vector {
//   float x;
//   float y;
// } Vector;

typedef SDL_FPoint Vector;

Vector Vector_new_speed(Vector); 

#endif

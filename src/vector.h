#include <SDL3/SDL.h>
#include <math.h>

#ifndef VECTOR_H
#define VECTOR_H

typedef SDL_FPoint Vector;

Vector Vector_new_velocity(Vector); 
float Vector_get_length(Vector);
float Vector_dot_product(Vector, Vector); 
float Vector_get_cos(Vector, Vector);
float Vector_get_angle(Vector, Vector);
Vector Vector_abs(Vector);
Vector Vector_only_x(Vector);
Vector Vector_only_y(Vector);

#endif

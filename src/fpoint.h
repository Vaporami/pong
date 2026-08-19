#include <SDL3/SDL.h>

#include "vector.h"

#ifndef FPOINT_H
#define FPOINT_H

typedef SDL_FPoint Fpoint;

bool Fpoint_move(Fpoint*, Vector);
bool Fpoint_move_dt(Fpoint*, Vector, uint64_t);

bool Fpoint_set_x(Fpoint*, Fpoint*, float);
bool Fpoint_set_y(Fpoint*, Fpoint*, float);
bool Fpoint_set_xy(Fpoint*, Fpoint*, Vector);

bool Fpoint_check_collisions(Fpoint*, Fpoint*);

#endif

#include <SDL3/SDL.h>

#include "fpoint.h"
#include "vector.h"

#ifndef FRECT_H
#define FRECT_H

typedef SDL_FRect Frect;

bool Frect_move(Frect*, Vector);
bool Frect_move_dt(Frect*, Vector, uint64_t);

bool Frect_set_x(Frect*, Fpoint*, float);
bool Frect_set_y(Frect*, Fpoint*, float);
bool Frect_set_xy(Frect*, Fpoint*, Vector);

bool Frect_check_collisions(Frect*, Frect*);

bool Frect_is_out_of_bounds(Frect*, Frect*, bool, bool);
#endif

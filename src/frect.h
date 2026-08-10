#include <SDL3/SDL.h>

#include "fpoint.h"

#ifndef FRECT_H
#define FRECT_H

typedef SDL_FRect Frect;

bool Frect_move(Frect*, float, float);
bool Frect_move_dt(Frect*, float, float, uint64_t);

bool Frect_set_x(Frect*, Fpoint*, float);
bool Frect_set_y(Frect*, Fpoint*, float);
bool Frect_set_xy(Frect*, Fpoint*, float, float);

#endif

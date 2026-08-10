#include <SDL3/SDL.h>

#ifndef FPOINT_H
#define FPOINT_H

typedef SDL_FPoint Fpoint;

bool Fpoint_move(Fpoint*, float, float);
bool Fpoint_move_dt(Fpoint*, float, float, uint64_t);

bool Fpoint_set_x(Fpoint*, Fpoint*, float);
bool Fpoint_set_y(Fpoint*, Fpoint*, float);
bool Fpoint_set_xy(Fpoint*, Fpoint*, float, float);

#endif

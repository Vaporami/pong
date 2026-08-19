#include <SDL3/SDL.h>

#include "frect.h"
#include "fpoint.h"
#include "vector.h"

#ifndef BOX_H
#define BOX_H

typedef struct Box {
  Frect rect;
  Fpoint center;
} Box;

Box* Box_new(Frect*);
bool Box_destroy(Box*);

bool Box_render(SDL_Renderer*, Box*);

bool Box_move(Box*, Vector);
bool Box_move_dt(Box*, Vector, uint64_t);

bool Box_set_x(Box*, Fpoint*, float);
bool Box_set_y(Box*, Fpoint*, float);
bool Box_set_xy(Box*, Fpoint*, Vector);

bool Box_check_collisions(Box*, Box*, bool);

bool Box_is_out_of_bounds(Box*, Box*, bool, bool);
bool Box_is_out_of_Frect_bounds(Box*, Frect*, bool, bool);
#endif

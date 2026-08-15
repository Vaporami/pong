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

#endif

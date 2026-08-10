#include <SDL3/SDL.h>

#include "frect.h"
#include "fpoint.h"

#ifndef BOX_H
#define BOX_H

typedef struct Box {
  Frect rect;
  Fpoint center;
} Box;

Box* Box_new(Frect*);
void Box_destroy(Box*);

bool Box_move(Box*, float, float);
bool Box_move_dt(Box*, float, float, uint64_t);

bool Box_set_x(Box*, Fpoint*, float);
bool Box_set_y(Box*, Fpoint*, float);
bool Box_set_xy(Box*, Fpoint*, float, float);

#endif

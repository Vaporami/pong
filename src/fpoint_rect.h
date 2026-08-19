#include <SDL3/SDL.h>

#include "frect.h"
#include "fpoint.h"

#ifndef FPOINT_RECT_H
#define FPOINT_RECT_H

typedef struct Fpoint_rect {
  Fpoint upper_left;
  Fpoint upper_right;
  Fpoint lower_left;
  Fpoint lower_right;
} Fpoint_rect;

Fpoint_rect Frect_to_Fpoint_rect(Frect*); 
bool Fpoint_rect_check_collisions(Fpoint_rect* a, Fpoint_rect* b);

#endif

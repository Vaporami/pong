#include <SDL3/SDL.h>

#include "sprite_data.h"

#ifndef SPRITE_H
#define SPRITE_H

typedef struct sprite {
  sprite_data* data;
  SDL_FRect dest_rect;
  SDL_FPoint pivot;
  SDL_FPoint center;
} sprite;

sprite* sprite_new(sprite_data*, SDL_FRect*, SDL_FPoint*);

bool sprite_render(SDL_Renderer*, sprite*, bool, bool, bool);

// Used for single displacement
bool sprite_move(sprite*, float, float);

// Used for continuous movement.
// The given values are scaled by the given delta time.
// Delta time - it's the time between the start of one tick and the start of the next one.
bool sprite_move_dt(sprite*, float, float, uint64_t);

bool sprite_set_x(sprite*, float);
bool sprite_set_y(sprite*, float);
bool sprite_set_xy(sprite*, float, float);

bool sprite_center_by_pivot(sprite*, bool, bool, uint32_t, uint32_t);
bool sprite_center_by_center(sprite*, bool, bool, uint32_t, uint32_t);

#endif

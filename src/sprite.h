#include <SDL3/SDL.h>

#include "sprite_data.h"

#ifndef SPRITE_H
#define SPRITE_H

#define CENTERING_BY_CENTER  1
#define CENTERING_BY_PIVOT   2

typedef struct sprite {
  sprite_data* data;
  SDL_FRect dest_rect;
  SDL_FPoint pivot;
  SDL_FPoint center;
} sprite;

sprite* sprite_new(sprite_data*, SDL_FRect*, SDL_FPoint*);

bool sprite_render(SDL_Renderer*, sprite*, bool, bool, bool);

// Used for single displacement
bool sprite_move(sprite*, SDL_FPoint*);

// Used for continuous movement.
// Consistent between frames.
// The given values are scaled by the given delta time.
// Delta time - it's the time between the start of one tick and the start of the next one.
// "vector" should contain the amount of pixels to move by per second on both "x" and "y" axes
bool sprite_move_cbf(sprite*, SDL_FPoint*, uint64_t);

bool sprite_set_xy(sprite*, SDL_FPoint*);

#endif

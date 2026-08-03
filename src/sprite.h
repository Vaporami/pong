#include <SDL3/SDL.h>

#include "sprite_data.h"

#ifndef SPRITE_H
#define SPRITE_H

typedef struct sprite {
  sprite_data* data;
  float x;
  float y;
} sprite;

sprite* sprite_new(sprite_data*, float, float);
bool sprite_render(SDL_Renderer*, sprite*, bool);

#endif

#include <SDL3/SDL.h>

#include "sprite_data.h"

#include "box.h"

#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite {
  Sprite_data* data;
  Box* box;
} Sprite;

Sprite* Sprite_new(Sprite_data*, Box*);
bool Sprite_destroy(Sprite*);

bool Sprite_render(SDL_Renderer*, Sprite*, bool);

bool Sprite_move(Sprite*, float, float);
bool Sprite_move_dt(Sprite*, float, float, uint64_t);

bool Sprite_set_x(Sprite*, Fpoint*, float);
bool Sprite_set_y(Sprite*, Fpoint*, float);
bool Sprite_set_xy(Sprite*, Fpoint*, float, float);

#endif

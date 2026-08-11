#include <SDL3/SDL.h>

#include "frect.h"
#include "fpoint.h"

#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

typedef struct Sprite_data {
  SDL_Texture* texture;
  Frect src_rect;
} Sprite_data;

Sprite_data* Sprite_data_new(SDL_Texture*, Frect*);
Sprite_data* Sprite_data_new_from_bmp(SDL_Renderer*, const char*, Frect*);
bool Sprite_data_destroy(Sprite_data*);

#endif

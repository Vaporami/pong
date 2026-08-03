#include <SDL3/SDL.h>

#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

typedef struct sprite_data {
  SDL_Texture* texture;
  SDL_FRect src_rect;
} sprite_data;

sprite_data* sprite_data_new(SDL_Texture*, SDL_FRect*);
sprite_data* sprite_data_new_from_bmp(SDL_Renderer*, const char*, SDL_FRect*);

#endif

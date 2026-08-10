#include <stdlib.h>

#include <SDL3/SDL.h>

#include "sprite_data.h"

Sprite_data* Sprite_data_new(SDL_Texture* texture, Frect* init_src_rect) {
  const char* func_title = "Sprite_data_new()";

  Sprite_data* data = (Sprite_data*)malloc(sizeof(Sprite_data));

  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : The given texture is NULL", func_title);
    return NULL;
  }

  Frect src_rect = { .x = 0, .y = 0, .w = texture->w, .h = texture->h };
  if (init_src_rect == NULL) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : The given src_rect is NULL. The sprite is gonna use the whole texture!", func_title);
  } else {
    if (init_src_rect->w <= 0 || init_src_rect->h <= 0) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : The given src_rect has invalid width or height", func_title);
      return NULL;
    }
    src_rect = *init_src_rect;
  }

  data->texture = texture;
  data->src_rect = src_rect;

  return data;
}

Sprite_data* Sprite_data_new_from_bmp(SDL_Renderer* renderer, const char* path, Frect* src_rect) {
  const char* func_title = "Sprite_data_new_from_bmp()";

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(path));
  Sprite_data* data = Sprite_data_new(texture, src_rect);
  if (data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_data_new() returned NULL", func_title);
  }
  return data;
}

bool Sprite_data_destroy(Sprite_data* data) {
  const char* func_title = "Sprite_data_destroy()";

  if (data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : data appeared to be NULL", func_title);
    return false;
  }

  SDL_DestroyTexture(data->texture);
  free(data);

  return false;
}

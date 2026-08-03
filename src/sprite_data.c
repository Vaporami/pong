#include <stdlib.h>

#include <SDL3/SDL.h>

#include "sprite_data.h"

sprite_data* sprite_data_new(SDL_Texture* texture, SDL_FRect* src_rect) {
  const char* func_title = "sprite_data_new()";

  sprite_data* data = (sprite_data*)malloc(sizeof(sprite_data));

  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : The given texture is NULL", func_title);
    return NULL;
  }

  data->texture = texture;
  data->src_rect = *src_rect;

  return data;
}

sprite_data* sprite_data_new_from_bmp(SDL_Renderer* renderer, const char* path, SDL_FRect* src_rect) {
  const char* func_title = "sprite_data_new_from_bmp()";

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(path));

  SDL_FRect rect = { .x = 0, .y = 0, .w = texture->w, .h = texture->h };
  if (src_rect == NULL) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : The given src_rect is NULL. The sprite is gonna use the whole texture!", func_title);
  } else {
    rect = *src_rect;
  }

  return sprite_data_new(texture, &rect);
}

bool sprite_data_destroy(sprite_data* data) {
  const char* func_title = "sprite_data_destroy()";

  if (data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : data appeared to be NULL", func_title);
    return false;
  }

  SDL_DestroyTexture(data->texture);
  free(data);

  return false;
}

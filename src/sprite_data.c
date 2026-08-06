#include <stdlib.h>

#include <SDL3/SDL.h>

#include "sprite_data.h"

sprite_data* sprite_data_new(SDL_Texture* texture, SDL_FRect* init_src_rect) {
  const char* func_title = "sprite_data_new()";

  sprite_data* data = (sprite_data*)malloc(sizeof(sprite_data));

  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : The given texture is NULL", func_title);
    return NULL;
  }

  // if user sent NULL as init_src_rect, then we assume that the sprite should be made from the whole texture
  // else, we assume that the sprite should be made from some piece of the texture, and this requires the exact position and width and height of the piece
  // if we need a piece of texture, but width or height is less than or equal to 0, then we can't get any piece of texture, and we also can't use the whole texture
  SDL_FRect src_rect = { .x = 0, .y = 0, .w = texture->w, .h = texture->h };
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

sprite_data* sprite_data_new_from_bmp(SDL_Renderer* renderer, const char* path, SDL_FRect* src_rect) {
  const char* func_title = "sprite_data_new_from_bmp()";

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(path));
  sprite_data* data = sprite_data_new(texture, src_rect);
  if (data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : sprite_data_new() returned NULL", func_title);
  }
  return data;
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

#include <stdlib.h>

#include <SDL3/SDL.h>

#include "sprite.h"

sprite* sprite_new(sprite_data* data, float x, float y) {
  const char* func_title = "sprite_new(sprite_data*, SDL_FRect*)";

  sprite* spr = (sprite*)malloc(sizeof(sprite));

  if (data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : data appeared to be NULL!", func_title);
    return NULL;
  }

  spr->data = data;
  spr->x = x;
  spr->y = y;

  return spr;
}

bool sprite_render(SDL_Renderer* renderer, sprite* spr, bool outline) {
  const char* func_title = "sprite_render(SDL_Renderer*, sprite*)";

  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t a = 0;

  if (!SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a)) {
    SDL_LogError(SDL_LOG_CATEGORY_GPU, "%s : %s", func_title, SDL_GetError());
    return false;
  };

  if (renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s : renderer appeared to be NULL!", func_title);
    return false;
  }

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  SDL_FRect dest_rect = { .x = spr->x, .y = spr->y, .w = spr->data->src_rect.w, .h = spr->data->src_rect.h };
  if (!SDL_RenderTexture(renderer, spr->data->texture, &(spr->data->src_rect), &dest_rect)) {
    SDL_LogError(SDL_LOG_CATEGORY_GPU, "%s : %s", func_title, SDL_GetError());
    return false;
  };

  if (outline) {
    if (!SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderRect(renderer, &dest_rect)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_SetRenderDrawColor(renderer, r, g, b, a)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }
  }

  return true;
}


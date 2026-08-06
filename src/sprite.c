#include <stdlib.h>

#include <SDL3/SDL.h>

#include "sprite.h"

sprite* sprite_new(sprite_data* init_data, SDL_FRect* init_dest_rect, SDL_FPoint* init_pivot) {
  const char* func_title = "sprite_new()";

  sprite* spr = (sprite*)malloc(sizeof(sprite));

  if (init_data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : data appeared to be NULL!", func_title);
    return NULL;
  }

  // initially, dest_rect's size equals to init_data->src_rect, and its position equals to (0,0) of the window;
  SDL_FRect dest_rect = { .x = 0, .y = 0, .w = init_data->src_rect.w, .h = init_data->src_rect.h };
  if (init_dest_rect == NULL) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : dest_rect appeared to be NULL! The function is gonna use init_data->src_rect to make a dest_rect", func_title);
  } else if (init_dest_rect->w == 0.0f || init_dest_rect->h == 0.0f) {
    dest_rect.x = init_dest_rect->x;
    dest_rect.y = init_dest_rect->y;
  } else {
    dest_rect = *init_dest_rect;
  }

  SDL_FPoint center = { .x = dest_rect.x + (dest_rect.w / 2), .y = dest_rect.y + (dest_rect.h / 2) };

  // initially, pivot's position equals to dest_rect's center
  SDL_FPoint pivot = center;
  if (init_pivot == NULL) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : init_pivot appeared to be NULL! The function is gonna use dest_rect to define a pivot", func_title);
  } else {
    pivot = *init_pivot;
  }

  spr->data       = init_data;
  spr->dest_rect  = dest_rect;
  spr->pivot      = pivot;
  spr->center     = center;

  return spr;
}

bool sprite_render(SDL_Renderer* renderer, sprite* spr, bool render_dest_rect, bool render_pivot, bool render_center) {
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

  if (!SDL_RenderTexture(renderer, spr->data->texture, &(spr->data->src_rect), &(spr->dest_rect))) {
    SDL_LogError(SDL_LOG_CATEGORY_GPU, "%s : %s", func_title, SDL_GetError());
    return false;
  };

  if (render_dest_rect) {
    if (!SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderRect(renderer, &(spr->dest_rect))) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }
  }

  if (render_pivot) {
    SDL_FRect rect = { .x = spr->pivot.x - 1, .y = spr->pivot.y - 1 , .w = 3, .h = 3};

    if (!SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderPoint(renderer, spr->pivot.x, spr->pivot.y)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderRect(renderer, &rect)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }
  }

  if (render_center) {
    SDL_FRect rect = { .x = spr->center.x - 1, .y = spr->center.y - 1 , .w = 3, .h = 3};

    if (!SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderPoint(renderer, spr->pivot.x, spr->pivot.y)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderRect(renderer, &rect)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }
  }

  if (!SDL_SetRenderDrawColor(renderer, r, g, b, a)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  return true;
}

bool sprite_move(sprite* spr, float x, float y) {
  const char* func_title = "sprite_move()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  spr->dest_rect.x += x;
  spr->dest_rect.y += y;

  spr->pivot.x += x;
  spr->pivot.y += y;

  spr->center.x += x;
  spr->center.y += y;

  return true;
}

bool sprite_move_dt(sprite* spr, float x_per_second, float y_per_second, uint64_t delta_time) {
  const char* func_title = "sprite_move()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  float delta_time_seconds = (float)delta_time / 1000.0f;

  spr->dest_rect.x += x_per_second * delta_time_seconds;
  spr->dest_rect.y += y_per_second * delta_time_seconds;

  spr->pivot.x += x_per_second * delta_time_seconds;
  spr->pivot.y += y_per_second * delta_time_seconds;

  spr->center.x += x_per_second * delta_time_seconds;
  spr->center.y += y_per_second * delta_time_seconds;

  return true;
}

// Instead of setting the new position directly, we calculate the difference between the old and new positions.
// Then move the sprite and its internals by the difference with sprite_move() function, because that's easier, than every time recalculate center and pivot.
bool sprite_set_xy(sprite* spr, float new_x, float new_y) {
  const char* func_title = "sprite_set_xy()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  float diff_x = new_x - spr->dest_rect.x;
  float diff_y = new_y - spr->dest_rect.y;

  return sprite_move(spr, diff_x, diff_y);
}


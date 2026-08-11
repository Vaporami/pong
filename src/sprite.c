#include <stdlib.h>

#include <SDL3/SDL.h>

#include "sprite.h"
#include "frect.h"
#include "fpoint.h"

Sprite* Sprite_new(Sprite_data* init_data, Box* init_box) {
  const char* func_title = "Sprite_new()";

  Sprite* spr = (Sprite*)malloc(sizeof(Sprite));

  if (init_data == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : init_data appeared to be NULL!", func_title);
    return NULL;
  }

  if (init_box == NULL) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : init_box appeared to be NULL! The src_rect of the given init_data is used!", func_title);
    init_box = Box_new(&(init_data->src_rect));
  }

  spr->data  = init_data;
  spr->box   = init_box;

  return spr;
}

bool Sprite_destroy(Sprite* sprite) {
  const char* func_title = "Sprite_destroy()";
  
  if (sprite == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : sprite appeared to be NULL!", func_title);
    return false;
  }

  bool result = true; // 1 ; 0000 0001 ; 0 ; 0000 0000

  result &= Sprite_data_destroy(sprite->data);
  result &= Box_destroy(sprite->box);

  return result;
}

bool Sprite_render(SDL_Renderer* renderer, Sprite* spr, bool render_box) {
  const char* func_title = "Sprite_render(SDL_Renderer*, sprite*)";

  if (renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s : renderer appeared to be NULL!", func_title);
    return false;
  }

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  if (!SDL_RenderTexture(renderer, spr->data->texture, &(spr->data->src_rect), &(spr->box->rect))) {
    SDL_LogError(SDL_LOG_CATEGORY_GPU, "%s : %s", func_title, SDL_GetError());
    return false;
  };

  if (render_box) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;
    
    if (!SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a)) {
      SDL_LogError(SDL_LOG_CATEGORY_GPU, "%s : %s", func_title, SDL_GetError());
      return false;
    }
    
    if (!SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderRect(renderer, &(spr->box->rect))) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    Frect outline_center_rect = { .x = spr->box->center.x-1, .y = spr->box->center.y-1, .w = 3, .h = 3 };
    if (!SDL_RenderRect(renderer, &outline_center_rect)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, SDL_ALPHA_OPAQUE)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
      return false;
    }

    if (!SDL_RenderPoint(renderer, spr->box->center.x, spr->box->center.y)) {
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

bool Sprite_move(Sprite* spr, float x, float y) {
  const char* func_title = "Sprite_move()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  return Box_move(spr->box, x, y);
}

bool Sprite_move_dt(Sprite* spr, float x_per_second, float y_per_second, uint64_t delta_time) {
  const char* func_title = "Sprite_move_dt()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  return Box_move_dt(spr->box, x_per_second, y_per_second, delta_time);
}

bool Sprite_set_x(Sprite* spr, Fpoint* pivot, float new_x) {
  const char* func_title = "Sprite_set_x()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  return Box_set_x(spr->box, pivot, new_x);
}

bool Sprite_set_y(Sprite* spr, Fpoint* pivot, float new_y) {
  const char* func_title = "Sprite_set_y()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  return Box_set_y(spr->box, pivot, new_y);
}

bool Sprite_set_xy(Sprite* spr, Fpoint* pivot, float new_x, float new_y) {
  const char* func_title = "Sprite_set_xy()";

  if (spr == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : spr appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Box_set_xy(spr->box, pivot, new_x, new_y);

  return result;
}

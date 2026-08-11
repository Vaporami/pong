#include <stdlib.h>

#include <SDL3/SDL.h>

#include "pad.h"

Pad* Pad_new(Sprite* init_sprite, float init_speed_per_second) {
  const char* func_title = "Pad_new()";

  if (init_sprite == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : init_sprite appeared to be NULL!", func_title);
    return NULL;
  }

  Pad* pad = (Pad*)malloc(sizeof(Pad));

  pad->sprite  = init_sprite;
  pad->box     = Box_new(&(init_sprite->box->rect));
  pad->speed   = init_speed_per_second;

  return pad;
}

bool Pad_destroy(Pad* pad) {
  const char* func_title = "Pad_destroy()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_destroy(pad->sprite);
  result &= Box_destroy(pad->box);

  return result;
} 

bool Pad_render(SDL_Renderer* renderer, Pad* pad, bool render_sprite_box, bool render_box) {
  const char* func_title = "Pad_render()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_render(renderer, pad->sprite, render_sprite_box);
  if (render_box) {
    result &= Box_render(renderer, pad->box);
  }
  return result;
}

bool Pad_move(Pad* pad, float x, float y) {
  const char* func_title = "Pad_move()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_move(pad->sprite, x, y);
  result &= Box_move(pad->box, x, y);

  return result;
}

bool Pad_move_dt(Pad* pad, float x_per_second, float y_per_second, uint64_t delta_time) {
  const char* func_title = "Pad_move_dt()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_move_dt(pad->sprite, x_per_second, y_per_second, delta_time);
  result &= Box_move_dt(pad->box, x_per_second, y_per_second, delta_time);

  return result;
}

bool Pad_set_x(Pad* pad, Fpoint* pivot, float x) {
  const char* func_title = "Pad_set_x()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_x(pad->sprite, pivot, x);
  result &= Box_set_x(pad->box, pivot, x);

  return result;
}

bool Pad_set_y(Pad* pad, Fpoint* pivot, float y) {
  const char* func_title = "Pad_set_y()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_y(pad->sprite, pivot, y);
  result &= Box_set_y(pad->box, pivot, y);

  return result;
}

bool Pad_set_xy(Pad* pad, Fpoint* pivot, float x, float y) {
  const char* func_title = "Pad_set_xy()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_xy(pad->sprite, pivot, x, y);
  result &= Box_set_xy(pad->box, pivot, x, y);

  return result;
}

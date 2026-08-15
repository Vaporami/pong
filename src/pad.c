#include <stdlib.h>

#include <SDL3/SDL.h>

#include "pad.h"

Pad* Pad_new(Sprite* init_sprite, Vector init_speed) {
  const char* func_title = "Pad_new()";

  if (init_sprite == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : init_sprite appeared to be NULL!", func_title);
    return NULL;
  }

  Pad* pad = (Pad*)malloc(sizeof(Pad));

  pad->sprite            = init_sprite;
  pad->box               = Box_new(&(init_sprite->box->rect));
  pad->speed             = init_speed;

  if (!Vector_normalize(&init_speed)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Vector_normalize() returned false!", func_title);
    return NULL;
  }

  pad->speed.x *= init_speed.x;
  pad->speed.y *= init_speed.y;

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

bool Pad_move(Pad* pad, Vector diff) {
  const char* func_title = "Pad_move()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_move(pad->sprite, diff);
  result &= Box_move(pad->box, diff);

  return result;
}

bool Pad_move_dt(Pad* pad, Vector speed, uint64_t delta_time) {
  const char* func_title = "Pad_move_dt()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_move_dt(pad->sprite, speed, delta_time);
  result &= Box_move_dt(pad->box, speed, delta_time);

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

  if (pivot == NULL) {
    result &= Sprite_set_y(pad->sprite, NULL, y); // pivot == центр спрайта
    result &= Box_set_y(pad->box, NULL, y); // pivot == центр спрайта
  } else {
    Fpoint pivot_copy = *pivot;
    result &= Sprite_set_y(pad->sprite, &(pivot_copy), y); // pivot == центр спрайта
    result &= Box_set_y(pad->box, &(pivot_copy), y); // pivot == центр спрайта
  }

  return result;
}

bool Pad_set_xy(Pad* pad, Fpoint* pivot, Vector position) {
  const char* func_title = "Pad_set_xy()";

  if (pad == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : pad appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Sprite_set_xy(pad->sprite, pivot, position);
  result &= Box_set_xy(pad->box, pivot, position);

  return result;
}

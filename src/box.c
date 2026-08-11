#include <stdlib.h>

#include <SDL3/SDL.h>

#include "frect.h"
#include "fpoint.h"
#include "box.h"

Box* Box_new(Frect* init_rect) {
  const char* func_title = "Box_new()";

  if (init_rect == NULL) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : init_rect appeared to be NULL!", func_title);
    return NULL;
  }

  // initially, pivot's position equals to dest_rect's center

  Box* box = (Box*)malloc(sizeof(Box));

  box->rect    = *init_rect;
  box->center  = (Fpoint){ .x = box->rect.x + (box->rect.w / 2), .y = box->rect.y + (box->rect.h / 2) };

  return box;
}

bool Box_destroy(Box* box) {
  const char* func_title = "Box_destroy()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  free(box);

  return true;
}

bool Box_render(SDL_Renderer* renderer, Box* box) {
  const char* func_title = "Box_render()";
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

  if (!SDL_RenderRect(renderer, &(box->rect))) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  Frect outline_center_rect = { .x = box->center.x - 1, .y = box->center.y - 1, .w = 3, .h = 3 };
  if (!SDL_RenderRect(renderer, &outline_center_rect)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, SDL_ALPHA_OPAQUE)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!SDL_RenderPoint(renderer, box->center.x, box->center.y)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!SDL_SetRenderDrawColor(renderer, r, g, b, a)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  return true;
}

bool Box_move(Box* box, float x, float y) {
  const char* func_title = "Box_move()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  Frect_move(&(box->rect), x, y);
  Fpoint_move(&(box->center), x, y);

  return true;
}

bool Box_move_dt(Box* box, float x_per_second, float y_per_second, uint64_t delta_time) {
  const char* func_title = "Box_move_dt()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  Frect_move_dt(&(box->rect), x_per_second, y_per_second, delta_time);
  Fpoint_move_dt(&(box->center), x_per_second, y_per_second, delta_time);

  return true;
}

bool Box_set_x(Box* box, Fpoint* pivot, float x) {
  const char* func_title = "Box_set_x()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  if (pivot == NULL) {
    float diff = x - box->rect.x;
    result &= Box_move(box, diff, 0);
  } else {
    float diff = x - pivot->x;
    result &= Box_move(box, diff, 0);
  }

  return result;
}

bool Box_set_y(Box* box, Fpoint* pivot, float y) {
  const char* func_title = "Box_set_y()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  if (pivot == NULL) {
    float diff = y - box->rect.y;
    result &= Box_move(box, 0, diff);
  } else {
    float diff = y - pivot->y;
    result &= Box_move(box, 0, diff);
  }

  return result;
}

bool Box_set_xy(Box* box, Fpoint* pivot, float x, float y) {
  const char* func_title = "Box_set_xy()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  // if (pivot == NULL) {
  //   float diff_x = x - box->rect.x;
  //   float diff_y = y - box->rect.y;
  //   result &= Box_move(box, diff_x, diff_y);
  // } else {
  //   float diff_x = x - pivot->x;
  //   float diff_y = y - pivot->y;
  //   result &= Box_move(box, diff_x, diff_y);
  // }

  result &= Box_set_x(box, pivot, x);
  result &= Box_set_y(box, pivot, y);

  return result;
}

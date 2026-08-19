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

  if (!SDL_SetRenderDrawColor(renderer, r, g, b, a)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  return true;
}

bool Box_move(Box* box, Vector diff) {
  const char* func_title = "Box_move()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  Frect_move(&(box->rect), diff);
  Fpoint_move(&(box->center), diff);

  return true;
}

bool Box_move_dt(Box* box, Vector speed, uint64_t delta_time) {
  const char* func_title = "Box_move_dt()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  Frect_move_dt(&(box->rect), speed, delta_time);
  Fpoint_move_dt(&(box->center), speed, delta_time);

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
    Vector vdiff = { .x = diff, .y = 0.0f };
    result &= Box_move(box, vdiff);
  } else {
    float diff = x - pivot->x;
    Vector vdiff = { .x = diff, .y = 0.0f };
    result &= Box_move(box, vdiff);
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
    Vector vdiff = { .x = 0.0f, .y = diff };
    result &= Box_move(box, vdiff);
  } else {
    float diff = y - pivot->y;
    Vector vdiff = { .x = 0.0f, .y = diff };
    result &= Box_move(box, vdiff);
  }

  return result;
}

bool Box_set_xy(Box* box, Fpoint* pivot, Vector position) {
  const char* func_title = "Box_set_xy()";

  if (box == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  bool result = true;

  result &= Box_set_x(box, pivot, position.x);
  result &= Box_set_y(box, pivot, position.y);

  return result;
}

bool Box_check_collisions(Box* a, Box* b, bool include_centers_collisions) {
  const char* func_title = "Box_check_collisions()";

  if (a == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"a\" box appeared to be NULL!", func_title);
    return false;
  }

  if (b == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"b\" box appeared to be NULL!", func_title);
    return false;
  }

  bool result = Frect_check_collisions(&(a->rect), &(b->rect));
  if (include_centers_collisions) {
    result &= Fpoint_check_collisions(&(a->center), &(b->center));
  }

  return result;
}

bool Box_is_out_of_bounds(Box* box, Box* bounds, bool on_x, bool on_y) {
  const char* func_title = "Box_is_out_of_bounds()";

  if (box == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  if (bounds == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : bounds appeared to be NULL!", func_title);
    return false;
  }

  return Frect_is_out_of_bounds(&(box->rect), &(bounds->rect), on_x, on_y);
}

bool Box_is_out_of_Frect_bounds(Box* box, Frect* bounds, bool on_x, bool on_y) {
  const char* func_title = "Box_is_out_of_Frect_bounds()";

  if (box == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : box appeared to be NULL!", func_title);
    return false;
  }

  if (bounds == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : bounds appeared to be NULL!", func_title);
    return false;
  }

  return Frect_is_out_of_bounds(&(box->rect), bounds, on_x, on_y);
}

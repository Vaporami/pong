#include <SDL3/SDL.h>

#include "fpoint.h"

bool Fpoint_move(Fpoint* fpoint, Vector diff) {
  const char* func_title = "Fpoint_move()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  fpoint->x += diff.x;
  fpoint->y += diff.y;
  
  return true;
}

bool Fpoint_move_dt(Fpoint* fpoint, Vector speed, uint64_t delta_time) {
  const char* func_title = "Fpoint_move_dt()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  float delta_time_seconds = (float)delta_time / 1000.0f;

  fpoint->x += speed.x * delta_time_seconds;
  fpoint->y += speed.y * delta_time_seconds;
  
  return true;
}

bool Fpoint_set_x(Fpoint* fpoint, Fpoint* pivot, float x) {
  const char* func_title = "fpoint_set_xy()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  if (pivot == NULL) {
    fpoint->x = x;
  } else {
    float diff = x - pivot->x;
    Vector vdiff = { .x = diff, .y = 0.0f };
    Fpoint_move(fpoint, vdiff);
  }

  return true;
}

bool Fpoint_set_y(Fpoint* fpoint, Fpoint* pivot, float y) {
  const char* func_title = "fpoint_set_xy()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  if (pivot == NULL) {
    fpoint->y = y;
  } else {
    float diff = y - pivot->y;
    Vector vdiff = { .x = 0.0f, .y = diff };
    Fpoint_move(fpoint, vdiff);
  }
  
  return true;
}

bool Fpoint_set_xy(Fpoint* fpoint, Fpoint* pivot, Vector position) {
  const char* func_title = "fpoint_set_xy()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  if (pivot == NULL) {
    fpoint->x = position.x;
    fpoint->y = position.y;
  } else {
    Vector vdiff = { .x = position.x - pivot->x, .y = position.y - pivot->y };
    Fpoint_move(fpoint, vdiff);
  }

  return true;
}

bool Fpoint_check_collisions(Fpoint* a, Fpoint* b) {
  const char* func_title = "Fpoint_check_collisions()";

  if (a == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"a\" fpoint appeared to be NULL!", func_title);
    return false;
  }

  if (b == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"b\" fpoint appeared to be NULL!", func_title);
    return false;
  }

  bool same_x = a->x == b->x;
  bool same_y = a->y == b->y;

  return same_x && same_y;
}

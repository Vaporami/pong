#include <SDL3/SDL.h>

#include "frect.h"

bool Frect_move(Frect* frect, float x, float y) {
  const char* func_title = "Frect_move()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  frect->x += x;
  frect->y += y;

  return true;
}

bool Frect_move_dt(Frect* frect, float x_per_second, float y_per_second, uint64_t delta_time) {
  const char* func_title = "Frect_move_dt()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  float delta_time_seconds = (float)delta_time / 1000.0f;

  frect->x += x_per_second * delta_time_seconds;
  frect->y += y_per_second * delta_time_seconds;

  return true;
}

bool Frect_set_x(Frect* frect, Fpoint* pivot, float x) {
  const char* func_title = "Frect_set_x()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  if (pivot == NULL) {
    frect->x = x;
  } else {
    float diff = x - pivot->x;
    Frect_move(frect, diff, 0);
  }

  return true;
}

bool Frect_set_y(Frect* frect, Fpoint* pivot, float y) {
  const char* func_title = "Frect_set_y()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  if (pivot == NULL) {
    frect->y = y;
  } else {
    float diff = y - pivot->y;
    Frect_move(frect, 0, diff);
  }

  return true;
}

bool Frect_set_xy(Frect* frect, Fpoint* pivot, float x, float y) {
  const char* func_title = "Frect_set_xy()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }
  
  if (pivot == NULL) {
    frect->x = x;
    frect->y = y;
  } else {
    float diff_x = x - pivot->x;
    float diff_y = y - pivot->y;
    Frect_move(frect, diff_x, diff_y);
  }
  return true;
}

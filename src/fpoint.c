#include <SDL3/SDL.h>

#include "fpoint.h"

bool Fpoint_move(Fpoint* fpoint, float x, float y) {
  const char* func_title = "Fpoint_move()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  fpoint->x += x;
  fpoint->y += y;
  
  return true;
}

bool Fpoint_move_dt(Fpoint* fpoint, float x_per_second, float y_per_second, uint64_t delta_time) {
  const char* func_title = "Fpoint_move_dt()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  float delta_time_seconds = (float)delta_time / 1000.0f;

  fpoint->x += x_per_second * delta_time_seconds;
  fpoint->y += y_per_second * delta_time_seconds;
  
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
    Fpoint_move(fpoint, diff, 0);
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
    Fpoint_move(fpoint, 0, diff);
  }
  
  return true;
}

bool Fpoint_set_xy(Fpoint* fpoint, Fpoint* pivot, float x, float y) {
  const char* func_title = "fpoint_set_xy()";

  if (fpoint == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : fpoint appeared to be NULL!", func_title);
    return false;
  }

  if (pivot == NULL) {
    fpoint->x = x;
    fpoint->y = y;
  } else {
    float diff_x = x - pivot->x;
    float diff_y = y - pivot->y;
    Fpoint_move(fpoint, diff_x, diff_y);
  }

  return true;;
}

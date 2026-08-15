#include <SDL3/SDL.h>

#include "frect.h"

bool Frect_move(Frect* frect, Vector diff) {
  const char* func_title = "Frect_move()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  frect->x += diff.x;
  frect->y += diff.y;

  return true;
}

bool Frect_move_dt(Frect* frect, Vector speed, uint64_t delta_time) {
  const char* func_title = "Frect_move_dt()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  float delta_time_seconds = (float)delta_time / 1000.0f;

  frect->x += speed.x * delta_time_seconds;
  frect->y += speed.y * delta_time_seconds;

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
    Vector vdiff = { .x = diff, .y = 0.0f };
    Frect_move(frect, vdiff);
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
    Vector vdiff = { .x = 0.0f, .y = diff };
    Frect_move(frect, vdiff);
  }

  return true;
}

bool Frect_set_xy(Frect* frect, Fpoint* pivot, Vector position) {
  const char* func_title = "Frect_set_xy()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }
  
  if (pivot == NULL) {
    frect->x = position.x;
    frect->y = position.y;
  } else {
    Vector vdiff = { .x = position.x - pivot->x, .y = position.y - pivot->y };
    Frect_move(frect, vdiff);
  }
  return true;
}

#include <SDL3/SDL.h>

#include "frect.h"
#include "fpoint_rect.h"

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

bool Frect_check_collisions(Frect* a, Frect* b) {
  const char* func_title = "Frect_check_collisions()";

  if (a == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"a\" frect appeared to be NULL!", func_title);
    return false;
  }

  if (b == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"b\" frect appeared to be NULL!", func_title);
    return false;
  }

  Fpoint_rect afpr = Frect_to_Fpoint_rect(a);
  Fpoint_rect bfpr = Frect_to_Fpoint_rect(b);

  return Fpoint_rect_check_collisions(&afpr, &bfpr);
}

bool Frect_is_out_of_bounds(Frect* frect, Frect* bounds, bool on_x, bool on_y) {
  const char* func_title = "Frect_is_out_of_bounds)";

  if (frect == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return false;
  }

  if (bounds == NULL)  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : bounds appeared to be NULL!", func_title);
    return false;
  }

  Fpoint frect_up_left = { .x = frect->x, .y = frect->y };
  Fpoint frect_low_right = { .x = frect_up_left.x + frect->w, .y = frect_up_left.y + frect->h };

  Fpoint bounds_up_left = { .x = frect->x, .y = frect->y };
  Fpoint bounds_low_right = { .x = bounds_up_left.x + frect->w, .y = bounds_up_left.y + frect->h };

  bool avoids_on_x = frect_up_left.x <= bounds_up_left.x && frect_low_right.x <= bounds_low_right.x;
  bool avoids_on_y = frect_up_left.y <= bounds_up_left.y && frect_low_right.y <= bounds_low_right.y;

  bool result = false;

  if (on_x && on_y) {
    result = avoids_on_x || avoids_on_y; 
  } else if (on_x) {
    result = avoids_on_x;
  } else if (on_y) {
    result = avoids_on_y;
  } else {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s : not axis was choosen! Returning false...", func_title);
  }

  return result;
}

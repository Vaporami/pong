#include <SDL3/SDL.h>

#include "fpoint_rect.h"

Fpoint_rect Frect_to_Fpoint_rect(Frect* frect) {
  const char* func_title = "Frect_to_Fpoint_rect()";

  if (frect == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : frect appeared to be NULL!", func_title);
    return (Fpoint_rect) {0};
  }

  return (Fpoint_rect) {
    .upper_left   = (Fpoint) { .x = frect->x, .y = frect->y },
    .upper_right  = (Fpoint) { .x = frect->x + frect->w, .y = frect->y },
    .lower_left   = (Fpoint) { .x = frect->x, .y = frect->y + frect->h },
    .lower_right  = (Fpoint) { .x = frect->x + frect->w, .y = frect->y + frect->h }
  };
}

bool Fpoint_rect_check_collisions(Fpoint_rect* a, Fpoint_rect* b) {
  const char* func_title = "Frect_to_Fpoint_rect()";

  if (a == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"a\" fpoint_rect appeared to be NULL!", func_title);
    return false;
  }

  if (b == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : \"b\" fpoint_rect appeared to be NULL!", func_title);
    return false;
  }

  bool upper_left_collide   =
    (b->upper_left.x <= a->upper_left.x && a->upper_left.x <= b->upper_right.x) && (b->upper_left.y <= a->upper_left.y && a->upper_left.y <= b->lower_left.y);
  bool upper_right_collide
    = (b->upper_left.x <= a->upper_right.x && a->upper_right.x <= b->upper_right.x) && (b->upper_right.y <= a->upper_right.y && a->upper_right.y <= b->lower_right.y);
  bool lower_left_collide
    = (b->lower_left.x <= a->lower_left.x && a->lower_left.x <= b->lower_right.x) && (b->lower_left.y <= a->lower_left.y && a->lower_left.y <= b->upper_left.y);
  bool lower_right_collide
    = (b->lower_left.x <= a->lower_right.x && a->lower_right.x <= b->lower_right.x) && (b->lower_right.y <= a->lower_right.y && a->lower_right.y <= b->upper_right.y);

  return upper_left_collide || upper_right_collide || lower_left_collide || lower_right_collide;
}

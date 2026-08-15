#include "vector.h"

bool Vector_normalize(Vector* vector) {
  const char* func_title = "Vector_normalize()";

  if (vector == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : vector appeared to be NULL!", func_title);
    return false;
  }

  float hypot = sqrtf(vector->x * vector->x + vector->y * vector->y);

  vector->x /= hypot;
  vector->y /= hypot;

  return true;
}

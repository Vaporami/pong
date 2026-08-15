#include <math.h>

#include "vector.h"

Vector Vector_new_speed(Vector vector) {
  float hypot = sqrtf(vector.x * vector.x + vector.y * vector.y);
  Vector speed = {
    .x = vector.x * vector.x / hypot,
    .y = vector.y * vector.y / hypot
  };
  if (vector.x < 0 && speed.x > 0) {
    speed.x *= -1;
  }
  if (vector.y < 0 && speed.y > 0) {
    speed.y *= -1;
  }
  SDL_Log("I was here!");
  return speed;
}

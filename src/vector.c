#include <math.h>

#include "vector.h"

Vector Vector_new_velocity(Vector raw_velocity) {
  float hypot = hypotf(raw_velocity.x, raw_velocity.y);

  Vector velocity = {
    .x = raw_velocity.x * fabsf(raw_velocity.x) / hypot,
    .y = raw_velocity.y * fabsf(raw_velocity.y) / hypot
  };

  return velocity;
}

float Vector_get_length(Vector v) {
  return hypotf(v.x, v.y);
}

float Vector_dot_product(Vector v1, Vector v2) {
  return v1.x * v2.x + v1.y * v2.y;
} 

float Vector_get_cos(Vector v1, Vector v2) {
  return Vector_dot_product(v1, v2) / (fabsf(Vector_get_length(v1)) * fabsf(Vector_get_length(v2)));
} 

float Vector_get_angle(Vector v1, Vector v2) {
  return acosf(Vector_get_cos(v1, v2));
} 

Vector Vector_abs(Vector v) {
  return (Vector){ .x = fabsf(v.x), .y = fabsf(v.y) };
}

Vector Vector_only_x(Vector v) {
  v.y = 0;
  return v;
}

Vector Vector_only_y(Vector v) {
  v.x = 0;
  return v;
}

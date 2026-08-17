#include <SDL3/SDL.h>

#include "sprite.h"
#include "vector.h"

typedef struct Ball {
  Sprite* sprite;

  Box* box;

  Vector raw_velocity;
  Vector velocity;

  uint32_t bounces;
} Ball;

bool Ball_apply_velocity(Ball*, Vector);
Ball* Ball_new(Sprite*, Vector);
bool Ball_destroy(Ball*);

bool Ball_render(SDL_Renderer*, Ball*, bool, bool);

bool Ball_move(Ball*, Vector);
bool Ball_move_dt(Ball*, Vector, uint64_t);

bool Ball_set_x(Ball*, Fpoint*, float);
bool Ball_set_y(Ball*, Fpoint*, float);
bool Ball_set_xy(Ball*, Fpoint*, Vector);

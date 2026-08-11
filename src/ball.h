#include <SDL3/SDL.h>

#include "sprite.h"

typedef struct Ball {
  Sprite* sprite;
  Box* box;
  float speed;
} Ball;

Ball* Ball_new(Sprite*, float);
bool Ball_destroy(Ball*);

bool Ball_render(SDL_Renderer*, Ball*, bool, bool);

bool Ball_move(Ball*, float, float);
bool Ball_move_dt(Ball*, float, float, uint64_t);

bool Ball_set_x(Ball*, Fpoint*, float);
bool Ball_set_y(Ball*, Fpoint*, float);
bool Ball_set_xy(Ball*, Fpoint*, float, float);

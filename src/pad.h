#include <SDL3/SDL.h>

#include "sprite.h"
#include "vector.h"

typedef struct Pad {
  Sprite* sprite;
  Box* box;

  Vector raw_velocity;
  Vector velocity;
} Pad;

bool Pad_apply_velocity(Pad*, Vector);
Pad* Pad_new(Sprite*, Vector);
bool Pad_destroy(Pad*);

bool Pad_render(SDL_Renderer*, Pad*, bool, bool);

bool Pad_move(Pad*, Vector);
bool Pad_move_dt(Pad*, Vector, uint64_t);

bool Pad_set_x(Pad*, Fpoint*, float);
bool Pad_set_y(Pad*, Fpoint*, float);
bool Pad_set_xy(Pad*, Fpoint*, Vector);

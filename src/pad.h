#include <SDL3/SDL.h>

#include "sprite.h"

typedef struct Pad {
  Sprite* sprite;
  Box* box;
  float speed;
} Pad;

Pad* Pad_new(Sprite*, float);
bool Pad_destroy(Pad*);

bool Pad_render(SDL_Renderer*, Pad*, bool, bool);

bool Pad_move(Pad*, float, float);
bool Pad_move_dt(Pad*, float, float, uint64_t);

bool Pad_set_x(Pad*, Fpoint*, float);
bool Pad_set_y(Pad*, Fpoint*, float);
bool Pad_set_xy(Pad*, Fpoint*, float, float);

#include <SDL3/SDL.h>

#include "sprite_data.h"
#include "sprite.h"

#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct application {
  SDL_Window* window;

  int32_t width;
  int32_t height;

  SDL_Renderer* renderer;
 
  const bool* keyboard;

  bool must_update_on_input; 

  // These two bools should be in a different "game" (or smth like that) struct
  bool must_move_pad_up;
  bool must_move_pad_down;

  sprite_data** sprite_data_set;
  sprite** sprite_set;

  uint64_t delta_time;

  bool running;
} application;

application* application_new(void);
void application_destroy(application*);
bool application_main(application*);

#endif

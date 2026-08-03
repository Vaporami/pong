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

  sprite_data** sprite_data_set;
  sprite** sprite_set;

  bool running;
} application;

application* application_new();

bool application_event_handling(application*);
bool application_render(application*);
bool application_main(application*);

#endif

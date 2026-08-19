#include <SDL3/SDL.h>

#include "sprite_data.h"
#include "sprite.h"
#include "pad.h"
#include "ball.h"

#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct Application {
  SDL_Window* window;

  int32_t width;
  int32_t height;

  SDL_Renderer* renderer;
 
  const bool* keyboard;

  bool must_update_on_input; 

  bool must_move_pad_up;
  bool must_move_pad_down;

  Sprite_data** sprite_data_set;
  Sprite** sprite_set;

  Pad* pad;
  Pad* rpad;
  Ball* ball;

  uint32_t pad_score;
  uint32_t rpad_score;
  uint32_t max_score;

  uint64_t delta_time;

  bool running;
} Application;

Application* Application_new(void);
void Application_destroy(Application*);
bool Application_main(Application*);

#endif

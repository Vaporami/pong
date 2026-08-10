#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "application.h"
#include "sprite_data.h"
#include "sprite.h"

#define SPRITE_SET_PAD 0
#define SPRITE_SET_RPAD 1
#define SPRITE_SET_BALL 2

Application* Application_new(void) {
  const char* func_title = "Application_new()";

  const uint32_t  WIDTH   = 1024;
  const uint32_t  HEIGHT  = 576;
  const char*     TITLE   = "Pong";

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Creating a new application's instance...", func_title);

  Application* app = (Application*)malloc(sizeof(Application));
  if (app == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : malloc() failed!", func_title);
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Space for application was allocated successfully!", func_title);

  app->window = SDL_CreateWindow(TITLE, WIDTH, HEIGHT, 0);
  if (app->window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
	      "%s : Window was created successfully with the name %s and size of %dx%d", func_title, TITLE, WIDTH, HEIGHT);

  app->width = WIDTH;
  app->height = HEIGHT;

  app->renderer = SDL_CreateRenderer(app->window, NULL);
  if (app->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_GPU,
	      "%s : Renderer was created successfully with the use of %s API", func_title, SDL_GetRendererName(app->renderer));

  app->keyboard = SDL_GetKeyboardState(NULL);

  Sprite_data** data_set = (Sprite_data**)malloc(3 * sizeof(Sprite_data*));
  data_set[0] = Sprite_data_new_from_bmp(app->renderer, "./data/bmps/pad.bmp", NULL);
  data_set[1] = Sprite_data_new_from_bmp(app->renderer, "./data/bmps/rpad.bmp", NULL);
  data_set[2] = Sprite_data_new_from_bmp(app->renderer, "./data/bmps/ball.bmp", NULL);

  app->sprite_data_set = data_set;

  Sprite** sprite_set = (Sprite**)malloc(3 * sizeof(Sprite*));

  sprite_set[0] = Sprite_new(data_set[0], Box_new(NULL));
  sprite_set[1] = Sprite_new(data_set[1], Box_new(NULL));
  sprite_set[2] = Sprite_new(data_set[2], Box_new(NULL));

  Sprite_set_y(sprite_set[SPRITE_SET_PAD],  &(sprite_set[SPRITE_SET_PAD]->box->center), (app->height / 2));
  Sprite_set_y(sprite_set[SPRITE_SET_RPAD], &(sprite_set[SPRITE_SET_RPAD]->box->center), (app->height / 2));
  Sprite_set_xy(sprite_set[SPRITE_SET_BALL], &(sprite_set[SPRITE_SET_BALL]->box->center), (app->width / 2), (app->height / 2));

  Sprite_set_x(sprite_set[SPRITE_SET_PAD], &(sprite_set[SPRITE_SET_PAD]->box->center), 100.0f);
  Sprite_set_x(sprite_set[SPRITE_SET_RPAD], &(sprite_set[SPRITE_SET_RPAD]->box->center), (float)app->width - 100.0f);

  app->sprite_set = sprite_set;

  app->must_update_on_input  = false;
  app->must_move_pad_up      = false;
  app->must_move_pad_down    = false;

  app->delta_time = 0;

  app->running = true;


  SDL_ShowWindow(app->window);
  return app;
}

void Application_destroy(Application* app) {
  for (int i = 0; i < 3; i++) {
    free(app->sprite_set[i]);
    free(app->sprite_data_set[i]);
  }
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
}

bool Application_input_handling(Application* app) {
  if (app->keyboard[SDL_SCANCODE_W]) {
    app->must_move_pad_up = true;
  } else {
    app->must_move_pad_up = false;
  }

  if (app->keyboard[SDL_SCANCODE_S]) {
    app->must_move_pad_down = true;
  } else {
    app->must_move_pad_down = false;
  }

  app->must_update_on_input = app->must_move_pad_up || app->must_move_pad_down;
  return app->must_update_on_input;
}

bool Application_close(Application* app) {
  const char* func_title = "Application_close()";
  app->running = false;
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : intended quit call, exiting...", func_title);
  return false;
}

bool Application_event_handling(Application* app) {

  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      Application_close(app);
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      if (event.key.scancode == SDL_SCANCODE_Q) {
	Application_close(app);
      }
    }
  }

  return true;
} 

bool Application_update_on_input(Application* app) {
  const char* func_title = "Application_update_on_input()";

  float speed = 500.0f;

  if (app->must_move_pad_up) {
    if (!Sprite_move_dt(app->sprite_set[SPRITE_SET_PAD], 0, -speed, app->delta_time)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_move returned false!", func_title);
      return false;
    }
  }

  if (app->must_move_pad_down) {
    if (!Sprite_move_dt(app->sprite_set[SPRITE_SET_PAD], 0, speed, app->delta_time)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_move returned false!", func_title);
      return false;
    }
  }


  return true;
}

bool Application_update_on_events(Application* app) {
  return app->running;
}

bool Application_render(Application* app) {
  const char* func_title = "Application_render()";

  if (!SDL_SetRenderDrawColor(app->renderer, 0x22, 0x80, 0x26, SDL_ALPHA_OPAQUE)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!SDL_RenderClear(app->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }



  if (!Sprite_render(app->renderer, app->sprite_set[SPRITE_SET_PAD], true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_render() returned false", func_title);
    return false;
  }

  if (!Sprite_render(app->renderer, app->sprite_set[SPRITE_SET_RPAD], true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_render() returned false", func_title);
    return false;
  }

  if (!Sprite_render(app->renderer, app->sprite_set[SPRITE_SET_BALL], true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : Sprite_render() returned false", func_title);
    return false;
  }



  if (!SDL_RenderPresent(app->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  return true;
}

bool Application_main(Application* app) {
  const char* func_title = "Application_main()";

  uint64_t end_time = 0;
  uint64_t start_time = SDL_GetTicks();

  while(app->running) {
    Application_input_handling(app);

    if (!Application_event_handling(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_event_handling() returned false", func_title);
      return false;
    }

    if (!Application_update_on_input(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_event_handling() returned false", func_title);
      return false;
    }

    if (!Application_update_on_events(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_event_handling() returned false", func_title);
      return false;
    }

    if (!Application_render(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Application_render() returned false", func_title);
      return false;
    }
    SDL_Delay(20);
    end_time = SDL_GetTicks();
    app->delta_time = end_time - start_time;
    start_time = SDL_GetTicks();
  }
  return true;
}

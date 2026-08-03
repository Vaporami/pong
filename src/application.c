#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "application.h"
#include "sprite_data.h"
#include "sprite.h"

#define SPRITE_SET_PAD 0
#define SPRITE_SET_RPAD 1
#define SPRITE_SET_BALL 2

application* application_new() {
  const char* func_title = "application_new()";

  const uint32_t  WIDTH   = 1024;
  const uint32_t  HEIGHT  = 576;
  const char*     TITLE   = "Pong";

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : Creating a new application's instance...", func_title);

  application* app = (application*)malloc(sizeof(application));
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

  sprite_data** data_set = (sprite_data**)malloc(3 * sizeof(sprite_data*));
  data_set[0] = sprite_data_new_from_bmp(app->renderer, "./data/bmps/pad.bmp", NULL);
  data_set[1] = sprite_data_new_from_bmp(app->renderer, "./data/bmps/rpad.bmp", NULL);
  data_set[2] = sprite_data_new_from_bmp(app->renderer, "./data/bmps/ball.bmp", NULL);
  app->sprite_data_set = data_set;

  sprite** sprite_set = (sprite**)malloc(3 * sizeof(sprite*));
  sprite_set[0] = sprite_new(data_set[0], 100, (app->height / 2) - (data_set[0]->src_rect.h / 2));
  sprite_set[1] = sprite_new(data_set[1], (app->width) - 100 - (data_set[1]->src_rect.w), (app->height / 2) - (data_set[1]->src_rect.h / 2));
  sprite_set[2] = sprite_new(data_set[2], (app->width / 2) - (data_set[2]->src_rect.w / 2), (app->height / 2) - (data_set[2]->src_rect.h / 2));
  app->sprite_set = sprite_set;

  app->running = true;

  SDL_ShowWindow(app->window);
  return app;
}

static bool application_close(application* app) {
  const char* func_title = "application_close()";
  app->running = false;
  SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "%s : intended quit call, exiting...", func_title);
  return false;
}

bool application_event_handling(application* app) {
  const char* func_title = "application_event_handling()";

  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      application_close(app);
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      if (event.key.scancode == SDL_SCANCODE_Q) {
	application_close(app);
      }
    }
  }

  return true;
} 

bool application_render(application* app) {
  const char* func_title = "application_render()";

  if (!SDL_SetRenderDrawColor(app->renderer, 0x22, 0x80, 0x26, SDL_ALPHA_OPAQUE)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!SDL_RenderClear(app->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  if (!sprite_render(app->renderer, app->sprite_set[SPRITE_SET_PAD], true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : sprite_render() returned false", func_title);
    return false;
  }

  if (!sprite_render(app->renderer, app->sprite_set[SPRITE_SET_RPAD], true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : sprite_render() returned false", func_title);
    return false;
  }

  if (!sprite_render(app->renderer, app->sprite_set[SPRITE_SET_BALL], true)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : sprite_render() returned false", func_title);
    return false;
  }

  if (!SDL_RenderPresent(app->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return false;
  }

  return true;
}

bool application_main(application* app) {
  const char* func_title = "application_main()";

  while(app->running) {
    if (!application_event_handling(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : application_event_handling(application*) returned false", func_title);
      return false;
    }
    if (!application_render(app)) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s : application_render(application*) returned false", func_title);
      return false;
    }
  }

  return true;
}

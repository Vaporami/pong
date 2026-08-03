#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "application.h"

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

  app->renderer = SDL_CreateRenderer(app->window, NULL);
  if (app->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s : %s", func_title, SDL_GetError());
    return NULL;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
	      "%s : Renderer was created successfully with the use of %s API", func_title, SDL_GetRendererName(app->renderer));

  app->running = true;

  SDL_ShowWindow(app->window);
  return app;
}

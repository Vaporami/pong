#include <stdio.h>

#include <SDL3/SDL.h>

#include "application.h"

int main(void) {
  if(!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
    return 1;
  };

  application* app = application_new();
  application_main(app);

  SDL_Quit();
  return 0;
}

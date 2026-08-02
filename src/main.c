#include <SDL3/SDL.h>

int main(void) {
  if(!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
    return 1;
  };
  SDL_Quit();
  return 0;
}

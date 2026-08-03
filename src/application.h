#include <SDL3/SDL.h>

typedef struct application {
  SDL_Window* window;

  int32_t width;
  int32_t height;

  SDL_Renderer* renderer;
 
  const bool* keyboard;

  bool running;
} application;

application* application_new();

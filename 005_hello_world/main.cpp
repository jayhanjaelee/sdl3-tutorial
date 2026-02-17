#include <SDL3/SDL.h>

int main() {
  if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
    SDL_Log("Failed!");
    return -1;
  }

  SDL_Window *window;
  window = SDL_CreateWindow("Hello World", 640, 400, SDL_WINDOW_RESIZABLE);
  SDL_RaiseWindow(window);

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }
    SDL_Delay(16); // 60 fps == 1 / 60 * 1000
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

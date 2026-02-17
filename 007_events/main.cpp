#include <SDL3/SDL.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window;
  window = SDL_CreateWindow("SDL3 - event", 320, 240, SDL_WINDOW_RESIZABLE);
  SDL_RaiseWindow(window);

  SDL_Event event;

  // For my application to run indefinitely
  bool running = true;
  while(running){
    // Event handling loop
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_EVENT_QUIT){
        running = false;
        break;
      }else if(event.type == SDL_EVENT_KEY_DOWN){
        SDL_Log("a key was pressed: %d", event.key.key);
      }
    }
    // Application/Game Logic
    // ...
  }

  SDL_Quit();

  return 0;
}

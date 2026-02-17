#include <SDL3/SDL.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window;
  window = SDL_CreateWindow("SDL3 - event", 320, 240, SDL_WINDOW_RESIZABLE);
  SDL_RaiseWindow(window);

  SDL_Event event;

  int w,h;
  // window 사이즈를 구해서 w, h 로 리턴.
  SDL_GetWindowSize(window, &w, &h);
  // Mouse 위치를 화면 중앙으로 위치시킨다.
  SDL_WarpMouseInWindow(window, (float)w/2, (float)h/2);

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
      }else if(event.type == SDL_EVENT_MOUSE_MOTION) {
        // SDL_Log("x,y: %f,%f", event.motion.x, event.motion.y);
      }else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.button.button == SDL_BUTTON_LEFT){
          SDL_Log("Left Button:%d", event.button.button);
        } else if(event.button.button == SDL_BUTTON_MIDDLE){
          SDL_Log("Middle Button:%d", event.button.button);
        } else if(event.button.button == SDL_BUTTON_RIGHT){
          SDL_Log("Right Button:%d", event.button.button);
        }
        SDL_Log("Clicks: %d", event.button.clicks);
      }
    }

    float x, y;
    // 윈도우 내부의 마우스 위치를 트랙킹함.
    // SDL_MouseButtonFlags mouse = SDL_GetMouseState(&x, &y);
    // 윈도우 바깥의 마우스 위치를 트랙킹함.
    SDL_MouseButtonFlags mouse = SDL_GetGlobalMouseState(&x, &y);
    SDL_Log("x,y: %f,%f", x,y);

    SDL_Delay(16);
  }

  SDL_Quit();

  return 0;
}

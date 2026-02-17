#include <SDL3/SDL.h>
#include <stdio.h>

struct SDLApplication {
  SDL_Window *mWindow;
  bool mRunning = true;

  // Constructor
  SDLApplication(const char *title) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *mWindow;
    mWindow = SDL_CreateWindow(title, 320, 240, SDL_WINDOW_RESIZABLE);
    SDL_RaiseWindow(mWindow);
  }

  // Destructor
  ~SDLApplication() {
    SDL_Quit();
  }

  void Tick() {
    SDL_Event event;

    // Mouse 위치를 화면 중앙으로 위치시킨다.
    // BAD ACCESS ERROR 발생.
    // SDL_WarpMouseInWindow(mWindow, w/2, h/2);

    // For my application to run indefinitely
    // Event handling loop
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_EVENT_QUIT){
        mRunning = false;
        break;
      }
      else if(event.type == SDL_EVENT_KEY_DOWN){
        SDL_Log("a key was pressed: %d", event.key.key);
      }
      else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.button.button == SDL_BUTTON_LEFT){
          SDL_Log("Left Button:%d", event.button.button);
        }
        if(event.button.button == SDL_BUTTON_MIDDLE){
          SDL_Log("Middle Button:%d", event.button.button);
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
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

  // Main application loop
  void MainLoop() {
    while(mRunning){
      Tick();
    }
  }
};

// Entry Point
int main(int argc, char *argv[]) {
  SDLApplication app("SDL3 Tutorials");
  app.MainLoop();
  return 0;
}

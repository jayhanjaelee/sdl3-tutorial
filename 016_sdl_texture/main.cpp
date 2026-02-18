#include <SDL3/SDL.h>
#include <cassert>
#include <iostream>

#define WINW 320
#define WINH 240

struct SDLApplication {
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

  // For my application indefinitely
  bool mRunning = true;
  bool mFullScreen = true;

  SDL_Texture *mTexture;

  // Constructor
  SDLApplication(const char *title) {
    SDL_Init(SDL_INIT_VIDEO);
    mWindow = SDL_CreateWindow(title, WINW, WINH, SDL_WINDOW_RESIZABLE);
    mRenderer = SDL_CreateRenderer(mWindow , nullptr); // OpenGL DirectX, Vulkan, Metal Support
    if (mRenderer == nullptr) {
      assert(0 && "Not able to create HW accelerated renderer");
    } else {
      SDL_Log("Renderer %s", SDL_GetRendererName(mRenderer)); // metal
                                                              // Log drivers that are available, in the order of priority SDL chooses them.
                                                              // Useful for e.g. debugging which ones a particular build of SDL contains.
      SDL_SetRenderLogicalPresentation(mRenderer, 320, 240, SDL_LOGICAL_PRESENTATION_STRETCH);
      // SDL_SetRenderLogicalPresentation(mRenderer, 320, 240, SDL_LOGICAL_PRESENTATION_LETTERBOX);
      // SDL_SetRenderLogicalPresentation(mRenderer, 320, 240, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
      /*
         SDL_Log("Available renderer drivers:");
         for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
         SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
         }
         */
    }
    SDL_RaiseWindow(mWindow);

    SDL_Surface *mSurface = SDL_LoadBMP("./character.bmp");
    mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
    /*
       mSurface = SDL_LoadBMP("./test.bmp");
       if (mSurface == nullptr) {
       assert(0 && "Improper file path found.");
       }
       */

    // blit -> bit block transfer (transfer rectangular block of pixel from one memory to another memory location)
  }

  // Destructor
  ~SDLApplication() {
    SDL_DestroyTexture(mTexture);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
  }

  void Tick() {
    Input();
    Update();
    Render();
  }

  void Input() {
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
        if((event.key.key == SDLK_LGUI) && (event.key.key == SDLK_F)){
          SDL_Log("command+f was pressed");
          mFullScreen = !mFullScreen;
          SDL_SetWindowFullscreen(mWindow, mFullScreen);
        }
      }
      else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.button.button == SDL_BUTTON_LEFT){
          SDL_Log("Left Button:%d", event.button.button);
          SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
          SDL_RenderClear(mRenderer);
        }
        if(event.button.button == SDL_BUTTON_MIDDLE){
          SDL_Log("Middle Button:%d", event.button.button);
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
          SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
          SDL_RenderClear(mRenderer);
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
    // SDL_Log("x,y: %f,%f", x,y);
  }

  void Update() {
  }

  void Render()
  {
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    static SDL_FRect dst_rect{
      .x = 50,
      .y = 50,
      .w = 16,
      .h = 16
    };
    dst_rect.x += .1f;
    SDL_RenderTexture(mRenderer, mTexture, nullptr, &dst_rect);

    SDL_RenderPresent(mRenderer);
    /*
       SDL_Surface *windowSurface = SDL_GetWindowSurface(mWindow);
       if (nullptr != windowSurface) {
       SDL_BlitSurface(mSurface , nullptr, windowSurface, nullptr);
       SDL_UpdateWindowSurface(mWindow);
       }
       */
  }

  // Main application loop
  void MainLoop() {
    Uint64 fps=0; // Number of frames per seconds
    Uint64 lastTime=0;
    while(mRunning){
      Uint64 currentTick = SDL_GetTicks();
      Tick();
      SDL_Delay(16); // set fps to 60 but why does my enviroment set it to 30?
      fps++;

      // Per frame calculator of elapsed time
      Uint64 deltaTime = SDL_GetTicks() - currentTick;
      // 1초가 지나면 fps 리셋
      // FPS calculation
      if(currentTick > lastTime + 1000){
        lastTime = currentTick;
        std::string title;
        title += "SDL3 Tutorials - FPS " + std::to_string(fps);
        SDL_SetWindowTitle(mWindow, title.c_str());
        fps = 0;
      }
    }
  }
};

// Entry Point
int main(int argc, char *argv[]) {
  SDLApplication app("SDL3 Tutorials");
  app.MainLoop();
  return 0;
}

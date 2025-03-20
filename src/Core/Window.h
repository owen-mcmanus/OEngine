#pragma once

#include "Renderer.h"
#include "SDLDeleter.h"

#include <SDL2/SDL.h>
#include <memory>

class Window {
  public:
    // Window();
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window() = default;

    Renderer& GetRenderer() const;

    void HandleEvent(const SDL_Event& event);
    void Clear() const;
    void Present() const;

  private:
    std::unique_ptr<SDL_Window, SDL_Deleter> window;
    std::unique_ptr<Renderer> renderer;
    // std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    // bool rendering_paused;
};

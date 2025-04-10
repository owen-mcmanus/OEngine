/**
 * @file Window.h
 * @author Owen McManus
 * @date 2025/9/4
 */

#pragma once

#include "../Utils/SDLDeleter.h"

#include <SDL3/SDL.h>
#include <memory>

namespace OEngine {

class Renderer;

class Window {
  public:
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window() = default;

    [[nodiscard]] Renderer& GetRenderer() const;

    void HandleEvent(const SDL_Event& event);

  private:
    std::unique_ptr<SDL_Window, SDL_Deleter> window;
    std::unique_ptr<Renderer> renderer;
};

} // namespace OEngine

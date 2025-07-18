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

/**
 * @brief A wrapper class for SDL_Window that includes a rendering context.
 *
 * The Window class is responsible for managing the SDL window and associated renderer,
 * and handling window-related events such as minimizing or restoring.
 */
class Window {
  public:
    /**
     * @brief Constructs a new Window.
     *
     * @param title Title of the window.
     * @param width Width of the window in pixels.
     * @param height Height of the window in pixels.
     * @param fullscreen Whether the window should start in fullscreen mode.
     * @throws std::runtime_error if window or renderer creation fails.
     */
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window() = default;

    static SDL_Window* GetSDLWindow();
    /**
     * @brief Gets a reference to the internal renderer associated with this window.
     *
     * @return Renderer& The renderer used for drawing operations.
     */
    [[nodiscard]] Renderer& GetRenderer() const;

    /**
     * @brief Handles SDL window events such as minimize and restore.
     *
     * @param event The SDL_Event received from the SDL event loop.
     */
    void HandleEvent(const SDL_Event& event);

  private:
    std::unique_ptr<SDL_Window, SDL_Deleter> window;
    std::unique_ptr<Renderer> renderer;
    static SDL_Window* windowInstance;
};

} // namespace OEngine

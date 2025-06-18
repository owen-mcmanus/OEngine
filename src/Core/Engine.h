/**
 * @file Engine.h
 * @author Owen McManus
 * @date 2025/4/11
 */

#pragma once

#include "../Events/Event.h"
#include "../Events/EventManager.h"
#include "SceneManager.h"

#include <memory>
#include <string>

/**
 * @namespace OEngine
 * @brief Contains all core components of the OEngine game engine.
 *
 * The OEngine namespace encapsulates the primary classes and functionality
 * of the game engine, including the Engine, Window, Scene, and SceneManager classes.
 */
namespace OEngine {

class Window;
class Scene;

/**
 * @class Engine
 * @brief Core engine class for OEngine.
 *
 * The Engine class encapsulates the primary functionality of the game engine,
 * including initialization, the main game loop, window creation, and scene management.
 */
class Engine {
  public:
    /**
     * @brief Constructs a new Engine object.
     *
     * Initializes the engine by setting up the logging system and the SDL environment.
     * Prepares the engine for running the game loop.
     *
     * @throw std::runtime_error if SDL_Init or IMG_Init fails.
     */
    Engine();

    /**
     * @brief Destroys the Engine object.
     *
     * Cleans up the engine by clearing texture caches, quitting SDL subsystems,
     * and closing the log file.
     */
    ~Engine();

    /**
     * @brief Starts the main game loop.
     *
     * Enters the main loop where events are processed, the active scene is updated,
     * and the window is rendered. The loop continues until a quit event is received.
     * Typically, CreateWindow() and SetActiveScene() are called prior to Run().
     *
     */
    void Run();

    /**
     * @brief Creates and initializes a new window.
     *
     * Allocates a new Window instance with the specified title, dimensions, and fullscreen mode.
     * This window is used for rendering.
     *
     * @param title The title of the window.
     * @param width The width of the window in pixels.
     * @param height The height of the window in pixels.
     * @param fullscreen True to create the window in fullscreen mode, false for windowed mode.
     * @return A reference to the newly created Window.
     */
    Window& CreateWindow(const std::string& title, int width, int height, bool fullscreen);

    /**
     * @brief Retrieves a reference to the current window.
     *
     * @return A reference to the active Window.
     * @throw std::runtime_error if no window has been created.
     * @pre A window must have been created via CreateWindow().
     */
    [[nodiscard]] Window& GetWindow() const;

    /**
     * @brief Signals the engine to stop running.
     *
     * Sets the internal running flag to `false`, which will cause the main game loop
     * to exit after the current iteration. Typically called in response to a quit event.
     */
    void Quit();

  private:
    volatile bool running = false; // marked volatile to supress warnings
    int frameDelay = 16;
    std::unique_ptr<Window> window;
    EventListener<QuitEvent> eventListener = [this](const QuitEvent& e) { Quit(); };
};

} // namespace OEngine
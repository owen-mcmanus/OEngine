#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"

#include <chrono>
namespace OEngine {
class Engine {
  public:
    Engine();
    explicit Engine(int fps);
    ~Engine();

    /**
     * @brief Runs the main game loop.
     *
     * This function starts the game loop, which handles events, updates the active scene, and
     * renders the scene. It also ensures that the game loop runs at a consistent frame rate based
     * on the `frameDelay`.
     */
    void Run();

    /**
     * @brief Creates a window for the game and returns a reference to it.
     *
     * @param title The title of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param fullscreen Whether the window should be fullscreen.
     * @return A reference to the created Window object.
     */
    Window& CreateWindow(const std::string& tite, int width, int height, bool fullscreen);

    /**
     * @brief Gets the current window.
     *
     * @return A reference to the current Window object.
     */
    [[nodiscard]] Window& GetWindow() const;

    /**
     * @brief Sets the active scene in the engine.
     *
     * @param scene A reference to the Scene object that will be set as the active scene.
     */
    void SetActiveScene(Scene& scene);

    /** @brief A flag that indicates whether the game loop is running or not. */
    bool running = false;

  private:
    std::chrono::milliseconds frameDelay;
    std::unique_ptr<Window> window;
    SceneManager sceneManager;
    void HandleEvents();
};
} // namespace OEngine
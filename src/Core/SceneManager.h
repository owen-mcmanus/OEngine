/**
 * @file SceneManager.h
 * @author Owen McManus
 * @date 2025/9/4
 */

#pragma once

#include <memory>
#include <optional>

namespace OEngine {

class Scene;
class Renderer;

/**
 * @brief Manages the active game scene.
 *
 * This class is responsible for storing a reference to the currently active scene
 * and delegating core lifecycle functions such as initialization, updates, rendering,
 * and event handling.
 */
class SceneManager {
  public:
    /**
     * @brief Sets the active scene and initializes it.
     *
     * @param scene A reference to the new active scene.
     */
    void SetActiveScene(Scene& scene);

    /**
     * @brief Forwards input or system events to the active scene.
     */
    void HandleEvents() const;

    /**
     * @brief Updates the logic of the active scene.
     */
    void Update() const;

    /**
     * @brief Renders the active scene.
     *
     * @param renderer The renderer used for drawing.
     */
    void Render(Renderer& renderer) const;

  private:
    std::optional<std::reference_wrapper<Scene>> activeScene;
};

} // namespace OEngine

/**
 * @file SceneManager.h
 * @author Owen McManus
 * @date 2025/6/18
 */

#pragma once

#include "Scene.h"

#include <memory>

namespace OEngine {

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
    static void SetActiveScene(std::unique_ptr<Scene>&& scene);

    /// Replace any existing scene with a freshly constructed on
    // template <class TScene, class... Args> static void MakeActiveScene(Args&&... args) {
    //     static_assert(std::is_base_of_v<Scene, TScene>, "TScene must derive from Scene");
    //     activeScene = std::make_unique<TScene>(std::forward<Args>(args)...);
    //     activeScene->Init();
    // }

    /**
     * @brief Updates the logic of the active scene.
     */
    static void Update(double deltaTime);

    /**
     * @brief Renders the active scene.
     *
     * @param renderer The renderer used for drawing.
     */
    static void Render(Renderer& renderer);
    static void ClearActiveScene();

  private:
    static std::unique_ptr<Scene> activeScene;
};

} // namespace OEngine

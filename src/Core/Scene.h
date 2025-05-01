/**
 * @file Scene.h
 * @author Owen McManus
 * @date 2025/5/1
 */

#pragma once
#include "GameObject.h"

#include <unordered_set>

namespace OEngine {

class Window;
class Renderer;

/**
 * @brief Interface for all scenes in the engine.
 *
 * Inherit from this class to implement your own game scenes.
 * Each scene must define its initialization, update, rendering, and event handling logic.
 */
class Scene {
  public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Scene() = default;

    /**
     * @brief Called once when the scene is first activated.
     */
    virtual void Init() = 0;

    /**
     * @brief Updates the scene logic every frame.
     */
    virtual void Update() = 0;

    /**
     * @brief Renders the scene to the screen.
     *
     * @param renderer The renderer used to draw the scene.
     */
    virtual void Render(Renderer& renderer) = 0;

    void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
    void RemoveGameObject(GameObject* ptr);

  protected:
    std::unordered_set<std::shared_ptr<GameObject>> activeGameObjects;
};
} // namespace OEngine
/**
 * @file Scene.h
 * @author Owen McManus
 * @date 2025/5/1
 */

#pragma once
#include "../GameObjects/Camera.h"
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
    virtual void Update(double deltaTime);
    virtual void PreUpdate(double deltaTime) {};
    virtual void PostUpdate(double deltaTime) {};

    /**
     * @brief Renders the scene to the screen.
     *
     * @param renderer The renderer used to draw the scene.
     */
    virtual void Render(Renderer& renderer);
    virtual void PreRender(Renderer& renderer) {};
    virtual void PostRender(Renderer& renderer) {};

    void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
    void RemoveGameObject(GameObject* ptr);

  protected:
    std::unordered_set<std::shared_ptr<GameObject>> activeGameObjects;
};
} // namespace OEngine
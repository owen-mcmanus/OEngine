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

class SceneManager {
  public:
    void SetActiveScene(Scene& scene);
    void HandleEvents() const;
    void Update() const;
    void Render(Renderer& renderer) const;

  private:
    std::optional<std::reference_wrapper<Scene>> activeScene;
};

} // namespace OEngine

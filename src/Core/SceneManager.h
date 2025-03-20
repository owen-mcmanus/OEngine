#pragma once
#include "Scene.h"
#include <memory>
#include <optional>

namespace OEngine {
class SceneManager {
  public:
    void SetActiveScene(Scene& scene);
    void HandleEvents();
    void Update();
    void Render(Renderer& renderer);

  private:
    std::optional<std::reference_wrapper<Scene>> activeScene;
};
} // namespace OEngine

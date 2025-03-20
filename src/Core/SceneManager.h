#pragma once

#include <memory>
#include <optional>

namespace OEngine {

class Scene;
class Renderer;

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

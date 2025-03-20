#pragma once
#include "Scene.h"
#include <memory>
#include <optional>

class SceneManager {
  public:
    void SetActiveScene(Scene& scene, Renderer& renderer);
    void HandleEvents();
    void Update();
    void Render(Renderer& renderer);

  private:
    std::optional<std::reference_wrapper<Scene>> activeScene;
};

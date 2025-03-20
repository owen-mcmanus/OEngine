#pragma once

namespace OEngine {

class Window;
class Renderer;

class Scene {
  public:
    virtual ~Scene() {}

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render(Renderer& renderer) = 0;
    virtual void HandleEvents() = 0;
};
} // namespace OEngine
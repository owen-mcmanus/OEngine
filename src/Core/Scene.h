#pragma once
#include "Window.h"

class Scene {
  public:
    virtual ~Scene() {}
    virtual void Init(Renderer& renderer) = 0;
    virtual void Update() = 0;
    virtual void Render(Renderer& renderer) = 0;
    virtual void HandleEvents() = 0;
};
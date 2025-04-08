#pragma once

#include "../src/Core/Renderer.h"
#include "../src/Core/Scene.h"
#include "../src/Core/Sprite.h"

class TestScene : public OEngine::Scene {
  public:
    TestScene() = default;
    ~TestScene() override;
    void Init() override;
    void Update() override;
    void HandleEvents() override;
    void Render(OEngine::Renderer& renderer) override;

  private:
    OEngine::Sprite* s = nullptr;
    OEngine::Sprite* s1 = nullptr;
    OEngine::Sprite* s2 = nullptr;
};
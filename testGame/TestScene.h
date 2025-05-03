#pragma once

#include "../src/Core/Renderer.h"
#include "../src/Core/Scene.h"
#include "../src/Events/EventManager.h"
#include "Plane.h"

class TestScene : public OEngine::Scene {
  public:
    TestScene() = default;
    ~TestScene() override;
    void Init() override;
    // void Update() override;
    void PreRender(OEngine::Renderer& renderer) override;

  private:
    Plane* s2 = nullptr;
    int spritePos = 300;

    OEngine::EventListener<OEngine::MouseButtonDownEvent> eventListener =
        [this](const OEngine::MouseButtonDownEvent& e) { spritePos = 300; };
    OEngine::EventListener<OEngine::MouseScrolledEvent> eventListener2 =
        [this](const OEngine::MouseScrolledEvent& e) { spritePos += e.GetScroll() * 30; };
};

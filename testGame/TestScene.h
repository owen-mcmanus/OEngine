#pragma once

#include "../src/Components/Sprite.h"
#include "../src/Core/GameObject.h"
#include "../src/Core/Renderer.h"
#include "../src/Core/Scene.h"
#include "../src/Events/EventManager.h"

#include <iostream>

class ResetEvent : public OEngine::Event {
  public:
    ResetEvent() = default;
    [[nodiscard]] OEngine::EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};

class TestScene : public OEngine::Scene {
  public:
    TestScene() = default;
    ~TestScene() override;
    void Init() override;
    void Update() override;
    void Render(OEngine::Renderer& renderer) override;

  private:
    OEngine::GameObject* s = nullptr;
    OEngine::GameObject* s1 = nullptr;
    OEngine::GameObject* s2 = nullptr;
    int spritePos = 300;

    OEngine::EventListener<OEngine::MouseButtonDownEvent> eventListener =
        [this](const OEngine::MouseButtonDownEvent& e) { spritePos = 300; };
    OEngine::EventListener<OEngine::MouseScrolledEvent> eventListener2 =
        [this](const OEngine::MouseScrolledEvent& e) { spritePos += e.GetScroll() * 30; };
};

#pragma once

#include "../src/Core/Renderer.h"
#include "../src/Core/Scene.h"
#include "../src/Core/Sprite.h"
#include "../src/Events/EventManager.h"
#include "../src/Utils/Keys.h"

#include <X11/X.h>
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
    OEngine::Sprite* s = nullptr;
    OEngine::Sprite* s1 = nullptr;
    OEngine::Sprite* s2 = nullptr;
    int spritePos = 300;

    OEngine::EventListener<OEngine::KeyDownEvent> eventListener1 =
        [this](const OEngine::KeyDownEvent& e) {
            // if (e.GetKey() == OEngine::Key::Keycode::SPACE)
            //     spritePos += 5;
            std::cout << static_cast<char>(e.GetKey()) << std::endl;
        };

    OEngine::EventListener<ResetEvent> eventListener = [this](const ResetEvent& e) {
        spritePos = 300;
    };
};

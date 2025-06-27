#pragma once
#include "../src/Components/Sprite.h"
#include "../src/Components/Transform.h"
#include "../src/Core/GameObject.h"
#include "../src/Events/Event.h"
#include "Events/EventManager.h"
#include "UI/Objects/Button.h"

class ResetEvent : public OEngine::Event {};

class PlaneController : public OEngine::Component {
  public:
    PlaneController() {
        OEngine::EventManager::AddListener<OEngine::UI::ButtonClickEvent>(&clickListener);
    }

    ~PlaneController() {
        OEngine::EventManager::RemoveListener<OEngine::UI::ButtonClickEvent>(&clickListener);
    }

    void Update(double deltaTime) override;

  private:
    bool rotate = false;
    OEngine::EventListener<OEngine::UI::ButtonClickEvent> clickListener =
        [this](const OEngine::UI::ButtonClickEvent& e) {
            if (e.name == "rotate")
                rotate = true;
        };
};

class Plane : public OEngine::GameObject {
  public:
    Plane(int x, int y) : GameObject(2) {
        AddComponent<OEngine::Transform>(x, y);
        AddComponent<OEngine::Sprite>(
            "/home/owen/github/OEngine/testGame/plane.png", 32, 32, false);
        AddComponent<PlaneController>();
    }
};

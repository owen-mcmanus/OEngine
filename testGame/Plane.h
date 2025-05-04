#pragma once
#include "../src/Components/Sprite.h"
#include "../src/Components/Transform.h"
#include "../src/Core/GameObject.h"
#include "../src/Events/Event.h"

class ResetEvent : public OEngine::Event {};

class PlaneController : public OEngine::Component {
  public:
    void Update(double deltaTime) override;
};

class Plane : public OEngine::GameObject {
  public:
    Plane(int x, int y) {
        AddComponent<OEngine::Transform>(x, y);
        AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
        AddComponent<PlaneController>();
    }
};

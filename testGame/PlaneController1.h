#pragma once
#include "../src/Components/Component.h"
#include "../src/Events/Event.h"

#include <memory>

class ResetEvent : public OEngine::Event {};

class PlaneController1 : public OEngine::Component {
  public:
    void Update(float deltaTime) override;
};

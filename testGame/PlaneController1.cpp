#include "PlaneController1.h"

#include "../src/Components/Transform.h"
#include "../src/Core/GameObject.h"
#include "../src/Events/EventManager.h"
#include "../src/IO/Keyboard.h"
#include "../src/IO/Mouse.h"

#include <iostream>

void PlaneController1::Update(const double deltaTime) {
    auto* t = owner->GetComponent<OEngine::Transform>();
    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::SPACE))
        t->Translate({0, 500 * deltaTime});
    if (OEngine::Mouse::IsPressed(OEngine::Mouse::MouseButton::MIDDLE)) {
        t->Translate({0, -500 * deltaTime});
    }
    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::W))
        t->localRotation += 90 * deltaTime;
    if (t->GetWorldPosition().y > 400) {
        OEngine::EventManager::AddEvent<ResetEvent>();
    }
}

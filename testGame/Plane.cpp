#include "Plane.h"

#include "../src/Events/EventManager.h"
#include "../src/IO/Keyboard.h"
#include "../src/IO/Mouse.h"

void PlaneController::Update(const double deltaTime) {
    auto* t = owner->GetComponent<OEngine::Transform>();

    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::SPACE))
        t->Translate({0, 500 * deltaTime});

    if (OEngine::Mouse::IsPressed(OEngine::Mouse::MouseButton::MIDDLE))
        t->Translate({0, -500 * deltaTime});

    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::G))
        t->localRotation += 90 * deltaTime;

    if (t->GetWorldPosition().y > 400)
        OEngine::EventManager::AddEvent<ResetEvent>();
}
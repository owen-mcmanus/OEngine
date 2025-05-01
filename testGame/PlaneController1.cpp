#include "PlaneController1.h"

#include "../src/Components/Transform.h"
#include "../src/Core/GameObject.h"
#include "../src/Events/EventManager.h"
#include "../src/IO/Keyboard.h"
#include "../src/IO/Mouse.h"

void PlaneController1::Update(float deltaTime) {
    auto* t = owner->GetComponent<OEngine::Transform>();
    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::SPACE))
        t->Translate({0, 5});
    if (OEngine::Mouse::IsPressed(OEngine::Mouse::MouseButton::MIDDLE)) {
        t->Translate({0, -5});
    }
    if (t->GetWorldPosition().y > 400) {
        OEngine::EventManager::AddEvent<ResetEvent>();
    }
}

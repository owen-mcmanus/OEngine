/**
 * @file Button.cpp
 * @author Owen McManus
 * @date 2025/5/18
 */

#include "Button.h"

#include "../../Components/PrimitiveSprite.h"
#include "../../Components/Transform.h"

using namespace OEngine::UI;

ButtonComponent::ButtonComponent(
    float x,
    float y,
    float width,
    float height,
    const std::string& name)
    : x(x), y(y), width(width), height(height), name(name) {
    EventManager::AddListener<MouseButtonDownEvent>(&clickListener);
}

ButtonComponent::~ButtonComponent() {
    EventManager::RemoveListener<MouseButtonDownEvent>(&clickListener);
}

void ButtonComponent::Update(double deltaTime) {
    if (Mouse::GetX() > x && Mouse::GetX() < x + width && Mouse::GetY() > y &&
        Mouse::GetY() < y + height) {
        if (hovered == false) {
            Mouse::SetCursorPointer();
            EventManager::AddEvent<ButtonMouseOver>(name);
            hovered = true;
        }
    } else {
        if (hovered == true) {
            hovered = false;
            Mouse::SetCursorDefault();
            EventManager::AddEvent<ButtonMouseOff>(name);
        }
    }
}

Button::Button(const std::string& name, float x, float y, float width, float height) {
    AddComponent<Transform>(x, y);
    AddComponent<ButtonComponent>(x, y, width, height, name);
    // AddComponent<Animation>();
    AddComponent<PrimitiveSprite>(PrimitiveSpriteType::FILL_RECTANGLE, Color::White, width, height);
    layer = 100;
}
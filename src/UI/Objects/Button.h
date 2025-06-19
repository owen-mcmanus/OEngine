/**
 * @file Button.h
 * @author Owen McManus
 * @date 2025/5/18
 */

#pragma once
#include "../../Core/GameObject.h"
#include "../../Events/Event.h"
#include "../../Events/EventManager.h"
#include "../../Utils/Color.h"

namespace OEngine::UI {

class ButtonClickEvent : public Event {
  public:
    explicit ButtonClickEvent(const std::string& name) : name(name) {};
    std::string name;
};

class ButtonMouseOver : public Event {
  public:
    explicit ButtonMouseOver(const std::string& name) : name(name) {};
    std::string name;
};

class ButtonMouseOff : public Event {
  public:
    explicit ButtonMouseOff(const std::string& name) : name(name) {};
    std::string name;
};

class ButtonComponent : public Component {
  public:
    ButtonComponent(float x, float y, float width, float height, const std::string& name);
    ~ButtonComponent();
    void Update(double deltaTime) override;
    std::string GetName();

  private:
    float x, y, width, height;
    bool hovered = false;
    std::string name;
    EventListener<MouseButtonDownEvent> clickListener = [this](const MouseButtonDownEvent& e) {
        if (e.GetButton() != Mouse::MouseButton::LEFT)
            return;
        if (e.GetX() > x && e.GetX() < x + width && e.GetY() > y && e.GetY() < y + height) {
            EventManager::AddEvent<ButtonClickEvent>(name);
        }
    };
};

class Button : public GameObject {
  public:
    Button(const std::string& name, float x, float y, float width, float height);
    ~Button() = default;
};
} // namespace OEngine::UI